/******************************************************************************
*    includes
******************************************************************************/
#include "ui_phone.h"
#include "ui_resource.h"
#include "public.h"
#include "cam_disp.h"
#include "V4l2Dev.h"
#include "ImageQueue.h"
#include <jpegdecode.h>
#include "debug.h"
#include "ImageSave.h"
/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} phone_ue_t;

typedef struct
{
	phone_ui_t ui;
	phone_ue_t ue;
} phone_para_t;
static phone_para_t *para = NULL;


#define USE_DISP		0
#define CAM_W			640
#define CAM_H			480
#define CAM_FPS			30

static disp_hdl_t disphdl;
static JpegDecoder* jpegdecoder = NULL;
JpegDecodeOutputDataType outputDataTpe= JpegDecodeOutputDataYV12;
JpegDecodeScaleDownRatio scaleRatio = JPEG_DECODE_SCALE_DOWN_1;

static pthread_t phone_id;
static int running = 1;
static BuffQ_t *ImageQ;

static lv_task_t *phone_task_id = NULL;
static	struct timespec img_start;
static lv_img_dsc_t *play_image = NULL;

#define TIME_DIFF_MS(e, s) ((int64_t)(e.tv_sec - s.tv_sec) * 1000000 + (int64_t)(e.tv_usec - s.tv_usec))/1000;


/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_PHONE, WINDOW_HOME);
	}
}

static void clean_screen(phone_ui_t *ui)
{
	// open tplayerdemo || willow					// ??????Ƶ????ͼƬͼ?㣬pipeҪ??0
	lv_obj_t *scn = lv_scr_act();					// ????Ļ
	static lv_style_t scn_style;
	lv_style_copy(&scn_style, &lv_style_plain);
	scn_style.body.main_color.full = 0x00000000;
	scn_style.body.grad_color.full = 0x00000000;
	lv_obj_set_style(scn, &scn_style);

	static lv_style_t cont_style;
	lv_style_copy(&cont_style, &lv_style_plain);
	cont_style.body.main_color.full = 0x00000000;		// ??cont
	cont_style.body.grad_color.full = 0x00000000;
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &cont_style);
}

static void phone_ue_create(phone_para_t *para)
{
	//lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void phone_ue_destory(phone_para_t *para)
{
	(void)para;
	return;
}

static uint8_t clamp(int value) {
    if (value < 0) return 0;
    if (value > 255) return 255;
    return (uint8_t)value;
}

void YV12ToBGR(uint8_t* yv12,  int width, int height, uint8_t* rgbImage) {
  	uint8_t* yPlane = yv12;
  	uint8_t* vPlane = yPlane + width * height;
	uint8_t* uPlane = vPlane + width * height / 4;

    int frameSize = width * height;
    int chromaWidth = width / 2;
    int chromaHeight = height / 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int yIndex = y * width + x;
            int uIndex = (y / 2) * chromaWidth + (x / 2);
            int vIndex = (y / 2) * chromaWidth + (x / 2);

            // Get the Y, U, and V values
            uint8_t Y = yPlane[yIndex];
            uint8_t U = uPlane[uIndex];
            uint8_t V = vPlane[vIndex];

            // // Convert YUV to RGB according to the formula
            int R = (int)(Y + 1.402 * (V - 128));
            int G = (int)(Y - 0.344136 * (U - 128) - 0.714136 * (V - 128));
            int B = (int)(Y + 1.772 * (U - 128));

            // Set the RGB pixel components
            int rgbIndex = yIndex * 4;
            rgbImage[rgbIndex]     = clamp(B);
            rgbImage[rgbIndex + 1] = clamp(G);
            rgbImage[rgbIndex + 2] = clamp(R);
			rgbImage[rgbIndex + 3] = 0xff;
        }
    }
}

void resizeYV12Nearest(uint8_t *yv12, int srcWidth, int srcHeight,
                       uint8_t *dst, int dstWidth, int dstHeight) {

	uint8_t *srcY = yv12;
	uint8_t *srcV = yv12 + srcWidth*srcHeight;
	uint8_t *srcU = srcV + srcWidth*srcHeight/4;
	uint8_t *dstY = dst;
	uint8_t *dstV = dst + dstWidth*dstHeight;
	uint8_t *dstU = dstV + dstWidth*dstHeight/4;

    float x_ratio = (float)srcWidth / (float)dstWidth;//1.3333333333
    float y_ratio = (float)srcHeight / (float)dstHeight;
    int px, py;

    for (int i = 0; i < dstHeight; i++) {
        for (int j = 0; j < dstWidth; j++) {
            px = (int)(j * x_ratio);
            py = (int)(i * y_ratio);

            // 保证坐标不超出原图范围
            if (px >= srcWidth) px = srcWidth - 1;
            if (py >= srcHeight) py = srcHeight - 1;

            // 计算源图像中的索引并赋值给目标图像
            dstY[i * dstWidth + j] = srcY[py * srcWidth + px];

            // 由于U和V分量的分辨率是Y的一半，需要对应调整
            // if (i % 2 == 0 && j % 2 == 0) {
            //     int srcUIndex = (py / 2) * (srcWidth / 2) + (px / 2);
            //     int srcVIndex = (py / 2) * (srcWidth / 2) + (px / 2);
            //     dstU[(i / 2) * (dstWidth / 2) + (j / 2)] = srcU[srcUIndex];
            //     dstV[(i / 2) * (dstWidth / 2) + (j / 2)] = srcV[srcVIndex];
            // }
        }
    }
}

void *lv_phone_image_thread(void * data)
{
	char *rgb_img = NULL;
	uint32_t rgb_size = 0;

	char *resize_img = NULL;
	uint32_t re_size = 0;

	int ret = V4l2CreateVideo("/dev/video0", CAM_W, CAM_H, CAM_FPS);
	if(ret < 0)
	{
		app_err("video open failed!!!");
		return 0;
	}
	jpegdecoder = JpegDecoderCreate();


#if USE_DISP
	re_size = LV_HOR_RES_MAX * LV_VER_RES_MAX * 3 / 2;
	resize_img = malloc(re_size);
	memset(&resize_img, 0, re_size);
	dispInit(&disphdl, LV_HOR_RES_MAX, LV_VER_RES_MAX);
#else

	rgb_size = CAM_W * CAM_H * 4;
	rgb_img = malloc(rgb_size);

#endif
	V4l2Start();

	struct timeval s_time;
	struct timeval e_time;

	while(running)
	{

		unsigned char *frame_addr= V4l2GetFrame();
		if(!frame_addr)
		{
			app_err("get frame error!!!");
			continue;
		}
#define USE_DECODER  0
		// ImageSaveFile(0, (char *)frame_addr, frame_len, "jpg", frame_len);
#if USE_DECODER
		JpegDecoderSetDataSourceBuf(jpegdecoder, (char *)frame_addr, V4l2GetFrameLen(), scaleRatio, outputDataTpe);
		ImgFrame* imgFrame = JpegDecoderGetFrame(jpegdecoder);
#endif

#if USE_DISP
		// app_err("111\n");

		resizeYV12Nearest(imgFrame->mYuvData, imgFrame->mDisplayWidth, imgFrame->mDisplayHeight,
	  	resize_img, LV_HOR_RES_MAX , LV_VER_RES_MAX);
		app_err("111\n");
		dispPlay(&disphdl, resize_img, re_size);
#else

#if USE_DECODER
		app_err("%d %d %d %d %d %d\n", imgFrame->mYuvSize, re_size, 
		imgFrame->mDisplayWidth, imgFrame->mDisplayHeight,
		imgFrame->mWidth, imgFrame->mHeight);
		gettimeofday(&s_time, NULL);
		YV12ToBGR(imgFrame->mYuvData, imgFrame->mDisplayWidth, imgFrame->mDisplayHeight, rgb_img);
		gettimeofday(&e_time, NULL);

		int64_t dt = TIME_DIFF_MS(e_time, s_time);
		//app_err("111111111111111 dt=%d\n",dt);
		BuffFrameInfo_t frame;
		frame.FrameY = (char *)rgb_img;
		frame.FrameUV = NULL;
		frame.Yszie =  rgb_size;
		frame.UVszie = 0;
		frame.TimeStamp = V4l2GetTimeStamp();
		frame.Width = imgFrame->mDisplayWidth;
		frame.Height = imgFrame->mDisplayHeight;
		frame.Fps = V4l2GetFps();
#else
 		lv_img_dsc_t *rgb_dsc = mal_load_image_from_mem(frame_addr, V4l2GetFrameLen());
		BuffFrameInfo_t frame;
		frame.FrameY = (char *)rgb_dsc->data;
		frame.FrameUV = NULL;
		frame.Yszie =  rgb_dsc->data_size;
		frame.UVszie = 0;
		frame.TimeStamp = V4l2GetTimeStamp();
		frame.Width = rgb_dsc->header.w;
		frame.Height = rgb_dsc->header.h;
		frame.Fps = V4l2GetFps();

#endif

		int ret = ImageQueuePushData(ImageQ, frame);
		if(ret < 0)
		{
			app_err("Buff queue push error\n");
		}
#endif

#if USE_DECODER
		JpegDecoderReleaseFrame(jpegdecoder);
#else
		mal_unload_image(rgb_dsc);
#endif 
		V4l2ReleaseFrame();
	}
	app_info("\n");
	V4l2DestroyVideo();
	if(jpegdecoder)
	{
		JpegDecoderDestory(jpegdecoder);
		jpegdecoder = NULL;
	}
	app_info("\n");
#if USE_DISP
	dispClose(&disphdl);
#else
	if(resize_img)
	{
		free(resize_img);
	}
	
	if(rgb_img)
	{
		free(rgb_img);
	}

//	system("cat /sys/devices/platform/soc@3000000/soc@3000000:usbc0@0/usb_device \n\r ");
//	system("cat /sys/devices/platform/soc@3000000/soc@3000000:usbc0@0/usb_host \n\r ");
#endif
	app_info("\n");

	return NULL;
}

static void phone_task(lv_task_t * param)
{
	phone_ui_t *ui = &para->ui;

	BuffFrameInfo_t *buff = ImageQueueGetDataBuff(ImageQ, 0, 50);
	if(!buff)
	{
		return;
	}
	
	lv_img_dsc_t rgb_dsc;
	memset(&rgb_dsc, 0, sizeof(lv_img_dsc_t));
	rgb_dsc.header.w = buff->Width;
	rgb_dsc.header.h = buff->Height;
	rgb_dsc.header.always_zero = 0;
	rgb_dsc.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
	rgb_dsc.data_size = buff->Yszie;
	rgb_dsc.data = buff->FrameY;
	
    if(rgb_dsc.header.w > (LV_HOR_RES_MAX) || rgb_dsc.header.h > (LV_VER_RES_MAX))
	{
		if(play_image)
		{
			mal_unload_image(play_image);
			play_image = NULL;
		}
		play_image = resize_image(&rgb_dsc, LV_HOR_RES_MAX, LV_VER_RES_MAX);
		lv_img_set_src(ui->img_1, play_image);

	}else{
		lv_img_set_src(ui->img_1, &rgb_dsc);
	}

	ImageQueueReleaseDataBuff(ImageQ, buff);

	float dt = get_diff_time(&img_start, 0);
	get_diff_time(&img_start, 1);

	struct timeval s_time = buff->TimeStamp;
	struct timeval e_time;
	e_time.tv_sec = img_start.tv_sec;
	e_time.tv_usec = img_start.tv_nsec/1000;
	int64_t dt1 = TIME_DIFF_MS(e_time, s_time);

 	app_info("dt = %dms dt1=%dms %p\n", (int)(dt*1000), dt1, buff->FrameY);
}

static void phone_key_canel_callback(void)
{
    switch_window(WINDOW_PHONE, WINDOW_HOME);
}


static int phone_create(void)
{
	para = (phone_para_t *)malloc(sizeof(phone_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(phone_para_t));

	para->ui.parent = lv_scr_act();
	phone_ui_create(&para->ui);
	phone_ue_create(para);
	
	key_callback_register(LV_KEY_4, phone_key_canel_callback);

	ImageQ = ImageQueueRequest("PhoneQueue", 5, CAM_W*CAM_H*4, 0);

	phone_task_id = lv_task_create(phone_task, 10, LV_TASK_PRIO_MID, NULL);

	running = 1;
	pthread_create(&phone_id, NULL, lv_phone_image_thread, NULL);
	get_diff_time(&img_start, 1);

	//clean_screen(&para->ui);
	app_info("\n");
	return 0;
}

static int phone_destory(void)
{

	running = 0;
	pthread_join(phone_id, NULL);
	lv_task_del(phone_task_id);	

	app_info("\n");

	ImageQueueDestroy(ImageQ);
	if(play_image)
	{
		mal_unload_image(play_image);		
		play_image = NULL;
	}
	app_info("\n");

	phone_ue_destory(para);
	phone_ui_destory(&para->ui);
	free(para);
	para = NULL;
	return 0;
}

static int phone_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int phone_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t phone_window = 
{
	.ops =
	{
		phone_create,
		phone_destory,
		phone_show,
		phone_hide
	}, 
	.data =
	{
		.id         = WINDOW_PHONE, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_PHONE(void)
{
	register_window(&phone_window);
}

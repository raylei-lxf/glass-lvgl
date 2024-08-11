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

#define CAM_W			640
#define CAM_H			480
#define CAM_FPS			30

static disp_hdl_t disphdl;
static JpegDecoder* jpegdecoder;
JpegDecodeOutputDataType outputDataTpe= JpegDecodeOutputDataNV21;
JpegDecodeScaleDownRatio scaleRatio = JPEG_DECODE_SCALE_DOWN_1;

static pthread_t phone_id;
static int running = 1;
static BuffQ_t *ImageQ;

static lv_task_t *phone_task_id;
static	struct timespec img_start;
lv_img_dsc_t *play_image = NULL;

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

void *lv_phone_image_thread(void * data)
{
	while(running)
	{

		unsigned char *frame_addr= V4l2GetFrame();
		if(!frame_addr)
		{
			app_err("get frame error!!!");
			continue;
		}
	
		// ImageSaveFile(0, (char *)frame_addr, frame_len, "jpg", frame_len);

		lv_img_dsc_t *rgb_img = mal_load_image_from_mem(frame_addr, V4l2GetFrameLen());
		
		BuffFrameInfo_t frame;
		frame.FrameY = (char *)rgb_img->data;
		frame.FrameUV = NULL;
		frame.Yszie =  rgb_img->data_size;
		frame.UVszie = 0;
		frame.TimeStamp = V4l2GetTimeStamp();
		frame.Width = rgb_img->header.w;
		frame.Height = rgb_img->header.h;
		frame.Fps = V4l2GetFps();

		//app_info("frame_len = %d  %p %d", V4l2GetFrameLen(), frame.FrameY, rgb_img->data_size);


		int ret = ImageQueuePushData(ImageQ, frame);
		if(ret < 0)
		{
			app_err("Buff queue push error\n");
		}

		mal_unload_image(rgb_img);

		//void *image1 = mal_load_image_from_mem(frame_addr, frame_len);
		// lv_img_set_src(photo_play, image1);
		
	
		//  JpegDecoderSetDataSourceBuf(jpegdecoder, (char *)frame_addr, frame_len, scaleRatio, outputDataTpe);
		//  ImgFrame* imgFrame = JpegDecoderGetFrame(jpegdecoder);
		//  dispPlay(&disphdl, imgFrame->mYuvData, imgFrame->mYuvSize);

		 V4l2ReleaseFrame();
		// uint32_t frame_addr;
		// uint32_t frame_len;
		

		// cameraGetFrame(cam_hd[0], &frame_addr, &frame_len);

		// ImageSaveFile(0, (char *)frame_addr, frame_len, "jpg", frame_len);

		// app_info("frame_len = %d", frame_len);
		// // JpegDecoderSetDataSourceBuf(jpegdecoder, (char *)frame_addr, frame_len, scaleRatio, outputDataTpe);
		// // ImgFrame* imgFrame = JpegDecoderGetFrame(jpegdecoder);
		// // dispPlay(&disphdl, imgFrame->mYuvData, imgFrame->mYuvSize);

		// cameraReleaseFrame(cam_hd[0]);		

	}
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
	
	lv_img_dsc_t rgb_img;
	memset(&rgb_img, 0, sizeof(lv_img_dsc_t));
	rgb_img.header.w = buff->Width;
	rgb_img.header.h = buff->Height;
	rgb_img.header.always_zero = 0;
	rgb_img.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
	rgb_img.data_size = buff->Yszie;
	rgb_img.data = buff->FrameY;
	
    if(rgb_img.header.w > (LV_HOR_RES_MAX) || rgb_img.header.h > (LV_VER_RES_MAX))
	{
		if(play_image)
		{
			mal_unload_image(play_image);		
		}
		play_image = resize_image(&rgb_img, LV_HOR_RES_MAX, LV_VER_RES_MAX);
		lv_img_set_src(ui->img_1, play_image);

	}else{
		lv_img_set_src(ui->img_1, &rgb_img);
	}

	ImageQueueReleaseDataBuff(ImageQ, buff);

	float dt = get_diff_time(&img_start, 0);
	get_diff_time(&img_start, 1);

	struct timeval s_time = buff->TimeStamp;
	struct timeval e_time;
	e_time.tv_sec = img_start.tv_sec;
	e_time.tv_usec = img_start.tv_nsec/1000;
	int dt1 = ((int32_t)(e_time.tv_sec - s_time.tv_sec) * 1000000 + (int32_t)(e_time.tv_usec - s_time.tv_usec))/1000;
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

	int ret = V4l2CreateVideo("/dev/video0", CAM_W, CAM_H, CAM_FPS);
	if(ret < 0)
	{
		app_err("video open failed!!!");
		return 0;
	}

	V4l2Start();
	// jpegdecoder = JpegDecoderCreate();

	// disphdl.src_w = CAM_H;
	// disphdl.src_h = CAM_W;
	// dispInit(&disphdl);
 
	ImageQ = ImageQueueRequest("PhoneQueue", 3, CAM_W*CAM_H*4, 0);

	phone_task_id = lv_task_create(phone_task, 5, LV_TASK_PRIO_MID, NULL);

	running = 1;
	pthread_create(&phone_id, NULL, lv_phone_image_thread, NULL);
	get_diff_time(&img_start, 1);

	return 0;
}

static int phone_destory(void)
{
	app_info("\n");

	running = 0;
	lv_task_del(phone_task_id);	
	pthread_join(phone_id, NULL);
	app_info("\n");

	V4l2DestroyVideo();

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


	app_info("\n");

	// JpegDecoderDestory(jpegdecoder);
	// dispClose(&disphdl);

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

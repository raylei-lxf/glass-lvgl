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

#define CAM_H			640
#define CAM_W			480
#define CAM_FPS			30

static disp_hdl_t disphdl;
static JpegDecoder* jpegdecoder;
JpegDecodeOutputDataType outputDataTpe= JpegDecodeOutputDataNV21;
JpegDecodeScaleDownRatio scaleRatio = JPEG_DECODE_SCALE_DOWN_1;

static pthread_t phone_id;
static int running = 1;
static BuffQ_t *ImageQ;

static lv_task_t *phone_task_id;

static lv_img_dsc_t *play_image = NULL;

static struct timespec img_start;

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
		get_diff_time(&img_start, 1);
	

		BuffFrameInfo_t frame;

		memset(&frame, 0, sizeof(BuffFrameInfo_t));
		frame.FrameY = (char *)frame_addr;
		frame.FrameUV=NULL;
		frame.Yszie = V4l2GetFrameLen();;
		frame.Width = V4l2GetWidth();
		frame.Height = V4l2GetHeight();
		frame.Fps= V4l2GetFps();
		frame.TimeStamp = V4l2GetTimeStamp();


		//app_info("frame_len = %d", frame.Yszie);
		ImageQueuePushData(ImageQ, frame);
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

	BuffFrameInfo_t *buff = ImageQueueGetDataBuff(ImageQ, 0, 1000);
	if(!buff)
	{
		return;
	}

	if(play_image)
	{
		mal_unload_image(play_image);
	}

	play_image = mal_load_image_from_mem(buff->FrameY, buff->Yszie);

    if(play_image->header.w > (LV_HOR_RES_MAX) || play_image->header.h > (LV_VER_RES_MAX))
	{
		play_image = resize_image(play_image, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	}

	ImageQueueReleaseDataBuff(ImageQ, buff);

	lv_img_set_src(ui->img_1, play_image);
	float  dt = get_diff_time(&img_start, 0);
	app_info("dt = %d\n", (int)(dt*1000));
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

	int ret = V4l2CreateVideo("/dev/video0", 	CAM_H, CAM_W, CAM_FPS);
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

	ImageQ = ImageQueueRequest("PhoneQueue", 3, CAM_H*CAM_W, 0);

	phone_task_id = lv_task_create(phone_task, 10, LV_TASK_PRIO_MID, NULL);

	running = 1;
	pthread_create(&phone_id, NULL, lv_phone_image_thread, NULL);


	return 0;
}

static int phone_destory(void)
{
	app_info("\n");
	running = 0;
	pthread_join(phone_id, NULL);

	app_info("\n");

	lv_task_del(phone_task_id);

	ImageQueueDestroy(ImageQ);

	V4l2DestroyVideo();

	app_info("\n");


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

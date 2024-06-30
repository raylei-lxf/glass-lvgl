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


static disp_hdl_t disphdl;
// static camera_hdl *cam_hd[1];
static JpegDecoder* jpegdecoder;
JpegDecodeOutputDataType outputDataTpe= JpegDecodeOutputDataNV21;
JpegDecodeScaleDownRatio scaleRatio = JPEG_DECODE_SCALE_DOWN_1;

static pthread_t phone_id;
static int running = 1;
static BuffQ_t *ImageQ;
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
			continue;
		}
		uint32_t frame_len = V4l2GetFrameLen();
		
		ImageSaveFile(0, (char *)frame_addr, frame_len, "jpg", frame_len);
		
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

static void phone_key_canel_callback(void)
{
    switch_window(WINDOW_HOME, get_last_window_id());
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


	V4l2CreateVideo("/dev/video0", 640, 480, 60);
	V4l2Start();
	//jpegdecoder = JpegDecoderCreate();
	// cameraCreate(cam_hd, 1);
	// cameraInit(cam_hd[0], 0, 640, 480, 30);
	// cameraStartCapture(cam_hd[0]);
	disphdl.src_w = 640;
	disphdl.src_h = 480;
	//dispInit(&disphdl);

	//ImageQ = ImageQueueRequest("phone", 3, 640*480, 0);

	running = 1;
	pthread_create(&phone_id, NULL, lv_phone_image_thread, NULL);

	return 0;
}

static int phone_destory(void)
{
	running = 0;
	pthread_join(phone_id, NULL);

	phone_ue_destory(para);
	phone_ui_destory(&para->ui);
	free(para);
	para = NULL;

	V4l2DestroyVideo();
	// cameraStopCapture(cam_hd[0]);
	// cameraDeInit(cam_hd[0]);
	// CameraDestroy(cam_hd, 1);
	// dispClose(&disphdl);
	// JpegDecoderDestory(jpegdecoder);
	//ImageQueueDestroy(ImageQ);

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

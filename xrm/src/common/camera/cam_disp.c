#include "cam_disp.h"
#include "dbList.h"
#include "debug.h"


int dispInit(disp_hdl_t *hdl)
{
	if(!hdl){
		return -1;
	}

    VoutRect mPreviewRect;
	videoParam param;

    mPreviewRect.x = 0;
	mPreviewRect.y = 0;
	mPreviewRect.width = SCREAN_W;//640;
	mPreviewRect.height = SCREAN_H;//480;

	hdl->DisPort = CreateVideoOutport(0);
	if(!hdl->DisPort){
		return -1;
	}
	hdl->DisPort->init(hdl->DisPort,1,ROTATION_ANGLE_0,&mPreviewRect);
//	app_info("hlayer = %d\n", hdl->DisPort->hlayer);
    mPreviewRect.width = hdl->DisPort->getScreenWidth(hdl->DisPort);
    mPreviewRect.height = hdl->DisPort->getScreenHeight(hdl->DisPort);
   // app_info("width:%d, height:%d\n", (int)mPreviewRect.width, (int)mPreviewRect.height);

    /* set Route */
	hdl->DisPort->setRoute(hdl->DisPort, VIDEO_SRC_FROM_CAM);

	/* set Rect */
	hdl->DisPort->setRect(hdl->DisPort,&mPreviewRect);
	param.srcInfo.format = DISPLAY_FMT;

	param.srcInfo.w = hdl->src_w;
	param.srcInfo.h = hdl->src_h;
	hdl->DisPort->allocateVideoMem(hdl->DisPort,&param);

    hdl->DisPort->SetZorder(hdl->DisPort,VIDEO_ZORDER_MIDDLE);
	
	hdl->DisPort->setEnable(hdl->DisPort, 0);
	hdl->DisPort->setRotateAngel(hdl->DisPort,ROTATION_ANGLE_0);

 //   app_info(" disp init end!\n");

    return 0;
}

int dispClose(disp_hdl_t *hdl)
{

	dispOutPort *disPort = hdl->DisPort;

	if(!disPort){
		return -1;
	}
    disPort->enable = 0;
	disPort->setEnable(disPort,0);
    disPort->freeVideoMem(disPort);
    disPort->deinit(disPort);
    DestroyVideoOutport(disPort);

	return 0;
}


void dispPlay(disp_hdl_t *hdl, char *frame, uint32_t len)
{
	videoParam paramDisp;

	paramDisp.isPhy = 0;
	paramDisp.srcInfo.w = hdl->src_w;
	paramDisp.srcInfo.h = hdl->src_h;
	paramDisp.srcInfo.crop_x = 0;
	paramDisp.srcInfo.crop_y = 0;
	paramDisp.srcInfo.crop_w = hdl->src_w;
	paramDisp.srcInfo.crop_h = hdl->src_h;
	paramDisp.srcInfo.format = DISPLAY_FMT;
	paramDisp.srcInfo.color_space = 0;


	hdl->DisPort->writeData(hdl->DisPort, frame, len, &paramDisp);

}


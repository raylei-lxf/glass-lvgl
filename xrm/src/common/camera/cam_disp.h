#ifndef _CAM_DISP_H
#define _CAM_DISP_H

#ifdef __cplusplus
extern "C"{
#endif
#include "videoOutPort.h"
#include "lv_conf.h"


#define SCREAN_W	LV_HOR_RES_MAX
#define SCREAN_H	LV_VER_RES_MAX 

// #define SCREAN_W	320
// #define SCREAN_H	240
#define DISPLAY_FMT		VIDEO_PIXEL_FORMAT_NV12

typedef struct{
	
	dispOutPort *DisPort;
	int frist_frame;	

	uint32_t src_w;
	uint32_t src_h;
}disp_hdl_t;

int dispInit(disp_hdl_t *hdl, int src_w, int src_h);
int dispClose(disp_hdl_t *hdl);
void dispPlay(disp_hdl_t *hdl, char *frame, uint32_t len);


#ifdef _cplusplus
}
#endif

#endif


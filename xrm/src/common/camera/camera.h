#ifndef _CAMERA_H
#define _CAMERA_H


#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <errno.h>
#include <linux/videodev2.h>

//#define __USE_VIN_ISP__

#ifdef __USE_VIN_ISP__
#include "AWIspApi.h"
#include "sunxi_camera_v2.h"
#endif

#define camera_dbg_en 1

#define camera_dbg(x,arg...) do{ \
                                if(camera_dbg_en) \
                                    printf("[CAMERA_DEBUG]"x,##arg); \
                            }while(0)

//print when error happens
#define camera_err(x,arg...) do{ \
                                printf("\033[1m\033[;31m[CAMERA_ERR]"x,##arg); \
                                printf("\033[0m"); \
                                fflush(stdout); \
                            }while(0)

#define camera_prompt(x,arg...) do{ \
                                printf("\033[1m\033[;32m[CAMERA_PROMPT]"x"\033[0m",##arg); \
                                fflush(stdout); \
                            }while(0)

#define camera_warn(x,arg...) printf("[CAMERA_WARN]"x,##arg)
//print unconditional, for important info
#define camera_print(x,arg...) printf("[CAMERA]"x,##arg)

#define SENSOR_W 	640
#define SENSOR_H	480

//#define SENSOR_FMT		V4L2_PIX_FMT_NV21
#define SENSOR_FMT	        V4L2_PIX_FMT_MJPEG

enum camera_stat{
	CAMERA_DEINIT_S,
	CAMERA_INIT_S,
	CAMERA_START_S,
	CAMERA_STOP_S,
};

struct buffer
{
    void *start[3];
    size_t length[3];
};

struct datainfo
{
    int index;
    void *start;
    unsigned long phaddr;
    size_t length;
    struct timeval timestamp;
};

typedef struct camera_hdl
{
	char dev_name[64];
    int videofd;
	int video_index;
	int driver_type;
	int sensor_type;
    unsigned int video_width;
    unsigned int video_height;
    unsigned int pixelformat;
    unsigned int fps;
	enum camera_stat status;
	int nplanes;
	struct v4l2_plane *planes_alloc;
    unsigned int num_buffer;
    struct buffer *buffers;
    struct datainfo data_info;
    fd_set fds;

	struct SunxiMemOpsS *ionfd;
#ifdef __USE_VIN_ISP__
    AWIspApi *ispPort;
	int ispId;
#endif
}camera_hdl;

int cameraInit(camera_hdl *hdl, int index, int w, int h, int fps);
int cameraDeInit(camera_hdl *hdl);
int cameraStartCapture(camera_hdl *hdl);
int cameraStopCapture(camera_hdl *hdl);
int cameraGetFrame(camera_hdl *hdl, unsigned int *frame, unsigned int *len);
int cameraReleaseFrame(camera_hdl *hdl);
enum camera_stat cameraGetStatus(camera_hdl *hdl);
int cameraCreate(camera_hdl *hdl[], int num);
int CameraDestroy(camera_hdl *hdl[], int num);

#endif




//
// Created by raylei on 1/19/23.
//

#ifndef SAMPLE_USB_V4L2DEV_H
#define SAMPLE_USB_V4L2DEV_H

#include <errno.h>
#include <fcntl.h>
// #include <iostream>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "xrm_conf.h"
#define IMG_BUFF_NUM 3
#define V4L2_FORMAT V4L2_PIX_FMT_MJPEG
#define V4L2_VIDEO_TYPE   V4L2_BUF_TYPE_VIDEO_CAPTURE

#define DebugWarn   com_warn
#define DebugInfo   com_info
#define DebugDbg   com_info
#define DebugErr    com_err
/*************************V4L2_PIX_FMT_YUYV V4L2_PIX_FMT_MJPEG****************可以选择*/

void V4l2CreateVideo(char *devName, int w, int h, int fps);
void V4l2DestroyVideo();

int V4l2Start();
void V4l2Stop();
unsigned char *V4l2GetFrame();
void V4l2ReleaseFrame();
void V4l2ClearAllFrame();
unsigned int V4l2GetFps();
unsigned int V4l2GetWidth();
unsigned int V4l2GetHeight();
unsigned int V4l2GetFrameLen();
unsigned int V4l2GetFormat();
struct timeval V4l2GetTimeStamp();

#endif // SAMPLE_USB_V4L2DEV_H

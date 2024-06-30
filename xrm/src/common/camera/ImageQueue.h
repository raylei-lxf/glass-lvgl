//
// Created by raylei on 8/9/23.
//

#ifndef IMU_CAMERA_DRIVER_IMAGEQUEUE_H
#define IMU_CAMERA_DRIVER_IMAGEQUEUE_H

#include "BuffQueue.h"

typedef struct __attribute__((packed))
{
    int index;
    char *FrameY;
    char *FrameUV;
    uint32_t Yszie;
    uint32_t UVszie;

    struct timeval TimeStamp;
    struct timeval SysTimeStamp;
    uint16_t Width;
    uint16_t Height;
    uint16_t Fps;
    uint16_t Exp;
    uint16_t Gain;
    uint16_t Format;
    int isSync;
} BuffFrameInfo_t;

/*申请图像队列*/
BuffQ_t *ImageQueueRequest(const char *name, uint32_t num, uint32_t Ysize, uint32_t UVszie);

/*销毁队列*/
void ImageQueueDestroy(BuffQ_t *bq);

/*push数据到队列中，会执行一次拷贝*/
int ImageQueuePushData(BuffQ_t *bq, BuffFrameInfo_t data);

/*获取队列中数据buff， mode：0非阻塞，1阻塞*/
BuffFrameInfo_t *ImageQueueGetDataBuff(BuffQ_t *bq, int mode, uint32_t timeout_ms);

/*释放该buff到空链表中去*/
int ImageQueueReleaseDataBuff(BuffQ_t *bq, BuffFrameInfo_t *data);

/*将该数据buff重新放到队列的头部*/
//int ImageQueuePutDataToHead(BuffQ_t *bq, BuffFrameInfo_t *data);

/*获取队列中空内容的buff.*/
BuffFrameInfo_t *ImageQueueGetEmpytBuff(BuffQ_t *bq);

/*将该buff地址push到FULL队列的尾部，和ImageQueueGetEmpytBuff配套使用*/
int ImageQueuePushBuffToList(BuffQ_t *bq, BuffFrameInfo_t *data);

/*只访问队列中的头部数据，并不从队列中移除*/
//BuffFrameInfo_t *ImageBuffQueueGetHeadData(BuffQ_t *bq, int mode);

void ImageBuffQueueClearAll(BuffQ_t *bq);

void ImageBuffSetDefaultValue(BuffQ_t *bq, char value);

#endif // IMU_CAMERA_DRIVER_IMAGEQUEUE_H

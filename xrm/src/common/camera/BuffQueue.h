//
// Created by raylei on 8/4/23.
//

#ifndef IMU_CAMERA_DRIVER_BUFFQUEUE_H
#define IMU_CAMERA_DRIVER_BUFFQUEUE_H

#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include "xrm_conf.h"
#include "dbList.h"

#define DebugWarn   com_warn
#define DebugInfo   com_info
#define DebugDbg   com_info
#define DebugErr    com_err

typedef struct
{
    char name[128];
    db_list_t *ListEmpty;
    db_list_t *ListFull;
    uint32_t num;
    int size;
    void *data[128];
    uint32_t DataCount;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
} BuffQ_t;

/*申请buff队列*/
BuffQ_t *BuffQueueRequest(const char *name, uint32_t num, uint32_t size);

/*销毁队列*/
void BuffQueueDestroy(BuffQ_t *bq);

/*push数据地址到队列中*/
int BuffQueuePushData(BuffQ_t *bq, void *data, int len);

/*从队列中获取数据地址，mode：0非阻塞，1阻塞*/
void *BuffQueueGetDataBuff(BuffQ_t *bq, int mode, uint32_t timeout_ms);

/*释放地址*/
int BuffQueueReleaseDataBuff(BuffQ_t *bq, void *data);

/*判断队列是否为空*/
int BuffQueueDataIsEmpty(BuffQ_t *bq);

/*将数据地址放置到队列的头部*/
//int BuffQueuePutDataToHead(BuffQ_t *bq, void *data);

/*只访问队列头部数据，不进行队列操作*/
//void *BuffQueueGetHeadData(BuffQ_t *bq, int mode);

#endif // IMU_CAMERA_DRIVER_BUFFQUEUE_H

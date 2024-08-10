//
// Created by raylei on 8/4/23.
//

#include "BuffQueue.h"
#include "dbList.h"

BuffQ_t *BuffQueueRequest(const char *name, uint32_t num, uint32_t size)
{
    int ret = 0;

    BuffQ_t *bq = (BuffQ_t *)malloc(sizeof(BuffQ_t));
    if (!bq)
    {
        DebugErr("malloc failed\n");
        return NULL;
    }
    memset(bq, 0, sizeof(BuffQ_t));
    if (strlen(name) < sizeof(bq->name))
    {
        memcpy(bq->name, name, strlen(name));
    }
    else
    {
        memcpy(bq->name, name, sizeof(bq->name));
    }
    DebugInfo("%s:requeset buffer queue, num=%d\n", bq->name, num);

    bq->ListFull = db_list_create(name, 0);
    if (!bq->ListFull)
    {
        DebugErr("create list failed\n");
        return NULL;
    }
    bq->ListEmpty = db_list_create(name, 0);
    if (!bq->ListEmpty)
    {
        DebugErr("create list failed\n");

        return NULL;
    }
    bq->num = num;
    bq->size = size;
    char *datap = (char *)malloc(bq->num * bq->size);
    for (int i = 0; i < bq->num; i++)
    {
        bq->data[i] = datap + i * bq->size;
        if (!bq->data)
        {
            DebugErr("malloc failed\n");
            return NULL;
        }
        __db_list_put_tail(bq->ListEmpty, bq->data[i]);
    }

    pthread_mutex_init(&bq->mutex, NULL);
    pthread_cond_init(&bq->cond, NULL);

    return bq;
}

void BuffQueueDestroy(BuffQ_t *bq)
{
    void *buff = NULL;

    if (!bq)
    {
        return;
    }
    DebugInfo("%s:destroy buff queue\n", bq->name);
    if (bq->data[0])
    {
        free(bq->data[0]);
    }
    __db_list_destory(bq->ListEmpty);
    __db_list_destory(bq->ListFull);

    pthread_mutex_destroy(&bq->mutex);
    pthread_cond_destroy(&bq->cond);

    free(bq);
}

int BuffQueuePushData(BuffQ_t *bq, void *data, int len)
{
    void *buff = NULL;

    int ret = -1;

    if (!bq)
    {
        return -1;
    }
    pthread_mutex_lock(&bq->mutex);
    if (!is_list_empty(bq->ListEmpty))
    {
        buff = (void *)__db_list_pop(bq->ListEmpty);
        memcpy(buff, data, len);
        bq->DataCount++;
        if (bq->DataCount > (bq->num - 3))
        {
            DebugWarn("%s:Buffer data count=%d\n", bq->name, bq->DataCount);
        }
        // DebugDbg("%s:buffer Data count=%d \n", bq->name, bq->DataCount);
        __db_list_put_tail(bq->ListFull, buff);
        pthread_cond_signal(&bq->cond);
        ret = 0;
    }
    pthread_mutex_unlock(&bq->mutex);

    return ret;
}

void *BuffQueueGetDataBuff(BuffQ_t *bq, int mode, uint32_t timeout_ms)
{
    void *buff = NULL;
    struct timespec abstime = {.tv_sec = 0, .tv_nsec = 0};
    int ret = 0;

    if (!bq)
    {
        return NULL;
    }

    struct timeval now;
    gettimeofday(&now, NULL);

    uint64_t time_us = now.tv_usec + timeout_ms * 1000;
    abstime.tv_sec = now.tv_sec + time_us / 1000000;
    abstime.tv_nsec = (time_us % 1000000) * 1000;

    pthread_mutex_lock(&bq->mutex);
    if (is_list_empty(bq->ListFull) && mode && timeout_ms)
    {
        // ret = pthread_cond_wait(&bq->cond, &bq->mutex);
        ret = pthread_cond_timedwait(&bq->cond, &bq->mutex, &abstime);
        if (ret == ETIMEDOUT)
        {
            DebugWarn("%s:BuffQueue wait timeout ret = %d\n", bq->name, ret);
        }
    }
    if (!is_list_empty(bq->ListFull))
    {
        buff = (void *)__db_list_pop(bq->ListFull);
        bq->DataCount--;
        // DebugDbg("%s:buffer Data count=%d \n", bq->name, bq->DataCount);
    }
    pthread_mutex_unlock(&bq->mutex);
    return buff;
}

int BuffQueueReleaseDataBuff(BuffQ_t *bq, void *data)
{
    if (!bq || !data)
    {
        return -1;
    }

    pthread_mutex_lock(&bq->mutex);
    __db_list_put_tail(bq->ListEmpty, data);
    pthread_mutex_unlock(&bq->mutex);

    return 0;
}

int BuffQueueDataIsEmpty(BuffQ_t *bq)
{
    int ret;

    if (!bq)
    {
        return 1;
    }

    pthread_mutex_lock(&bq->mutex);
    ret = is_list_empty(bq->ListFull);
    pthread_mutex_unlock(&bq->mutex);

    return ret;
}

// int BuffQueuePutDataToHead(BuffQ_t *bq, void *data)
// {
//     if (!bq)
//     {
//         return -1;
//     }

//     pthread_mutex_lock(&bq->mutex);
//     bq->DataCount++;
//     __db_list_put_head(bq->ListFull, data);
//     pthread_mutex_unlock(&bq->mutex);

//     return 0;
// }

// void *BuffQueueGetHeadData(BuffQ_t *bq, int mode)
// {
//     void *buff = NULL;
//     struct timespec abstime = {.tv_sec = 0, .tv_nsec = 0};
//     int ret = 0;

//     if (!bq)
//     {
//         return NULL;
//     }

//     struct timeval now;
//     gettimeofday(&now, NULL);
//     abstime.tv_sec = now.tv_sec + 2;
//     abstime.tv_nsec = now.tv_usec + 0;

//     pthread_mutex_lock(&bq->mutex);
//     if (is_list_empty(bq->ListFull) && mode)
//     {
//         // ret = pthread_cond_wait(&bq->cond, &bq->mutex);
//         ret = pthread_cond_timedwait(&bq->cond, &bq->mutex, &abstime);
//         if (ret == ETIMEDOUT)
//         {
//             DebugWarn("BuffQueue wait timeout ret = %d\n", ret);
//         }
//     }
//     if (!is_list_empty(bq->ListFull))
//     {
//         buff = get_current_data(bq->ListFull);
//     }
//     pthread_mutex_unlock(&bq->mutex);

//     return buff;
// }

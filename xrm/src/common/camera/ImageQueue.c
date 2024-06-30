//
// Created by raylei on 8/9/23.
//

#include "ImageQueue.h"

BuffQ_t *ImageQueueRequest(const char *name, uint32_t num, uint32_t Ysize, uint32_t UVszie)
{
    BuffQ_t *bq = BuffQueueRequest(name, num, sizeof(BuffFrameInfo_t));

    if (!bq)
    {
        return NULL;
    }

    for (int i = 0; i < bq->num; i++)
    {
        BuffFrameInfo_t *frame = (BuffFrameInfo_t *)bq->data[i];
        if (Ysize)
        {
            frame->FrameY = (char *)malloc(Ysize + UVszie);
            if (!frame->FrameY)
            {
                DebugErr("malloc failed\n");
                BuffQueueDestroy(bq);
                return NULL;
            }
            if (UVszie)
            {
                frame->FrameUV = frame->FrameY + Ysize;
            }
            else
            {
                frame->FrameUV = NULL;
            }
            DebugDbg("FrameY addr=%p, FrameUv addr=%p\n", frame->FrameY, frame->FrameUV);
        }
        frame->index = i;
    }
    return bq;
}

void ImageQueueDestroy(BuffQ_t *bq)
{
    BuffFrameInfo_t *buff = NULL;

    if (!bq)
    {
        return;
    }

    for (int i = 0; i < bq->num; i++)
    {
        buff = (BuffFrameInfo_t *)bq->data[i];
        free(buff->FrameY);
    }

    BuffQueueDestroy(bq);
}

int ImageQueuePushData(BuffQ_t *bq, BuffFrameInfo_t data)
{
    BuffFrameInfo_t *buff = NULL;

    int ret = -1;

    if (!bq)
    {
        return -1;
    }

    pthread_mutex_lock(&bq->mutex);
    if (!is_list_empty(bq->ListEmpty))
    {
        buff = (BuffFrameInfo_t *)__db_list_pop(bq->ListEmpty);
        if (data.FrameY && data.Yszie)
        {
            memcpy(buff->FrameY, data.FrameY, data.Yszie);
            buff->Yszie = data.Yszie;
        }

        if (data.FrameUV && data.UVszie)
        {
            buff->FrameUV = buff->FrameY + buff->Yszie;
            memcpy(buff->FrameUV, data.FrameUV, data.UVszie);
            buff->UVszie = data.UVszie;
        }

        buff->TimeStamp = data.TimeStamp;
        buff->SysTimeStamp = data.SysTimeStamp;
        buff->Width = data.Width;
        buff->Height = data.Height;
        buff->Fps = data.Fps;
        buff->Gain = data.Gain;
        buff->Exp = data.Exp;
        buff->Format = data.Format;
        buff->isSync = data.isSync;
        bq->DataCount++;
        if (bq->DataCount > 3)
        {
            DebugWarn("%s:Buffer data count=%d\n", bq->name, bq->DataCount);
        }
        //  DebugDbg("%s:buffer Data count=%d \n", bq->name, bq->DataCount);
        __db_list_put_tail(bq->ListFull, buff);
        pthread_cond_signal(&bq->cond);
        ret = 0;
    }
    pthread_mutex_unlock(&bq->mutex);
    return ret;
}

BuffFrameInfo_t *ImageQueueGetEmpytBuff(BuffQ_t *bq)
{
    BuffFrameInfo_t *buff = NULL;

    if (!bq)
    {
        return NULL;
    }

    pthread_mutex_lock(&bq->mutex);
    if (!is_list_empty(bq->ListEmpty))
    {
        buff = (BuffFrameInfo_t *)__db_list_pop(bq->ListEmpty);
    }
    pthread_mutex_unlock(&bq->mutex);

    return buff;
}

int ImageQueuePushBuffToList(BuffQ_t *bq, BuffFrameInfo_t *data)
{
    if (!bq)
    {
        return -1;
    }

    pthread_mutex_lock(&bq->mutex);
    bq->DataCount++;
    // DebugDbg("%s:buffer Data count=%d \n", bq->name, bq->DataCount);
    __db_list_put_tail(bq->ListFull, data);
    pthread_cond_signal(&bq->cond);
    pthread_mutex_unlock(&bq->mutex);

    return 0;
}

BuffFrameInfo_t *ImageQueueGetDataBuff(BuffQ_t *bq, int mode, uint32_t timeout_ms)
{
    return (BuffFrameInfo_t *)BuffQueueGetDataBuff(bq, mode, timeout_ms);
}

int ImageQueueReleaseDataBuff(BuffQ_t *bq, BuffFrameInfo_t *data)
{
    return BuffQueueReleaseDataBuff(bq, data);
}

// int ImageQueuePutDataToHead(BuffQ_t *bq, BuffFrameInfo_t *data)
// {
//     return BuffQueuePutDataToHead(bq, data);
// }

// BuffFrameInfo_t *ImageBuffQueueGetHeadData(BuffQ_t *bq, int mode)
// {
//     return (BuffFrameInfo_t *)BuffQueueGetHeadData(bq, mode);
// }

void ImageBuffQueueClearAll(BuffQ_t *bq)
{
    do
    {
        BuffFrameInfo_t *buff = ImageQueueGetDataBuff(bq, 0, 0);
        if (!buff)
        {
            break;
        }
        ImageQueueReleaseDataBuff(bq, buff);
    } while (1);
}

void ImageBuffSetDefaultValue(BuffQ_t *bq, char value)
{
    do
    {
        BuffFrameInfo_t *buff = ImageQueueGetEmpytBuff(bq);
        if (!buff)
        {
            break;
        }
        memset(buff->FrameY, value, buff->Yszie);
        memset(buff->FrameUV, value, buff->UVszie);

        ImageQueuePushBuffToList(bq, buff);

    } while (1);

    ImageBuffQueueClearAll(bq);
}
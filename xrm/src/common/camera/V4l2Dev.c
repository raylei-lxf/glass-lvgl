//
// Created by raylei on 1/19/23.
//

#include <linux/uvcvideo.h>
#include "V4l2Dev.h"

static  int fd;
static char DevName[64];
static struct v4l2_streamparm param;
static struct v4l2_capability cap;
static struct v4l2_fmtdesc fmtdesc;
static  struct v4l2_format fmt;
static  struct v4l2_requestbuffers req;
struct v4l2_buffer buf;
static  enum v4l2_buf_type type;
static unsigned int n_buffers;
static unsigned int fps;

static  unsigned char *buffer[IMG_BUFF_NUM];
static unsigned int length;
static   int isSuccessful;

void V4l2CreateVideo(char *devName, int w, int h, int fps)
{
    isSuccessful = -1;

    if (!devName)
    {
        return;
    }
    if ((fd = open(devName, O_RDWR)) < 0)
    {
        DebugErr("open %s failed!!!\n", devName);
        fd = -1;
        return;
    }

    DebugInfo("devName = %s\n", devName);
    memset(DevName, 0, sizeof(DevName));
    memcpy(DevName, devName, strlen(devName));

    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
    { // 查询视频设备的功能
        DebugErr("unable Querying Capabilities\n");
        goto FAILED;
    }

    fmtdesc.index = 0;
    fmtdesc.type = V4L2_VIDEO_TYPE;
    DebugInfo("Support format: \n");
    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)
    { // 获取当前视频设备支持的视频格式
        DebugInfo("\t%d. %s\n", fmtdesc.index + 1, fmtdesc.description);
        fmtdesc.index++;
    }
    // set fmt
    fmt.type = V4L2_VIDEO_TYPE;
    fmt.fmt.pix.width = w;
    fmt.fmt.pix.height = h;
    fmt.fmt.pix.pixelformat = V4L2_FORMAT; //*************************V4L2_PIX_FMT_YUYV V4L2_PIX_FMT_MJPEG****************可以选择
    fmt.fmt.pix.field = V4L2_FIELD_NONE;

    if (V4L2_FORMAT == V4L2_PIX_FMT_MJPEG)
    {
        DebugInfo("v4l2 format = V4L2_PIX_FMT_MJPEG\n");
    }
    else
    {
        DebugInfo("v4l2 format = V4L2_PIX_FMT_YUYV\n");
    }

    // 设置视频设备的视频数据格式，例如设置视频图像数据的长、宽，图像格式（JPEG、YUYV格式）
    if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
    {
        DebugErr("Setting Pixel Format error\n");
        goto FAILED;
    }

    if (ioctl(fd, VIDIOC_G_FMT, &fmt) == -1)
    { // 获取图像格式
        DebugErr("Unable to get format\n");
        goto FAILED;
    }

    struct v4l2_streamparm Stream_Parm;
    memset(&Stream_Parm, 0, sizeof(Stream_Parm));
    Stream_Parm.type = V4L2_VIDEO_TYPE;
    Stream_Parm.parm.capture.timeperframe.denominator = fps;
    Stream_Parm.parm.capture.timeperframe.numerator = 1;
    ioctl(fd, VIDIOC_S_PARM, &Stream_Parm);
    ioctl(fd, VIDIOC_G_PARM, &Stream_Parm);
    DebugInfo("fps=%d\n", Stream_Parm.parm.capture.timeperframe.denominator);

    req.count = IMG_BUFF_NUM;
    req.type = V4L2_VIDEO_TYPE;
    req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) // 开启内存映射或用户指针I/O
    {
        DebugErr("Requesting Buffer error\n");
        goto FAILED;
    }

    for (n_buffers = 0; n_buffers < req.count; n_buffers++)
    {
        // struct v4l2_buffer buf = {0};
        memset(&buf, 0, sizeof(buf));
        buf.type = V4L2_VIDEO_TYPE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;

        if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1)
        { // 查询已经分配的V4L2的视频缓冲区的相关信息，包括视频缓冲区的使用状态、在内核空间的偏移地址、缓冲区长度等。
            DebugErr("Querying Buffer error\n");
            goto FAILED;
        }

        buffer[n_buffers] = (unsigned char *)mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        if (buffer[n_buffers] == MAP_FAILED)
        {
            DebugErr("buffer map error\n");
            goto FAILED;
        }
        length = buf.length;
        // DebugInfo("Length: %d\nAddress: %p\n", buf.length, buffer[n_buffers]);
        // DebugInfo("Image Length: %d\n", buf.bytesused);
    }
    // 6 queue
    for (n_buffers = 0; n_buffers < req.count; n_buffers++)
    {
        buf.index = n_buffers;
        buf.type = V4L2_VIDEO_TYPE;
        buf.memory = V4L2_MEMORY_MMAP;
        if (ioctl(fd, VIDIOC_QBUF, &buf))
        {
            DebugErr("query buffer error\n");
            goto FAILED;
        }
    }
    isSuccessful = 0;

    return;
FAILED:

    close(fd);
    fd = -1;
    return;
}

void V4l2DestroyVideo()
{
    if (fd < 0)
    {
        return;
    }

    type = V4L2_VIDEO_TYPE;
    ioctl(fd, VIDIOC_STREAMOFF, &type);

   // V4l2ClearAllFrame();
    for (n_buffers = 0; n_buffers < req.count; n_buffers++)
    {
        munmap(buffer[n_buffers], length);
    }
    close(fd);
    fd = -1;
}

unsigned char *V4l2GetFrame()
{
    struct timeval timeout;
    fd_set fdsr;
    int ret;

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    FD_ZERO(&fdsr);
    FD_SET(fd, &fdsr);

    ret = select(fd + 1, &fdsr, NULL, NULL, &timeout);
    if (ret == 0)
    {
        DebugErr("%s:select timeout!!!\n", DevName);
        return NULL;
    }
    if (ret < 0)
    {
        DebugErr("%s:select error!!!\n", DevName);
        return NULL;
    }

    buf.type = V4L2_VIDEO_TYPE;
    buf.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_DQBUF, &buf) < 0)
    {
        DebugErr("%s:VIDIOC_DQBUF error!!!\n", DevName);
        return NULL;
    }

    length = buf.bytesused;
    // printf("Image Length: %d\n", buf.bytesused);
    //    	struct timeval stamp;
    //	stamp = buf.timestamp;
    //	printf("<%s %d>: timeStamp = %d %d\n",  __func__, __LINE__ , stamp.tv_sec, stamp.tv_usec);
    // printf("<%s %d>: buf.index = %d len=%d\n",  __func__, __LINE__ , buf.index, fmt.fmt.pix.sizeimage);
    return buffer[buf.index];
}

struct timeval V4l2GetTimeStamp()
{
    return buf.timestamp;
}

void V4l2ReleaseFrame()
{
    buf.type = V4L2_VIDEO_TYPE;
    buf.memory = V4L2_MEMORY_MMAP;
    ioctl(fd, VIDIOC_QBUF, &buf);
}
void V4l2ClearAllFrame()
{
    for (n_buffers = 0; n_buffers < req.count; n_buffers++)
    {
        buf.index = n_buffers;
        buf.type = V4L2_VIDEO_TYPE;
        buf.memory = V4L2_MEMORY_MMAP;

        ioctl(fd, VIDIOC_DQBUF, &buf);
        ioctl(fd, VIDIOC_QBUF, &buf);
    }
}

int V4l2Start()
{
    type = V4L2_VIDEO_TYPE;
    if (ioctl(fd, VIDIOC_STREAMON, &type) == -1)
    {
        DebugErr("%s:stream on error\n", DevName);
        return -1;
    }
    return 0;
}

void V4l2Stop()
{
    type = V4L2_VIDEO_TYPE;
    if (ioctl(fd, VIDIOC_STREAMOFF, &type) == -1)
    {
        DebugErr("%s:stream on error\n", DevName);
    }
}

unsigned int V4l2GetFps()
{
    struct v4l2_streamparm Stream_Parm;

    if (fd < 0)
    {
        return -1;
    }

    memset(&Stream_Parm, 0, sizeof(Stream_Parm));
    Stream_Parm.type = V4L2_VIDEO_TYPE;
    if (ioctl(fd, VIDIOC_G_PARM, &Stream_Parm) == -1)
    {
        return -1;
    }

    return Stream_Parm.parm.capture.timeperframe.denominator;
}
unsigned int V4l2GetWidth()
{
    return fmt.fmt.pix.width;
}
unsigned int V4l2GetHeight()
{
    return fmt.fmt.pix.height;
}
unsigned int V4l2GetFrameLen()
{
    return length;
}

unsigned int V4l2GetFormat()
{
    return fmt.fmt.pix.pixelformat;
}

// void main()
// {
//     V4l2CreateVideo("/dev/video0", 640, 480, 60);
// 	V4l2Start();
    
//     while(1)
//     {
// 		unsigned char *frame_addr= V4l2GetFrame();
// 		if(!frame_addr)
// 		{
// 			continue;
// 		}
// 		uint32_t frame_len = V4l2GetFrameLen();
		
// 		printf("frame_len=%d\n", frame_len);
		
// 		V4l2ReleaseFrame();
//     }
//     V4l2DestroyVideo();
// }
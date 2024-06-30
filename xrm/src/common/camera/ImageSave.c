//
// Created by raylei on 2/1/23.
//

#include "ImageSave.h"
#include "sys/stat.h"
#include "sys/types.h"

static char FileName[8][128] = {0};

static char *getFileName(int index, const char *format, uint64_t timeStamp)
{
    char *file_name = FileName[index];

    memset(file_name, 0, 128);
    sprintf(file_name, "/tmp/sensor%d", index);
    if (access(file_name, F_OK) != 0)
    {
        mkdir(file_name, 666);
    }

    sprintf(file_name, "%s/%s", file_name, format);
    if (access(file_name, F_OK) != 0)
    {
        mkdir(file_name, 666);
    }
    sprintf(file_name, "%s/%ld.%s", file_name, timeStamp, format);

    // sprintf(file_name, "/tmp/%s/%ld.%s", format, timeStamp,format);
    printf("%s\n", file_name);

    return file_name;
}

static void systemCache()
{
    int ret;

    ret = system("echo 1 > /proc/sys/vm/drop_caches");
    if (ret)
    {
    }
}

void ImageSaveFile(int index, char *frame, unsigned int len, const char *format, uint64_t timeStamp)
{
    static uint32_t frame_counter = 0;
    char *file_name = FileName[index];
    FILE *fid;
    int ret;

    getFileName(index, format, timeStamp);

    fid = fopen(file_name, "w+");
    fflush(stdout);
    ret = fwrite(frame, 1, len, fid);
    if (ret)
    {
    }
    fflush(fid);
    frame_counter++;

    if (frame_counter > 10)
    {
        systemCache();
        frame_counter = 0;
    }
    fclose(fid);
}

void yuvSaveFile(int index, char *y, char *uv, unsigned int y_size, unsigned int uv_size, uint64_t timeStamp)
{
    static uint32_t frame_counter = 0;
    char *file_name = FileName[index];
    FILE *fid;
    int ret;

    getFileName(index, "yuv", timeStamp);

    fid = fopen(file_name, "w+");
    fflush(stdout);
    ret = fwrite(y, 1, y_size, fid);
    if (ret)
    {
    }
    if (uv)
    {
        fwrite(uv, 1, uv_size, fid);
    }

    fflush(fid);
    frame_counter++;

    if (frame_counter > 10)
    {
        systemCache();
        frame_counter = 0;
    }
    fclose(fid);
}

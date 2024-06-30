//
// Created by raylei on 2/1/23.
//

#ifndef SAMPLE_ORBBEC_IMAGESAVE_H
#define SAMPLE_ORBBEC_IMAGESAVE_H

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

void ImageSaveFile(int index, char *frame, unsigned int len, const char *format, uint64_t timeStamp);

void yuvSaveFile(int index, char *y, char *uv, unsigned int y_size, unsigned int uv_size, uint64_t timeStamp);
#endif //SAMPLE_ORBBEC_IMAGESAVE_H

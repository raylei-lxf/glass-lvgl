#ifndef __MAL_IMAGE_H__
#define __MAL_IMAGE_H__
#include "lv_common.h"


void *mal_load_image(char *path);
int mal_unload_image(void *dec);

lv_img_dsc_t *resize_image(const lv_img_dsc_t* src, int dst_width, int dst_height);
#endif


#ifndef __MAL_IMAGE_H__
#define __MAL_IMAGE_H__
#include "lv_common.h"

void *mal_load_image(char *path);
int mal_unload_image(void *dec);

#endif


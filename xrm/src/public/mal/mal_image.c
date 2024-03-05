#include "mal_image.h"
#include "lv_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


typedef struct {
    uint8_t r, g, b, a;
} PixelRGBA;

unsigned char *stbi_convert_rb(unsigned char *data, int w, int h, int Bpp)
{
	int i, j;
	unsigned char *buf;
	unsigned char tmp;
	
	buf = (unsigned char *)data;
	for(i=0; i<h; i++)
	{
		for(j=0; j<w; j++)
		{
			tmp = buf[2];
			buf[2] = buf[0];	// R
			buf[0] = tmp;		// B
			buf += 4;
 		}
	}
	return data;
}

void *mal_load_image(char *path)
{
	int w, h, n;
  	lv_img_dsc_t *dsc = NULL;
	unsigned char *data = NULL;
	
	dsc = (lv_img_dsc_t *)malloc(sizeof(lv_img_dsc_t));
	if(NULL == dsc) {
		com_info("\n");
		goto err;
	}
	memset(dsc, 0, sizeof(lv_img_dsc_t));
	
	data = stbi_load(path, &w, &h, &n, 4);
	if(NULL == data) {
		com_info("\n");
		goto err;
	}
	data = stbi_convert_rb(data, w, h, 4);
	dsc->header.w = w;
	dsc->header.h = h;
	dsc->header.always_zero = 0;
	dsc->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
	dsc->data_size = w * h * 4;
	dsc->data = data;
	
	return dsc;
	
	err:
	if(data) {
		stbi_image_free(data);
	}
	if(dsc) {
		free(dsc);
	}
	return NULL;
}

int mal_unload_image(void *dsc)
{
	if(NULL == dsc) {
		return -1;
	}
	
	lv_img_dsc_t *img_dsc = (lv_img_dsc_t *)dsc;
	if(img_dsc->data) {
		stbi_image_free((void *)img_dsc->data);
	}
	if(img_dsc) {
		free(img_dsc);
	}

	return 0;
}

lv_img_dsc_t *resize_image(const lv_img_dsc_t* src, int dst_width, int dst_height) 
{

    float x_ratio = (float)src->header.w / dst_width;
    float y_ratio = (float)src->header.h / dst_height;

	lv_img_dsc_t *dst = (lv_img_dsc_t *)malloc(sizeof(lv_img_dsc_t));
	memset(dst, 0, sizeof(lv_img_dsc_t));
	
	dst->header.w = dst_width;
	dst->header.h = dst_height;
	dst->header.always_zero = 0;
	dst->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
	dst->data_size = dst_width * dst_height * 4;

	char *dstdata = malloc(dst->data_size);
	//memset(dstdata, 0xff, dst->data_size);
	dst->data = dstdata;

	PixelRGBA *src_rgba = src->data;
	PixelRGBA *dst_rgba = dstdata;

    for (int y = 0; y < dst_height; y++) {
        for (int x = 0; x < dst_width; x++) {
            int src_x = (int)(x * x_ratio);
            int src_y = (int)(y * y_ratio);
            dst_rgba[y * dst_width + x] = src_rgba[src_y * src->header.w + src_x];
        }
    }
	mal_unload_image(src);
	return dst;
}




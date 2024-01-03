#include "mal_image.h"
#include "lv_common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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


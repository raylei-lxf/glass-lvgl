	#ifndef  __PUBLIC_H__
#define  __PUBLIC_H__

#include "xrm_conf.h"
#include "mal_middle.h"
#include <time.h>
#include <sys/time.h>
#include "lvgl.h"

typedef struct IMG_SRC{
	void *bluetooth[2];
	void *tempurature[2];
	void *wifi[2];
	void *usb[2];
	void *cigar_out[2];
	void *ac_out[2];
	void *sloar_in[2];
	void *ext_batt[2];
	void *ac_in[2];
}IMG_SRC_T;

typedef struct NUM_BIT{
	int bit5;
	int thou;
	int hund;
	int ten;
	int bits;
}NUM_BIT_T;

void system_sleep(void);

float get_diff_time(struct timespec * start , bool update);
void ui_num_zero_hide(lv_obj_t *obj, int value);
NUM_BIT_T get_num_bit(int value);
void lv_img_update_src(lv_obj_t * img, const void * src_img);
void ui_select_img(lv_obj_t *obj, char state, char *img[2]);
void ui_set_num_show(lv_obj_t *obj[4], unsigned int value, void *img[]);
void ui_lable_set_font(lv_obj_t *lable, const lv_font_t *font);
void ui_set_time_lable(lv_obj_t *lable, uint32_t h, uint32_t m);
void ui_set_lable(lv_obj_t *lable, uint8_t *str);
void ui_set_hidden(lv_obj_t * obj, bool en);

void lcd_mode_set(int mode, int lcd_time);

typedef void (*key_callback)(void);
void key_callback_register(lv_key_nj_t key_num, key_callback func);
void key_callback_unregister(void);
void recovery_callback_register(void);
void key_mode_set(int key_num, int mode);

#if 0
LV_FONT_DECLARE(microsoft_halvetica_20_4);
LV_FONT_DECLARE(microsoft_halvetica_24_4);
LV_FONT_DECLARE(microsoft_halvetica_28_4);
LV_FONT_DECLARE(microsoft_halvetica_32_4);
LV_FONT_DECLARE(microsoft_halvetica_36_4);
LV_FONT_DECLARE(microsoft_halvetica_48_4);
LV_FONT_DECLARE(microsoft_halvetica_64_4);


LV_FONT_DECLARE(microsoft_din_condensed_24_4);
LV_FONT_DECLARE(microsoft_din_condensed_28_4);
LV_FONT_DECLARE(microsoft_din_condensed_32_4);


LV_FONT_DECLARE(microsoft_helvetica_bold_54_4);	
#endif

#endif


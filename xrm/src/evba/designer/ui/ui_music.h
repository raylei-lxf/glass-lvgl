#ifndef __UI_MUSIC_H__
#define __UI_MUSIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*    includes
******************************************************************************/
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	lv_obj_t *parent;
	lv_obj_t *cont_main;
	lv_obj_t *cont_1;
	lv_obj_t *cont_music_list;
	lv_obj_t *cont_music_process;
	lv_obj_t *cont_music_process_bak;
	lv_obj_t *label_music_start;
	lv_obj_t *label_music_totle;
	lv_obj_t *label_music;
	lv_obj_t *img_xunhuan;
	lv_obj_t *cont_2;
	lv_obj_t *cont_3;
	lv_obj_t *cont_4;
	lv_obj_t *cont_5;
	lv_obj_t *cont_6;
	lv_obj_t *cont_7;
	lv_obj_t *cont_8;
	lv_obj_t *cont_9;
	lv_obj_t *cont_10;
	lv_obj_t *cont_11;
	lv_obj_t *cont_12;
	lv_obj_t *cont_13;
	lv_obj_t *cont_14;
	lv_obj_t *cont_15;
	lv_obj_t *cont_16;
	lv_obj_t *cont_17;
	lv_obj_t *cont_18;
	lv_obj_t *cont_19;
	lv_obj_t *cont_20;
	lv_obj_t *cont_30;
	lv_obj_t *cont_21;
	lv_obj_t *cont_22;
	lv_obj_t *cont_24;
	lv_obj_t *cont_25;
	lv_obj_t *cont_26;
	lv_obj_t *cont_31;
	lv_obj_t *cont_32;
	lv_obj_t *cont_33;
	lv_obj_t *cont_34;
	lv_obj_t *cont_23;
	lv_obj_t *list_mp3;
} music_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void music_ui_create(music_ui_t *ui);
void music_ui_destory(music_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

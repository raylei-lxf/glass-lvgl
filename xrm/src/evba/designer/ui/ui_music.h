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
	lv_obj_t *img_music_title;
	lv_obj_t *label_music_title;
	lv_obj_t *cont_music_process;
	lv_obj_t *cont_music_process_bak;
	lv_obj_t *label_music_start;
	lv_obj_t *label_music_totle;
	lv_obj_t *cont_5;
	lv_obj_t *img_2;
	lv_obj_t *label_4;
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

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
	lv_obj_t *label_music_start;
	lv_obj_t *cont_5;
	lv_obj_t *img_2;
	lv_obj_t *label_4;
	lv_obj_t *cont_music_1;
	lv_obj_t *cont_music_1_2;
	lv_obj_t *cont_music_1_3;
	lv_obj_t *cont_music_1_4;
	lv_obj_t *cont_music_1_5;
	lv_obj_t *cont_music_1_6;
	lv_obj_t *cont_music_1_7;
	lv_obj_t *cont_music_1_8;
	lv_obj_t *cont_music_1_9;
	lv_obj_t *cont_music_1_10;
	lv_obj_t *cont_music_1_11;
	lv_obj_t *cont_music_1_1;
	lv_obj_t *cont_music_2;
	lv_obj_t *cont_music_2_2;
	lv_obj_t *cont_music_2_3;
	lv_obj_t *cont_music_2_4;
	lv_obj_t *cont_music_2_5;
	lv_obj_t *cont_music_2_6;
	lv_obj_t *cont_music_2_7;
	lv_obj_t *cont_music_2_8;
	lv_obj_t *cont_music_2_9;
	lv_obj_t *cont_music_2_10;
	lv_obj_t *cont_music_2_11;
	lv_obj_t *cont_music_2_1;
	lv_obj_t *cont_music_3;
	lv_obj_t *cont_music_3_2;
	lv_obj_t *cont_music_3_3;
	lv_obj_t *cont_music_3_4;
	lv_obj_t *cont_music_3_5;
	lv_obj_t *cont_music_3_6;
	lv_obj_t *cont_music_3_7;
	lv_obj_t *cont_music_3_8;
	lv_obj_t *cont_music_3_9;
	lv_obj_t *cont_music_3_10;
	lv_obj_t *cont_music_3_11;
	lv_obj_t *cont_music_3_1;
	lv_obj_t *cont_music_4;
	lv_obj_t *cont_music_4_2;
	lv_obj_t *cont_music_4_3;
	lv_obj_t *cont_music_4_4;
	lv_obj_t *cont_music_4_5;
	lv_obj_t *cont_music_4_6;
	lv_obj_t *cont_music_4_7;
	lv_obj_t *cont_music_4_8;
	lv_obj_t *cont_music_4_9;
	lv_obj_t *cont_music_4_10;
	lv_obj_t *cont_music_4_11;
	lv_obj_t *cont_music_4_1;
	lv_obj_t *cont_music_5;
	lv_obj_t *cont_music_5_2;
	lv_obj_t *cont_music_5_3;
	lv_obj_t *cont_music_5_4;
	lv_obj_t *cont_music_5_5;
	lv_obj_t *cont_music_5_6;
	lv_obj_t *cont_music_5_7;
	lv_obj_t *cont_music_5_8;
	lv_obj_t *cont_music_5_9;
	lv_obj_t *cont_music_5_10;
	lv_obj_t *cont_music_5_11;
	lv_obj_t *cont_music_5_1;
	lv_obj_t *list_mp3;
	lv_obj_t *bar_music;
	lv_obj_t *label_music_totle;
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

#ifndef __UI_HOME_H__
#define __UI_HOME_H__

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
	lv_obj_t *img_player;
	lv_obj_t *label_player;
	lv_obj_t *img_photo;
	lv_obj_t *img_music;
	lv_obj_t *img_file;
	lv_obj_t *img_setting;
	lv_obj_t *img_phone;
	lv_obj_t *label_photo;
	lv_obj_t *label_music;
	lv_obj_t *label_file;
	lv_obj_t *label_setting;
	lv_obj_t *label_phone;
	lv_obj_t *cont_botton;
	lv_obj_t *label_vol;
	lv_obj_t *bar_vol_bag;
	lv_obj_t *bar_vol_blue;
	lv_obj_t *cont_tip;
	lv_obj_t *label_tip_title;
	lv_obj_t *cont_tip_line;
	lv_obj_t *img_tip;
	lv_obj_t *label_tip_content;
} home_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void home_ui_create(home_ui_t *ui);
void home_ui_destory(home_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

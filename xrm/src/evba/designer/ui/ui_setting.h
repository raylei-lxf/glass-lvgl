#ifndef __UI_SETTING_H__
#define __UI_SETTING_H__

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
	lv_obj_t *cont_setting_line;
	lv_obj_t *img_setting_title;
	lv_obj_t *label_setting_title;
	lv_obj_t *cont_setting_language;
	lv_obj_t *label_language_title;
	lv_obj_t *label_language;
	lv_obj_t *cont_setting_factory;
	lv_obj_t *label_factory;
	lv_obj_t *cont_upgrade;
	lv_obj_t *label_upgrade;
} setting_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void setting_ui_create(setting_ui_t *ui);
void setting_ui_destory(setting_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

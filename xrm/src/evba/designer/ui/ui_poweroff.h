#ifndef __UI_POWEROFF_H__
#define __UI_POWEROFF_H__

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
	lv_obj_t *label_tip_title;
	lv_obj_t *cont_tip_line;
	lv_obj_t *img_tip;
	lv_obj_t *label_tip_content;
} poweroff_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void poweroff_ui_create(poweroff_ui_t *ui);
void poweroff_ui_destory(poweroff_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

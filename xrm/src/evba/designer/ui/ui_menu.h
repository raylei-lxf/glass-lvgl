#ifndef __UI_MENU_H__
#define __UI_MENU_H__

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
	lv_obj_t *cont_botton;
	lv_obj_t *label_vol;
	lv_obj_t *bar_vol_bag;
	lv_obj_t *bar_vol_blue;
	lv_obj_t *label_val;
} menu_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void menu_ui_create(menu_ui_t *ui);
void menu_ui_destory(menu_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

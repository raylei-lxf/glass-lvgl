#ifndef __UI_ERR_TIP_H__
#define __UI_ERR_TIP_H__

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
	lv_obj_t *label_1;
} err_tip_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void err_tip_ui_create(err_tip_ui_t *ui);
void err_tip_ui_destory(err_tip_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

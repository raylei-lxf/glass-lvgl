#ifndef __UI_PHOTO_LIST_H__
#define __UI_PHOTO_LIST_H__

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
	lv_obj_t *list_photo;
	lv_obj_t *cont_1;
	lv_obj_t *img_1;
	lv_obj_t *label_1;
} photo_list_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void photo_list_ui_create(photo_list_ui_t *ui);
void photo_list_ui_destory(photo_list_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

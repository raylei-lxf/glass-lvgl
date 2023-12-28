#ifndef __UI_PHOTO_H__
#define __UI_PHOTO_H__

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
	lv_obj_t *img_photo_show;
	lv_obj_t *img_photo_ing;
	lv_obj_t *img_photo_line;
} photo_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void photo_ui_create(photo_ui_t *ui);
void photo_ui_destory(photo_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

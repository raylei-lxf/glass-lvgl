#ifndef __UI_FILE_STORE_H__
#define __UI_FILE_STORE_H__

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
	lv_obj_t *img_file_store_title;
	lv_obj_t *cont_file_store_line;
	lv_obj_t *label_file_store_title;
	lv_obj_t *cont_sd;
	lv_obj_t *label_sd;
	lv_obj_t *cont_u;
	lv_obj_t *label_usb;
} file_store_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void file_store_ui_create(file_store_ui_t *ui);
void file_store_ui_destory(file_store_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

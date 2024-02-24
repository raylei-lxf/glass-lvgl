#ifndef __UI_FILE_H__
#define __UI_FILE_H__

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
	lv_obj_t *cont_file_line;
	lv_obj_t *img_file_title;
	lv_obj_t *label_file_title;
	lv_obj_t *file_list;
} file_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void file_ui_create(file_ui_t *ui);
void file_ui_destory(file_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

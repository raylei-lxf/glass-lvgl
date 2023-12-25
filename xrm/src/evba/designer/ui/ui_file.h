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
	lv_obj_t *cont_file;
	lv_obj_t *cont_file_line;
	lv_obj_t *img_file_title;
	lv_obj_t *label_file_title;
	lv_obj_t *cont_file_photo;
	lv_obj_t *img_file_photo;
	lv_obj_t *label_file_photo;
	lv_obj_t *cont_file_imge;
	lv_obj_t *img_file_imge;
	lv_obj_t *label_file_imge;
	lv_obj_t *cont_file_video;
	lv_obj_t *img_file_video;
	lv_obj_t *label_file_video;
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

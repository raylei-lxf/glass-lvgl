#ifndef __UI_VIDEO_LIST_H__
#define __UI_VIDEO_LIST_H__

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
	lv_obj_t *list_video;
	lv_obj_t *cont_1;
	lv_obj_t *img_1;
	lv_obj_t *label_1;
} video_list_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void video_list_ui_create(video_list_ui_t *ui);
void video_list_ui_destory(video_list_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

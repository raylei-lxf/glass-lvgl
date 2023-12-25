#ifndef __UI_PLAYER_H__
#define __UI_PLAYER_H__

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
	lv_obj_t *bar_player_pro;
	lv_obj_t *label_player_start;
	lv_obj_t *label_player_total;
	lv_obj_t *label_1;
} player_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void player_ui_create(player_ui_t *ui);
void player_ui_destory(player_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

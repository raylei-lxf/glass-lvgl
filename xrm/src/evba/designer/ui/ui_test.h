#ifndef __UI_TEST_H__
#define __UI_TEST_H__

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
	lv_obj_t *btn_back_home;
	lv_obj_t *img_back_home;
	lv_obj_t *label_1;
	lv_obj_t *img_1;
	lv_obj_t *img_4;
} test_ui_t;


/******************************************************************************
*    functions
******************************************************************************/
void test_ui_create(test_ui_t *ui);
void test_ui_destory(test_ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif

/******************************************************************************
*    includes
******************************************************************************/
#include "ui_test.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_btn_back_home;
static lv_style_t style1_btn_back_home;
static lv_style_t style0_img_back_home;


/******************************************************************************
*    functions
******************************************************************************/
void test_ui_create(test_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0xf4f4f4);
	style0_cont_main.body.grad_color = lv_color_hex(0xf4f4f4);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.border.width = 1;

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_BTN
	lv_style_copy(&style0_btn_back_home, &lv_style_btn_rel);
	style0_btn_back_home.body.main_color = lv_color_hex(0xf4f4f4);
	style0_btn_back_home.body.grad_color = lv_color_hex(0xf4f4f4);
	style0_btn_back_home.body.border.width = 1;
	style0_btn_back_home.body.border.opa = 100;

	lv_style_copy(&style1_btn_back_home, &lv_style_btn_pr);
	style1_btn_back_home.body.main_color = lv_color_hex(0xffffff);
	style1_btn_back_home.body.grad_color = lv_color_hex(0xffffff);
	style1_btn_back_home.body.border.width = 1;

	ui->btn_back_home = lv_btn_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->btn_back_home, 0, 0);
	lv_obj_set_size(ui->btn_back_home, 78, 35);
	lv_btn_set_style(ui->btn_back_home, LV_BTN_STYLE_REL, &style0_btn_back_home);
	lv_btn_set_style(ui->btn_back_home, LV_BTN_STYLE_PR, &style1_btn_back_home);
#endif // LV_USE_BTN

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_back_home, &lv_style_plain);
	style0_img_back_home.image.intense = 255;

	ui->img_back_home = lv_img_create(ui->btn_back_home, NULL);
	lv_obj_set_pos(ui->img_back_home, 34, 8);
	lv_obj_set_size(ui->img_back_home, 10, 19);
	lv_img_set_src(ui->img_back_home, LV_SYMBOL_LEFT);
	lv_img_set_style(ui->img_back_home, LV_IMG_STYLE_MAIN, &style0_img_back_home);
#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_1 = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_1, "Text");
	lv_label_set_long_mode(ui->label_1, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_1, 202, 140);
	lv_obj_set_size(ui->label_1, 36, 22);
#endif // LV_USE_LABEL

#ifdef LV_USE_IMG
	ui->img_1 = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_1, 161, 48);
	lv_obj_set_size(ui->img_1, 70, 44);
#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	ui->img_4 = lv_img_create(ui->img_1, NULL);
	lv_obj_set_pos(ui->img_4, 0, 0);
	lv_obj_set_size(ui->img_4, 70, 44);
#endif // LV_USE_IMG

}

void test_ui_destory(test_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

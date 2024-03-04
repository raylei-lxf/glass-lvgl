/******************************************************************************
*    includes
******************************************************************************/
#include "ui_menu.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_cont_botton;
static lv_style_t style0_label_vol;
static lv_style_t style0_bar_vol_bag;
static lv_style_t style0_bar_vol_blue;
static lv_style_t style0_label_val;


/******************************************************************************
*    functions
******************************************************************************/
void menu_ui_create(menu_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0xf4f4f4);
	style0_cont_main.body.grad_color = lv_color_hex(0xf4f4f4);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.opa = 0;
	style0_cont_main.body.border.width = 1;
	style0_cont_main.body.border.opa = 0;

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_botton, &lv_style_pretty);
	style0_cont_botton.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_botton.body.radius = 0;
	style0_cont_botton.body.border.color = lv_color_hex(0xffffff);
	style0_cont_botton.body.shadow.color = lv_color_hex(0xffffff);

	ui->cont_botton = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_botton, 0, 325);
	lv_obj_set_size(ui->cont_botton, 473, 33);
	lv_cont_set_fit4(ui->cont_botton, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_botton, LV_CONT_STYLE_MAIN, &style0_cont_botton);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_vol, &lv_style_transp);
	style0_label_vol.text.color = lv_color_hex(0x444444);
	style0_label_vol.text.line_space = 2;

	ui->label_vol = lv_label_create(ui->cont_botton, NULL);
	lv_label_set_text(ui->label_vol, "VOL");
	lv_label_set_long_mode(ui->label_vol, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_vol, 20, 8);
	lv_obj_set_size(ui->label_vol, 54, 22);
	lv_label_set_style(ui->label_vol, LV_LABEL_STYLE_MAIN, &style0_label_vol);
#endif // LV_USE_LABEL

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_vol_bag, &lv_style_pretty);
	style0_bar_vol_bag.body.main_color = lv_color_hex(0x3244b5);
	style0_bar_vol_bag.body.grad_color = lv_color_hex(0x3244b5);
	style0_bar_vol_bag.body.radius = 0;
	style0_bar_vol_bag.body.opa = 0;
	style0_bar_vol_bag.body.border.color = lv_color_hex(0x3244b5);
	style0_bar_vol_bag.body.border.opa = 255;
	style0_bar_vol_bag.body.shadow.color = lv_color_hex(0xcccccc);

	ui->bar_vol_bag = lv_bar_create(ui->cont_botton, NULL);
	lv_obj_set_pos(ui->bar_vol_bag, 118, 6);
	lv_obj_set_size(ui->bar_vol_bag, 248, 21);
	lv_bar_set_range(ui->bar_vol_bag, 0, 100);
	lv_bar_set_value(ui->bar_vol_bag, 100, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_vol_bag, LV_BAR_STYLE_BG, &style0_bar_vol_bag);
#endif // LV_USE_BAR

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_vol_blue, &lv_style_pretty);
	style0_bar_vol_blue.body.main_color = lv_color_hex(0xcccccc);
	style0_bar_vol_blue.body.grad_color = lv_color_hex(0xcccccc);
	style0_bar_vol_blue.body.radius = 0;
	style0_bar_vol_blue.body.border.color = lv_color_hex(0xcccccc);
	style0_bar_vol_blue.body.border.opa = 255;

	ui->bar_vol_blue = lv_bar_create(ui->bar_vol_bag, NULL);
	lv_obj_set_pos(ui->bar_vol_blue, 0, 0);
	lv_obj_set_size(ui->bar_vol_blue, 248, 21);
	lv_bar_set_range(ui->bar_vol_blue, 0, 100);
	lv_bar_set_value(ui->bar_vol_blue, 60, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_vol_blue, LV_BAR_STYLE_BG, &style0_bar_vol_blue);
#endif // LV_USE_BAR

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_val, &lv_style_transp);
	style0_label_val.text.color = lv_color_hex(0x444444);
	style0_label_val.text.line_space = 2;

	ui->label_val = lv_label_create(ui->cont_botton, NULL);
	lv_label_set_text(ui->label_val, "100");
	lv_label_set_long_mode(ui->label_val, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_val, 388, 7);
	lv_obj_set_size(ui->label_val, 69, 22);
	lv_label_set_style(ui->label_val, LV_LABEL_STYLE_MAIN, &style0_label_val);
#endif // LV_USE_LABEL

}

void menu_ui_destory(menu_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

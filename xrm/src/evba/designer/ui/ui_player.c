/******************************************************************************
*    includes
******************************************************************************/
#include "ui_player.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_bar_player_pro;
static lv_style_t style0_label_1;


/******************************************************************************
*    functions
******************************************************************************/
void player_ui_create(player_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.opa = 0;
	style0_cont_main.body.border.width = 1;

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_player_pro, &lv_style_pretty);
	style0_bar_player_pro.body.grad_color = lv_color_hex(0xffffff);
	style0_bar_player_pro.body.radius = 0;

	ui->bar_player_pro = lv_bar_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->bar_player_pro, 25, 342);
	lv_obj_set_size(ui->bar_player_pro, 438, 6);
	lv_bar_set_range(ui->bar_player_pro, 0, 100);
	lv_bar_set_value(ui->bar_player_pro, 0, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_player_pro, LV_BAR_STYLE_BG, &style0_bar_player_pro);
#endif // LV_USE_BAR

#ifdef LV_USE_LABEL
	ui->label_player_start = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_player_start, "00:16");
	lv_label_set_long_mode(ui->label_player_start, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player_start, 26, 312);
	lv_obj_set_size(ui->label_player_start, 125, 31);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	ui->label_player_total = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_player_total, "02:58");
	lv_label_set_long_mode(ui->label_player_total, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player_total, 340, 306);
	lv_obj_set_size(ui->label_player_total, 125, 31);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_1, &lv_style_transp);
	style0_label_1.text.font = &lv_font_roboto_28;
	style0_label_1.text.line_space = 2;

	ui->label_1 = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_1, "Text.mp4");
	lv_label_set_long_mode(ui->label_1, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_1, 23, 33);
	lv_obj_set_size(ui->label_1, 386, 40);
	lv_label_set_style(ui->label_1, LV_LABEL_STYLE_MAIN, &style0_label_1);
#endif // LV_USE_LABEL

}

void player_ui_destory(player_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

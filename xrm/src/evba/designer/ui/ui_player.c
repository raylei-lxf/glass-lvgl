/******************************************************************************
*    includes
******************************************************************************/
#include "ui_player.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_player;
static lv_style_t style0_bar_player_pro;
static lv_style_t style0_bar_player_pro_bak;
static lv_style_t style0_bar_3;
static lv_style_t style0_bar_4;
static lv_style_t style0_label_player_start;
static lv_style_t style0_label_player_total;


/******************************************************************************
*    functions
******************************************************************************/
void player_ui_create(player_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_player, &lv_style_pretty);
	style0_cont_player.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_player.body.radius = 0;
	style0_cont_player.body.border.width = 1;

	ui->cont_player = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_player, 0, 0);
	lv_obj_set_size(ui->cont_player, 480, 360);
	lv_cont_set_fit4(ui->cont_player, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_player, LV_CONT_STYLE_MAIN, &style0_cont_player);
#endif // LV_USE_CONT

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_player_pro, &lv_style_pretty);
	style0_bar_player_pro.body.grad_color = lv_color_hex(0xffffff);
	style0_bar_player_pro.body.radius = 0;

	ui->bar_player_pro = lv_bar_create(ui->cont_player, NULL);
	lv_obj_set_pos(ui->bar_player_pro, 25, 342);
	lv_obj_set_size(ui->bar_player_pro, 438, 6);
	lv_bar_set_range(ui->bar_player_pro, 0, 100);
	lv_bar_set_value(ui->bar_player_pro, 0, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_player_pro, LV_BAR_STYLE_BG, &style0_bar_player_pro);
#endif // LV_USE_BAR

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_player_pro_bak, &lv_style_pretty);
	style0_bar_player_pro_bak.body.grad_color = lv_color_hex(0xffffff);
	style0_bar_player_pro_bak.body.radius = 0;

	ui->bar_player_pro_bak = lv_bar_create(ui->bar_player_pro, NULL);
	lv_obj_set_pos(ui->bar_player_pro_bak, 24, 342);
	lv_obj_set_size(ui->bar_player_pro_bak, 438, 6);
	lv_bar_set_range(ui->bar_player_pro_bak, 0, 100);
	lv_bar_set_value(ui->bar_player_pro_bak, 0, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_player_pro_bak, LV_BAR_STYLE_BG, &style0_bar_player_pro_bak);
#endif // LV_USE_BAR

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_3, &lv_style_pretty);
	style0_bar_3.body.main_color = lv_color_hex(0xffff00);
	style0_bar_3.body.grad_color = lv_color_hex(0xffff00);
	style0_bar_3.body.radius = 0;
	style0_bar_3.body.border.color = lv_color_hex(0xffff00);
	style0_bar_3.body.border.width = 0;

	ui->bar_3 = lv_bar_create(ui->bar_player_pro, NULL);
	lv_obj_set_pos(ui->bar_3, 25, 342);
	lv_obj_set_size(ui->bar_3, 438, 6);
	lv_bar_set_range(ui->bar_3, 0, 100);
	lv_bar_set_value(ui->bar_3, 40, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_3, LV_BAR_STYLE_BG, &style0_bar_3);
#endif // LV_USE_BAR

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_4, &lv_style_pretty);
	style0_bar_4.body.grad_color = lv_color_hex(0xffffff);
	style0_bar_4.body.radius = 0;

	ui->bar_4 = lv_bar_create(ui->bar_3, NULL);
	lv_obj_set_pos(ui->bar_4, 24, 342);
	lv_obj_set_size(ui->bar_4, 438, 6);
	lv_bar_set_range(ui->bar_4, 0, 100);
	lv_bar_set_value(ui->bar_4, 0, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_4, LV_BAR_STYLE_BG, &style0_bar_4);
#endif // LV_USE_BAR

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_player_start, &lv_style_transp);

	ui->label_player_start = lv_label_create(ui->cont_player, NULL);
	lv_label_set_text(ui->label_player_start, "00:16");
	lv_label_set_long_mode(ui->label_player_start, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player_start, 26, 312);
	lv_obj_set_size(ui->label_player_start, 125, 31);
	lv_label_set_style(ui->label_player_start, LV_LABEL_STYLE_MAIN, &style0_label_player_start);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_player_total, &lv_style_transp);

	ui->label_player_total = lv_label_create(ui->cont_player, NULL);
	lv_label_set_text(ui->label_player_total, "02:58");
	lv_label_set_long_mode(ui->label_player_total, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player_total, 340, 306);
	lv_obj_set_size(ui->label_player_total, 125, 31);
	lv_label_set_style(ui->label_player_total, LV_LABEL_STYLE_MAIN, &style0_label_player_total);
#endif // LV_USE_LABEL

}

void player_ui_destory(player_ui_t *ui)
{
	lv_obj_del(ui->cont_player);
}

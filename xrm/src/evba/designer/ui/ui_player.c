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
static lv_style_t style0_cont_par;
static lv_style_t style0_label_player_total;
static lv_style_t style0_bar_player_pro;


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

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_par, &lv_style_pretty);
	style0_cont_par.body.opa = 0;
	style0_cont_par.body.border.opa = 0;

	ui->cont_par = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_par, 0, 325);
	lv_obj_set_size(ui->cont_par, 480, 35);
	lv_cont_set_fit4(ui->cont_par, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_par, LV_CONT_STYLE_MAIN, &style0_cont_par);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	ui->label_1 = lv_label_create(ui->cont_par, NULL);
	lv_label_set_text(ui->label_1, "00:16");
	lv_label_set_long_mode(ui->label_1, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_1, 13, 0);
	lv_obj_set_size(ui->label_1, 48, 22);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_player_total, &lv_style_transp);

	ui->label_player_total = lv_label_create(ui->cont_par, NULL);
	lv_label_set_text(ui->label_player_total, "02:58");
	lv_label_set_long_mode(ui->label_player_total, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player_total, 415, 0);
	lv_obj_set_size(ui->label_player_total, 50, 25);
	lv_label_set_style(ui->label_player_total, LV_LABEL_STYLE_MAIN, &style0_label_player_total);
#endif // LV_USE_LABEL

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_player_pro, &lv_style_pretty);
	style0_bar_player_pro.body.grad_color = lv_color_hex(0xffffff);
	style0_bar_player_pro.body.radius = 0;

	ui->bar_player_pro = lv_bar_create(ui->cont_par, NULL);
	lv_obj_set_pos(ui->bar_player_pro, 17, 20);
	lv_obj_set_size(ui->bar_player_pro, 438, 6);
	lv_bar_set_range(ui->bar_player_pro, 0, 100);
	lv_bar_set_value(ui->bar_player_pro, 0, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_player_pro, LV_BAR_STYLE_BG, &style0_bar_player_pro);
#endif // LV_USE_BAR

}

void player_ui_destory(player_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

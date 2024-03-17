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
static lv_style_t style0_label_player_current;
static lv_style_t style0_label_player_total;
static lv_style_t style0_bar_video;
static lv_style_t style1_bar_video;


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
	lv_obj_set_pos(ui->cont_par, 0, 305);
	lv_obj_set_size(ui->cont_par, 480, 55);
	lv_cont_set_fit4(ui->cont_par, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_par, LV_CONT_STYLE_MAIN, &style0_cont_par);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_player_current, &lv_style_transp);
	style0_label_player_current.text.color = lv_color_hex(0xe4e4e4);
	style0_label_player_current.text.font = &lv_font_roboto_22;
	style0_label_player_current.text.line_space = 2;

	ui->label_player_current = lv_label_create(ui->cont_par, NULL);
	lv_label_set_text(ui->label_player_current, "00:00");
	lv_label_set_long_mode(ui->label_player_current, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player_current, 10, 10);
	lv_obj_set_size(ui->label_player_current, 108, 22);
	lv_label_set_style(ui->label_player_current, LV_LABEL_STYLE_MAIN, &style0_label_player_current);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_player_total, &lv_style_transp);
	style0_label_player_total.text.color = lv_color_hex(0xe2e2e2);
	style0_label_player_total.text.font = &lv_font_roboto_22;
	style0_label_player_total.text.line_space = 2;

	ui->label_player_total = lv_label_create(ui->cont_par, NULL);
	lv_label_set_text(ui->label_player_total, "00:00");
	lv_label_set_align(ui->label_player_total, LV_LABEL_ALIGN_RIGHT);
	lv_label_set_long_mode(ui->label_player_total, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player_total, 348, 10);
	lv_obj_set_size(ui->label_player_total, 104, 25);
	lv_label_set_style(ui->label_player_total, LV_LABEL_STYLE_MAIN, &style0_label_player_total);
#endif // LV_USE_LABEL

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_video, &lv_style_pretty);
	style0_bar_video.body.grad_color = lv_color_hex(0xffffff);
	style0_bar_video.body.radius = 0;
	style0_bar_video.body.border.width = 0;
	style0_bar_video.body.border.opa = 255;

	lv_style_copy(&style1_bar_video, &lv_style_pretty_color);
	style1_bar_video.body.main_color = lv_color_hex(0xffff00);
	style1_bar_video.body.grad_color = lv_color_hex(0xffff00);
	style1_bar_video.body.radius = 0;
	style1_bar_video.body.border.color = lv_color_hex(0xffff00);
	style1_bar_video.body.border.width = 0;
	style1_bar_video.body.border.opa = 255;

	ui->bar_video = lv_bar_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->bar_video, 9, 342);
	lv_obj_set_size(ui->bar_video, 450, 15);
	lv_bar_set_range(ui->bar_video, 0, 1000);
	lv_bar_set_value(ui->bar_video, 0, LV_ANIM_ON);
	lv_bar_set_anim_time(ui->bar_video, 1000);
	lv_bar_set_style(ui->bar_video, LV_BAR_STYLE_BG, &style0_bar_video);
	lv_bar_set_style(ui->bar_video, LV_BAR_STYLE_INDIC, &style1_bar_video);
#endif // LV_USE_BAR

}

void player_ui_destory(player_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

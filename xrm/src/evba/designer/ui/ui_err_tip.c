/******************************************************************************
*    includes
******************************************************************************/
#include "ui_err_tip.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_cont_1;
static lv_style_t style0_label_1;


/******************************************************************************
*    functions
******************************************************************************/
void err_tip_ui_create(err_tip_ui_t *ui)
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
	lv_style_copy(&style0_cont_1, &lv_style_pretty);
	style0_cont_1.body.main_color = lv_color_hex(0x0041c5);
	style0_cont_1.body.grad_color = lv_color_hex(0x1509c0);

	ui->cont_1 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_1, 82, 77);
	lv_obj_set_size(ui->cont_1, 297, 203);
	lv_cont_set_fit4(ui->cont_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_1, LV_CONT_STYLE_MAIN, &style0_cont_1);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_1, &lv_style_transp);
	style0_label_1.text.color = lv_color_hex(0xffffff);
	style0_label_1.text.sel_color = lv_color_hex(0xffffff);
	style0_label_1.text.font = &lv_font_roboto_28;
	style0_label_1.text.line_space = 2;

	ui->label_1 = lv_label_create(ui->cont_1, NULL);
	lv_label_set_text(ui->label_1, "no file");
	lv_label_set_long_mode(ui->label_1, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_1, 104, 78);
	lv_obj_set_size(ui->label_1, 85, 30);
	lv_label_set_style(ui->label_1, LV_LABEL_STYLE_MAIN, &style0_label_1);
#endif // LV_USE_LABEL

}

void err_tip_ui_destory(err_tip_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

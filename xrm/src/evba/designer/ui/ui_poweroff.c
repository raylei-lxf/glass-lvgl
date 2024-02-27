/******************************************************************************
*    includes
******************************************************************************/
#include "ui_poweroff.h"
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
void poweroff_ui_create(poweroff_ui_t *ui)
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
	style0_cont_1.body.main_color = lv_color_hex(0x0037a5);
	style0_cont_1.body.grad_color = lv_color_hex(0x0037a5);

	ui->cont_1 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_1, 95, 91);
	lv_obj_set_size(ui->cont_1, 290, 190);
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
	lv_label_set_text(ui->label_1, "poweroff...");
	lv_label_set_align(ui->label_1, LV_LABEL_ALIGN_CENTER);
	lv_label_set_long_mode(ui->label_1, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_1, 66, 77);
	lv_obj_set_size(ui->label_1, 151, 41);
	lv_label_set_style(ui->label_1, LV_LABEL_STYLE_MAIN, &style0_label_1);
#endif // LV_USE_LABEL

}

void poweroff_ui_destory(poweroff_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

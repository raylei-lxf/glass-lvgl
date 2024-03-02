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
static lv_style_t style0_label_tip_title;
static lv_style_t style0_cont_tip_line;
static lv_style_t style0_label_tip_content;

static void *img_tip_tishi_png = NULL;

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
	style0_cont_1.body.main_color = lv_color_hex(0x101d6b);
	style0_cont_1.body.grad_color = lv_color_hex(0x101d6b);
	style0_cont_1.body.border.width = 0;

	ui->cont_1 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_1, 89, 100);
	lv_obj_set_size(ui->cont_1, 300, 174);
	lv_cont_set_fit4(ui->cont_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_1, LV_CONT_STYLE_MAIN, &style0_cont_1);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_tip_title, &lv_style_transp);
	style0_label_tip_title.text.color = lv_color_hex(0xffffff);
	style0_label_tip_title.text.font = &lv_font_roboto_28;
	style0_label_tip_title.text.line_space = 2;

	ui->label_tip_title = lv_label_create(ui->cont_1, NULL);
	lv_label_set_text(ui->label_tip_title, "POWEROFF");
	lv_label_set_align(ui->label_tip_title, LV_LABEL_ALIGN_CENTER);
	lv_label_set_long_mode(ui->label_tip_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_title, 56, 78);
	lv_obj_set_size(ui->label_tip_title, 194, 68);
	lv_label_set_style(ui->label_tip_title, LV_LABEL_STYLE_MAIN, &style0_label_tip_title);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_tip_line, &lv_style_pretty);
	style0_cont_tip_line.body.main_color = lv_color_hex(0x5366d7);
	style0_cont_tip_line.body.grad_color = lv_color_hex(0x5366d7);

	ui->cont_tip_line = lv_cont_create(ui->cont_1, NULL);
	lv_obj_set_pos(ui->cont_tip_line, 1, 39);
	lv_obj_set_size(ui->cont_tip_line, 300, 1);
	lv_cont_set_fit4(ui->cont_tip_line, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_tip_line, LV_CONT_STYLE_MAIN, &style0_cont_tip_line);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_tip = lv_img_create(ui->cont_1, NULL);
	lv_obj_set_pos(ui->img_tip, 9, 47);
	lv_obj_set_size(ui->img_tip, 23, 23);
	img_tip_tishi_png = (void *)mal_load_image(LV_IMAGE_PATH"tishi.png");
	lv_img_set_src(ui->img_tip, img_tip_tishi_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_tip_content, &lv_style_transp);
	style0_label_tip_content.text.color = lv_color_hex(0xffffff);
	style0_label_tip_content.text.sel_color = lv_color_hex(0xffffff);
	style0_label_tip_content.text.line_space = 2;

	ui->label_tip_content = lv_label_create(ui->cont_1, NULL);
	lv_label_set_text(ui->label_tip_content, "Tip");
	lv_label_set_long_mode(ui->label_tip_content, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_content, 7, 6);
	lv_obj_set_size(ui->label_tip_content, 145, 31);
	lv_label_set_style(ui->label_tip_content, LV_LABEL_STYLE_MAIN, &style0_label_tip_content);
#endif // LV_USE_LABEL

}

void poweroff_ui_destory(poweroff_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_tip_tishi_png);
}

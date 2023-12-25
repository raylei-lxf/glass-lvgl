/******************************************************************************
*    includes
******************************************************************************/
#include "ui_setting.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_setting;
static lv_style_t style0_cont_setting_line;
static lv_style_t style0_img_setting_title;
static lv_style_t style0_label_setting_title;
static lv_style_t style0_cont_setting_language;
static lv_style_t style0_label_language_title;
static lv_style_t style0_label_language;
static lv_style_t style0_cont_setting_factory;
static lv_style_t style0_label_factory;
static lv_style_t style0_cont_upgrade;
static lv_style_t style0_label_upgrade;

static void *img_setting_title_shezhitubiao_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void setting_ui_create(setting_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_setting, &lv_style_pretty);
	style0_cont_setting.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_setting.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_setting.body.radius = 0;
	style0_cont_setting.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_setting.body.border.width = 0;
	style0_cont_setting.body.shadow.color = lv_color_hex(0x4456c6);

	ui->cont_setting = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_setting, 0, 0);
	lv_obj_set_size(ui->cont_setting, 480, 360);
	lv_cont_set_fit4(ui->cont_setting, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_setting, LV_CONT_STYLE_MAIN, &style0_cont_setting);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_setting_line, &lv_style_pretty);
	style0_cont_setting_line.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_setting_line.body.radius = 0;

	ui->cont_setting_line = lv_cont_create(ui->cont_setting, NULL);
	lv_obj_set_pos(ui->cont_setting_line, 0, 48);
	lv_obj_set_size(ui->cont_setting_line, 480, 5);
	lv_cont_set_fit4(ui->cont_setting_line, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_setting_line, LV_CONT_STYLE_MAIN, &style0_cont_setting_line);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_setting_title, &lv_style_plain);

	ui->img_setting_title = lv_img_create(ui->cont_setting, NULL);
	lv_obj_set_pos(ui->img_setting_title, 15, 8);
	lv_obj_set_size(ui->img_setting_title, 34, 34);
	img_setting_title_shezhitubiao_png = (void *)mal_load_image(LV_IMAGE_PATH"shezhitubiao.png");
	lv_img_set_src(ui->img_setting_title, img_setting_title_shezhitubiao_png);

	lv_img_set_style(ui->img_setting_title, LV_IMG_STYLE_MAIN, &style0_img_setting_title);
#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_setting_title, &lv_style_transp);

	ui->label_setting_title = lv_label_create(ui->cont_setting, NULL);
	lv_label_set_text(ui->label_setting_title, "Text");
	lv_label_set_long_mode(ui->label_setting_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_setting_title, 60, 8);
	lv_obj_set_size(ui->label_setting_title, 109, 36);
	lv_label_set_style(ui->label_setting_title, LV_LABEL_STYLE_MAIN, &style0_label_setting_title);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_setting_language, &lv_style_pretty);
	style0_cont_setting_language.body.main_color = lv_color_hex(0x00007f);
	style0_cont_setting_language.body.grad_color = lv_color_hex(0x00007f);
	style0_cont_setting_language.body.radius = 0;
	style0_cont_setting_language.body.border.color = lv_color_hex(0xffffff);
	style0_cont_setting_language.body.border.width = 4;
	style0_cont_setting_language.body.border.opa = 0;

	ui->cont_setting_language = lv_cont_create(ui->cont_setting, NULL);
	lv_obj_set_pos(ui->cont_setting_language, 9, 73);
	lv_obj_set_size(ui->cont_setting_language, 465, 43);
	lv_cont_set_fit4(ui->cont_setting_language, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_setting_language, LV_CONT_STYLE_MAIN, &style0_cont_setting_language);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_language_title, &lv_style_transp);

	ui->label_language_title = lv_label_create(ui->cont_setting_language, NULL);
	lv_label_set_text(ui->label_language_title, "Text");
	lv_label_set_long_mode(ui->label_language_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_language_title, 14, 0);
	lv_obj_set_size(ui->label_language_title, 121, 41);
	lv_label_set_style(ui->label_language_title, LV_LABEL_STYLE_MAIN, &style0_label_language_title);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_language, &lv_style_transp);

	ui->label_language = lv_label_create(ui->cont_setting_language, NULL);
	lv_label_set_text(ui->label_language, "Text");
	lv_label_set_long_mode(ui->label_language, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_language, 320, 0);
	lv_obj_set_size(ui->label_language, 121, 41);
	lv_label_set_style(ui->label_language, LV_LABEL_STYLE_MAIN, &style0_label_language);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_setting_factory, &lv_style_pretty);
	style0_cont_setting_factory.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_setting_factory.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_setting_factory.body.radius = 0;
	style0_cont_setting_factory.body.border.width = 0;

	ui->cont_setting_factory = lv_cont_create(ui->cont_setting, NULL);
	lv_obj_set_pos(ui->cont_setting_factory, 8, 130);
	lv_obj_set_size(ui->cont_setting_factory, 465, 43);
	lv_cont_set_fit4(ui->cont_setting_factory, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_setting_factory, LV_CONT_STYLE_MAIN, &style0_cont_setting_factory);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_factory, &lv_style_transp);

	ui->label_factory = lv_label_create(ui->cont_setting_factory, NULL);
	lv_label_set_text(ui->label_factory, "Text");
	lv_label_set_long_mode(ui->label_factory, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_factory, 14, 0);
	lv_obj_set_size(ui->label_factory, 121, 41);
	lv_label_set_style(ui->label_factory, LV_LABEL_STYLE_MAIN, &style0_label_factory);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_upgrade, &lv_style_pretty);
	style0_cont_upgrade.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_upgrade.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_upgrade.body.radius = 0;
	style0_cont_upgrade.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_upgrade.body.border.width = 0;

	ui->cont_upgrade = lv_cont_create(ui->cont_setting, NULL);
	lv_obj_set_pos(ui->cont_upgrade, 7, 184);
	lv_obj_set_size(ui->cont_upgrade, 465, 43);
	lv_cont_set_fit4(ui->cont_upgrade, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_upgrade, LV_CONT_STYLE_MAIN, &style0_cont_upgrade);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_upgrade, &lv_style_transp);

	ui->label_upgrade = lv_label_create(ui->cont_upgrade, NULL);
	lv_label_set_text(ui->label_upgrade, "Text");
	lv_label_set_long_mode(ui->label_upgrade, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_upgrade, 14, 0);
	lv_obj_set_size(ui->label_upgrade, 121, 41);
	lv_label_set_style(ui->label_upgrade, LV_LABEL_STYLE_MAIN, &style0_label_upgrade);
#endif // LV_USE_LABEL

}

void setting_ui_destory(setting_ui_t *ui)
{
	lv_obj_del(ui->cont_setting);
	mal_unload_image(img_setting_title_shezhitubiao_png);
}

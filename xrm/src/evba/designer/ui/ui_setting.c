/******************************************************************************
*    includes
******************************************************************************/
#include "ui_setting.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_cont_setting_line;
static lv_style_t style0_cont_setting_language;
static lv_style_t style0_cont_setting_factory;
static lv_style_t style0_cont_upgrade;
static lv_style_t style0_cont_tip;
static lv_style_t style0_cont_tip_line;

static void *img_setting_title_shezhitubiao_png = NULL;
static void *img_tip_tishi_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void setting_ui_create(setting_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_main.body.border.width = 0;
	style0_cont_main.body.shadow.color = lv_color_hex(0x4456c6);

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_setting_line, &lv_style_pretty);
	style0_cont_setting_line.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_setting_line.body.radius = 0;
	style0_cont_setting_line.body.border.color = lv_color_hex(0xffffff);
	style0_cont_setting_line.body.border.width = 0;
	style0_cont_setting_line.body.border.opa = 255;

	ui->cont_setting_line = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_setting_line, 0, 48);
	lv_obj_set_size(ui->cont_setting_line, 480, 2);
	lv_cont_set_fit4(ui->cont_setting_line, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_setting_line, LV_CONT_STYLE_MAIN, &style0_cont_setting_line);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_setting_title = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_setting_title, 22, 8);
	lv_obj_set_size(ui->img_setting_title, 34, 34);
	img_setting_title_shezhitubiao_png = (void *)mal_load_image(LV_IMAGE_PATH"shezhitubiao.png");
	lv_img_set_src(ui->img_setting_title, img_setting_title_shezhitubiao_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_setting_title = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_setting_title, "Setting");
	lv_label_set_long_mode(ui->label_setting_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_setting_title, 65, 9);
	lv_obj_set_size(ui->label_setting_title, 96, 33);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_setting_language, &lv_style_pretty);
	style0_cont_setting_language.body.main_color = lv_color_hex(0x00007f);
	style0_cont_setting_language.body.grad_color = lv_color_hex(0x00007f);
	style0_cont_setting_language.body.radius = 0;
	style0_cont_setting_language.body.border.color = lv_color_hex(0xffffff);
	style0_cont_setting_language.body.border.opa = 255;

	ui->cont_setting_language = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_setting_language, 9, 73);
	lv_obj_set_size(ui->cont_setting_language, 465, 50);
	lv_cont_set_fit4(ui->cont_setting_language, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_setting_language, LV_CONT_STYLE_MAIN, &style0_cont_setting_language);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	ui->label_language_title = lv_label_create(ui->cont_setting_language, NULL);
	lv_label_set_text(ui->label_language_title, "Text");
	lv_label_set_long_mode(ui->label_language_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_language_title, 18, 9);
	lv_obj_set_size(ui->label_language_title, 163, 32);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	ui->label_language = lv_label_create(ui->cont_setting_language, NULL);
	lv_label_set_text(ui->label_language, "Text");
	lv_label_set_long_mode(ui->label_language, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_language, 293, 7);
	lv_obj_set_size(ui->label_language, 149, 34);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_setting_factory, &lv_style_pretty);
	style0_cont_setting_factory.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_setting_factory.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_setting_factory.body.radius = 0;
	style0_cont_setting_factory.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_setting_factory.body.border.opa = 255;

	ui->cont_setting_factory = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_setting_factory, 8, 130);
	lv_obj_set_size(ui->cont_setting_factory, 465, 50);
	lv_cont_set_fit4(ui->cont_setting_factory, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_setting_factory, LV_CONT_STYLE_MAIN, &style0_cont_setting_factory);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	ui->label_factory = lv_label_create(ui->cont_setting_factory, NULL);
	lv_label_set_text(ui->label_factory, "Text");
	lv_label_set_long_mode(ui->label_factory, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_factory, 13, 5);
	lv_obj_set_size(ui->label_factory, 359, 36);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_upgrade, &lv_style_pretty);
	style0_cont_upgrade.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_upgrade.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_upgrade.body.radius = 0;
	style0_cont_upgrade.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_upgrade.body.border.opa = 255;

	ui->cont_upgrade = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_upgrade, 8, 184);
	lv_obj_set_size(ui->cont_upgrade, 465, 50);
	lv_cont_set_fit4(ui->cont_upgrade, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_upgrade, LV_CONT_STYLE_MAIN, &style0_cont_upgrade);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	ui->label_upgrade = lv_label_create(ui->cont_upgrade, NULL);
	lv_label_set_text(ui->label_upgrade, "Text");
	lv_label_set_long_mode(ui->label_upgrade, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_upgrade, 14, 4);
	lv_obj_set_size(ui->label_upgrade, 393, 37);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_tip, &lv_style_pretty);
	style0_cont_tip.body.main_color = lv_color_hex(0x101d6b);
	style0_cont_tip.body.grad_color = lv_color_hex(0x101d6b);
	style0_cont_tip.body.border.width = 0;

	ui->cont_tip = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_tip, 96, 87);
	lv_obj_set_size(ui->cont_tip, 300, 175);
	lv_cont_set_fit4(ui->cont_tip, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_tip, LV_CONT_STYLE_MAIN, &style0_cont_tip);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	ui->label_tip_title = lv_label_create(ui->cont_tip, NULL);
	lv_label_set_text(ui->label_tip_title, "Untreated");
	lv_label_set_long_mode(ui->label_tip_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_title, 62, 67);
	lv_obj_set_size(ui->label_tip_title, 194, 68);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_tip_line, &lv_style_pretty);
	style0_cont_tip_line.body.main_color = lv_color_hex(0x5366d7);
	style0_cont_tip_line.body.grad_color = lv_color_hex(0x5366d7);

	ui->cont_tip_line = lv_cont_create(ui->cont_tip, NULL);
	lv_obj_set_pos(ui->cont_tip_line, 1, 39);
	lv_obj_set_size(ui->cont_tip_line, 300, 1);
	lv_cont_set_fit4(ui->cont_tip_line, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_tip_line, LV_CONT_STYLE_MAIN, &style0_cont_tip_line);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_tip = lv_img_create(ui->cont_tip, NULL);
	lv_obj_set_pos(ui->img_tip, 9, 47);
	lv_obj_set_size(ui->img_tip, 23, 23);
	img_tip_tishi_png = (void *)mal_load_image(LV_IMAGE_PATH"tishi.png");
	lv_img_set_src(ui->img_tip, img_tip_tishi_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_tip_content = lv_label_create(ui->cont_tip, NULL);
	lv_label_set_text(ui->label_tip_content, "Tip");
	lv_label_set_long_mode(ui->label_tip_content, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_content, 8, 9);
	lv_obj_set_size(ui->label_tip_content, 145, 26);
#endif // LV_USE_LABEL

}

void setting_ui_destory(setting_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_setting_title_shezhitubiao_png);
	mal_unload_image(img_tip_tishi_png);
}

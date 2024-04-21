/******************************************************************************
*    includes
******************************************************************************/
#include "ui_file_store.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_img_file_store_title;
static lv_style_t style0_cont_file_store_line;
static lv_style_t style0_label_file_store_title;
static lv_style_t style0_cont_sd;
static lv_style_t style0_label_sd;
static lv_style_t style0_cont_u;
static lv_style_t style0_label_usb;

static void *img_file_store_title_file_title_png = NULL;

extern int m_file_store_focus;
/******************************************************************************
*    functions
******************************************************************************/
void file_store_ui_create(file_store_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_main.body.border.width = 0;
	style0_cont_main.body.border.opa = 255;
	style0_cont_main.body.shadow.color = lv_color_hex(0x4456c6);

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_file_store_title, &lv_style_plain);

	ui->img_file_store_title = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_file_store_title, 17, 7);
	lv_obj_set_size(ui->img_file_store_title, 35, 36);
	img_file_store_title_file_title_png = (void *)mal_load_image(LV_IMAGE_PATH"file_title.png");
	lv_img_set_src(ui->img_file_store_title, img_file_store_title_file_title_png);

	lv_img_set_style(ui->img_file_store_title, LV_IMG_STYLE_MAIN, &style0_img_file_store_title);
#endif // LV_USE_IMG

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_file_store_line, &lv_style_pretty);
	style0_cont_file_store_line.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_file_store_line.body.radius = 0;
	style0_cont_file_store_line.body.border.color = lv_color_hex(0xffffff);
	style0_cont_file_store_line.body.border.width = 0;

	ui->cont_file_store_line = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_file_store_line, 0, 48);
	lv_obj_set_size(ui->cont_file_store_line, 480, 2);
	lv_cont_set_fit4(ui->cont_file_store_line, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_file_store_line, LV_CONT_STYLE_MAIN, &style0_cont_file_store_line);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_file_store_title, &lv_style_transp);

	ui->label_file_store_title = lv_label_create(ui->parent, NULL);
	lv_label_set_text(ui->label_file_store_title, "File");
	lv_label_set_long_mode(ui->label_file_store_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file_store_title, 59, 9);
	lv_obj_set_size(ui->label_file_store_title, 166, 36);
	lv_label_set_style(ui->label_file_store_title, LV_LABEL_STYLE_MAIN, &style0_label_file_store_title);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_sd, &lv_style_pretty);
	style0_cont_sd.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_sd.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_sd.body.radius = 0;
	style0_cont_sd.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_sd.body.border.opa = 255;

	ui->cont_sd = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_sd, 12, 60);
	lv_obj_set_size(ui->cont_sd, 465, 50);
	lv_cont_set_fit4(ui->cont_sd, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_sd, LV_CONT_STYLE_MAIN, &style0_cont_sd);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_sd, &lv_style_transp);

	ui->label_sd = lv_label_create(ui->cont_sd, NULL);
	lv_label_set_text(ui->label_sd, "Text");
	lv_label_set_long_mode(ui->label_sd, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_sd, 10, 4);
	lv_obj_set_size(ui->label_sd, 359, 36);
	lv_label_set_style(ui->label_sd, LV_LABEL_STYLE_MAIN, &style0_label_sd);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_u, &lv_style_pretty);
	style0_cont_u.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_u.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_u.body.radius = 0;
	style0_cont_u.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_u.body.border.opa = 255;

	ui->cont_u = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_u, 12, 115);
	lv_obj_set_size(ui->cont_u, 465, 50);
	lv_cont_set_fit4(ui->cont_u, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_u, LV_CONT_STYLE_MAIN, &style0_cont_u);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_usb, &lv_style_transp);

	ui->label_usb = lv_label_create(ui->cont_u, NULL);
	lv_label_set_text(ui->label_usb, "Text");
	lv_label_set_long_mode(ui->label_usb, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_usb, 8, 14);
	lv_obj_set_size(ui->label_usb, 359, 36);
	lv_label_set_style(ui->label_usb, LV_LABEL_STYLE_MAIN, &style0_label_usb);
#endif // LV_USE_LABEL

}

void file_store_ui_destory(file_store_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_file_store_title_file_title_png);
}

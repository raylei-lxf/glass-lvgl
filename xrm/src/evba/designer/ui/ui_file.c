/******************************************************************************
*    includes
******************************************************************************/
#include "ui_file.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_cont_file_line;
static lv_style_t style0_file_list;
static lv_style_t style1_file_list;
static lv_style_t style3_file_list;
static lv_style_t style4_file_list;
static lv_style_t style5_file_list;

static void *img_file_title_file_title_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void file_ui_create(file_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.border.color = lv_color_hex(0xffffff);
	style0_cont_main.body.border.width = 0;

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_file_line, &lv_style_pretty);
	style0_cont_file_line.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_file_line.body.radius = 0;
	style0_cont_file_line.body.border.color = lv_color_hex(0xffffff);
	style0_cont_file_line.body.border.width = 0;

	ui->cont_file_line = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_file_line, 0, 48);
	lv_obj_set_size(ui->cont_file_line, 480, 2);
	lv_cont_set_fit4(ui->cont_file_line, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_file_line, LV_CONT_STYLE_MAIN, &style0_cont_file_line);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_file_title = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_file_title, 15, 7);
	lv_obj_set_size(ui->img_file_title, 35, 36);
	img_file_title_file_title_png = (void *)mal_load_image(LV_IMAGE_PATH"file_title.png");
	lv_img_set_src(ui->img_file_title, img_file_title_file_title_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_file_title = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_file_title, "File");
	lv_label_set_long_mode(ui->label_file_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file_title, 59, 9);
	lv_obj_set_size(ui->label_file_title, 115, 36);
#endif // LV_USE_LABEL

#ifdef LV_USE_LIST
	lv_style_copy(&style0_file_list, &lv_style_transp_fit);
	style0_file_list.body.main_color = lv_color_hex(0x4456c6);
	style0_file_list.body.grad_color = lv_color_hex(0x4456c6);
	style0_file_list.body.border.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style1_file_list, &lv_style_pretty);
	style1_file_list.body.main_color = lv_color_hex(0x4456c6);
	style1_file_list.body.grad_color = lv_color_hex(0x4456c6);
	style1_file_list.body.radius = 0;
	style1_file_list.body.border.color = lv_color_hex(0x4456c6);
	style1_file_list.body.border.width = 0;
	style1_file_list.body.border.opa = 255;
	style1_file_list.body.shadow.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style3_file_list, &lv_style_transp);
	style3_file_list.body.main_color = lv_color_hex(0x5596d8);
	style3_file_list.body.grad_color = lv_color_hex(0x5596d8);
	style3_file_list.body.radius = 0;
	style3_file_list.body.opa = 255;
	style3_file_list.body.border.color = lv_color_hex(0x000000);
	style3_file_list.body.border.width = 0;
	style3_file_list.body.border.part = 15;
	style3_file_list.body.border.opa = 255;
	style3_file_list.body.shadow.color = lv_color_hex(0x808080);
	style3_file_list.body.shadow.width = 0;
	style3_file_list.body.shadow.type = 1;
	style3_file_list.body.padding.top = 5;
	style3_file_list.body.padding.bottom = 5;
	style3_file_list.body.padding.left = 5;
	style3_file_list.body.padding.right = 5;
	style3_file_list.body.padding.inner = 5;
	style3_file_list.text.color = lv_color_hex(0xf0f0f0);
	style3_file_list.text.sel_color = lv_color_hex(0x5596d8);
	style3_file_list.text.font = &lv_font_roboto_16;
	style3_file_list.text.letter_space = 0;
	style3_file_list.text.line_space = 2;
	style3_file_list.text.opa = 255;
	style3_file_list.image.color = lv_color_hex(0xf0f0f0);
	style3_file_list.image.intense = 0;
	style3_file_list.image.opa = 255;

	lv_style_copy(&style4_file_list, &lv_style_btn_rel);
	style4_file_list.body.main_color = lv_color_hex(0x4456c6);
	style4_file_list.body.grad_color = lv_color_hex(0x4456c6);
	style4_file_list.body.radius = 0;
	style4_file_list.body.border.color = lv_color_hex(0x4456c6);
	style4_file_list.body.border.width = 0;
	style4_file_list.body.border.opa = 255;
	style4_file_list.text.line_space = 2;

	lv_style_copy(&style5_file_list, &lv_style_btn_pr);
	style5_file_list.body.main_color = lv_color_hex(0x101d6b);
	style5_file_list.body.grad_color = lv_color_hex(0x101d6b);
	style5_file_list.body.radius = 0;
	style5_file_list.body.border.color = lv_color_hex(0x101d6b);
	style5_file_list.body.border.width = 0;
	style5_file_list.body.border.opa = 255;
	style5_file_list.text.line_space = 2;

	ui->file_list = lv_list_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->file_list, 23, 62);
	lv_obj_set_size(ui->file_list, 444, 275);
	lv_list_set_single_mode(ui->file_list, false);
	lv_list_set_scroll_propagation(ui->file_list, false);
	lv_list_set_edge_flash(ui->file_list, false);
	lv_list_set_style(ui->file_list, LV_LIST_STYLE_BG, &style0_file_list);
	lv_list_set_style(ui->file_list, LV_LIST_STYLE_SCRL, &style1_file_list);
	lv_list_set_style(ui->file_list, LV_LIST_STYLE_EDGE_FLASH, &style3_file_list);
	lv_list_set_style(ui->file_list, LV_LIST_STYLE_BTN_REL, &style4_file_list);
	lv_list_set_style(ui->file_list, LV_LIST_STYLE_BTN_PR, &style5_file_list);
#endif // LV_USE_LIST

}

void file_ui_destory(file_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_file_title_file_title_png);
}

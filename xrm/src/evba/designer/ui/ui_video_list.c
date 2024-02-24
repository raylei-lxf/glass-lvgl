/******************************************************************************
*    includes
******************************************************************************/
#include "ui_video_list.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_cont_1;
static lv_style_t style0_list_video;
static lv_style_t style1_list_video;
static lv_style_t style3_list_video;
static lv_style_t style4_list_video;
static lv_style_t style5_list_video;

static void *img_1_videotubiao_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void video_list_ui_create(video_list_ui_t *ui)
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

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_1, &lv_style_pretty);
	style0_cont_1.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_1.body.radius = 0;
	style0_cont_1.body.border.color = lv_color_hex(0xffffff);
	style0_cont_1.body.border.width = 0;

	ui->cont_1 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_1, 0, 48);
	lv_obj_set_size(ui->cont_1, 480, 2);
	lv_cont_set_fit4(ui->cont_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_1, LV_CONT_STYLE_MAIN, &style0_cont_1);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_1 = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_1, 24, 10);
	lv_obj_set_size(ui->img_1, 30, 30);
	img_1_videotubiao_png = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao.png");
	lv_img_set_src(ui->img_1, img_1_videotubiao_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_1 = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_1, "Video");
	lv_label_set_long_mode(ui->label_1, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_1, 64, 12);
	lv_obj_set_size(ui->label_1, 64, 33);
#endif // LV_USE_LABEL

#ifdef LV_USE_LIST
	lv_style_copy(&style0_list_video, &lv_style_transp_fit);
	style0_list_video.body.main_color = lv_color_hex(0x4456c6);
	style0_list_video.body.grad_color = lv_color_hex(0x4456c6);
	style0_list_video.body.border.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style1_list_video, &lv_style_pretty);
	style1_list_video.body.main_color = lv_color_hex(0x4456c6);
	style1_list_video.body.grad_color = lv_color_hex(0x4456c6);
	style1_list_video.body.radius = 0;
	style1_list_video.body.border.color = lv_color_hex(0x4456c6);
	style1_list_video.body.border.width = 0;
	style1_list_video.body.border.opa = 255;
	style1_list_video.body.shadow.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style3_list_video, &lv_style_transp);
	style3_list_video.body.main_color = lv_color_hex(0x5596d8);
	style3_list_video.body.grad_color = lv_color_hex(0x5596d8);
	style3_list_video.body.radius = 0;
	style3_list_video.body.opa = 255;
	style3_list_video.body.border.color = lv_color_hex(0x000000);
	style3_list_video.body.border.width = 0;
	style3_list_video.body.border.part = 15;
	style3_list_video.body.border.opa = 255;
	style3_list_video.body.shadow.color = lv_color_hex(0x808080);
	style3_list_video.body.shadow.width = 0;
	style3_list_video.body.shadow.type = 1;
	style3_list_video.body.padding.top = 5;
	style3_list_video.body.padding.bottom = 5;
	style3_list_video.body.padding.left = 5;
	style3_list_video.body.padding.right = 5;
	style3_list_video.body.padding.inner = 5;
	style3_list_video.text.color = lv_color_hex(0xf0f0f0);
	style3_list_video.text.sel_color = lv_color_hex(0x5596d8);
	style3_list_video.text.font = &lv_font_roboto_16;
	style3_list_video.text.letter_space = 0;
	style3_list_video.text.line_space = 2;
	style3_list_video.text.opa = 255;
	style3_list_video.image.color = lv_color_hex(0xf0f0f0);
	style3_list_video.image.intense = 0;
	style3_list_video.image.opa = 255;

	lv_style_copy(&style4_list_video, &lv_style_btn_rel);
	style4_list_video.body.main_color = lv_color_hex(0x4456c6);
	style4_list_video.body.grad_color = lv_color_hex(0x4456c6);
	style4_list_video.body.radius = 0;
	style4_list_video.body.border.color = lv_color_hex(0x4456c6);
	style4_list_video.body.border.width = 0;
	style4_list_video.body.border.opa = 255;
	style4_list_video.text.line_space = 2;

	lv_style_copy(&style5_list_video, &lv_style_btn_pr);
	style5_list_video.body.main_color = lv_color_hex(0x101d6b);
	style5_list_video.body.grad_color = lv_color_hex(0x101d6b);
	style5_list_video.body.radius = 0;
	style5_list_video.body.border.color = lv_color_hex(0x101d6b);
	style5_list_video.body.border.width = 0;
	style5_list_video.body.border.opa = 255;
	style5_list_video.text.line_space = 2;

	ui->list_video = lv_list_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->list_video, 22, 62);
	lv_obj_set_size(ui->list_video, 444, 275);
	lv_list_set_single_mode(ui->list_video, false);
	lv_list_set_scroll_propagation(ui->list_video, false);
	lv_list_set_edge_flash(ui->list_video, false);
	lv_list_set_style(ui->list_video, LV_LIST_STYLE_BG, &style0_list_video);
	lv_list_set_style(ui->list_video, LV_LIST_STYLE_SCRL, &style1_list_video);
	lv_list_set_style(ui->list_video, LV_LIST_STYLE_EDGE_FLASH, &style3_list_video);
	lv_list_set_style(ui->list_video, LV_LIST_STYLE_BTN_REL, &style4_list_video);
	lv_list_set_style(ui->list_video, LV_LIST_STYLE_BTN_PR, &style5_list_video);
#endif // LV_USE_LIST

}

void video_list_ui_destory(video_list_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_1_videotubiao_png);
}

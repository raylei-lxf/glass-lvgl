/******************************************************************************
*    includes
******************************************************************************/
#include "ui_music.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_cont_1;
static lv_style_t style0_cont_music_list;
static lv_style_t style0_label_music_start;
static lv_style_t style0_cont_5;
static lv_style_t style0_cont_music_1;
static lv_style_t style0_cont_music_1_2;
static lv_style_t style0_cont_music_1_3;
static lv_style_t style0_cont_music_1_4;
static lv_style_t style0_cont_music_1_5;
static lv_style_t style0_cont_music_1_6;
static lv_style_t style0_cont_music_1_7;
static lv_style_t style0_cont_music_1_8;
static lv_style_t style0_cont_music_1_9;
static lv_style_t style0_cont_music_1_10;
static lv_style_t style0_cont_music_1_11;
static lv_style_t style0_cont_music_1_1;
static lv_style_t style0_cont_music_2;
static lv_style_t style0_cont_music_2_2;
static lv_style_t style0_cont_music_2_3;
static lv_style_t style0_cont_music_2_4;
static lv_style_t style0_cont_music_2_5;
static lv_style_t style0_cont_music_2_6;
static lv_style_t style0_cont_music_2_7;
static lv_style_t style0_cont_music_2_8;
static lv_style_t style0_cont_music_2_9;
static lv_style_t style0_cont_music_2_10;
static lv_style_t style0_cont_music_2_11;
static lv_style_t style0_cont_music_2_1;
static lv_style_t style0_cont_music_3;
static lv_style_t style0_cont_music_3_2;
static lv_style_t style0_cont_music_3_3;
static lv_style_t style0_cont_music_3_4;
static lv_style_t style0_cont_music_3_5;
static lv_style_t style0_cont_music_3_6;
static lv_style_t style0_cont_music_3_7;
static lv_style_t style0_cont_music_3_8;
static lv_style_t style0_cont_music_3_9;
static lv_style_t style0_cont_music_3_10;
static lv_style_t style0_cont_music_3_11;
static lv_style_t style0_cont_music_3_1;
static lv_style_t style0_cont_music_4;
static lv_style_t style0_cont_music_4_2;
static lv_style_t style0_cont_music_4_3;
static lv_style_t style0_cont_music_4_4;
static lv_style_t style0_cont_music_4_5;
static lv_style_t style0_cont_music_4_6;
static lv_style_t style0_cont_music_4_7;
static lv_style_t style0_cont_music_4_8;
static lv_style_t style0_cont_music_4_9;
static lv_style_t style0_cont_music_4_10;
static lv_style_t style0_cont_music_4_11;
static lv_style_t style0_cont_music_4_1;
static lv_style_t style0_cont_music_5;
static lv_style_t style0_cont_music_5_2;
static lv_style_t style0_cont_music_5_3;
static lv_style_t style0_cont_music_5_4;
static lv_style_t style0_cont_music_5_5;
static lv_style_t style0_cont_music_5_6;
static lv_style_t style0_cont_music_5_7;
static lv_style_t style0_cont_music_5_8;
static lv_style_t style0_cont_music_5_9;
static lv_style_t style0_cont_music_5_10;
static lv_style_t style0_cont_music_5_11;
static lv_style_t style0_cont_music_5_1;
static lv_style_t style0_list_mp3;
static lv_style_t style1_list_mp3;
static lv_style_t style3_list_mp3;
static lv_style_t style4_list_mp3;
static lv_style_t style5_list_mp3;
static lv_style_t style0_bar_music;
static lv_style_t style1_bar_music;
static lv_style_t style0_label_music_totle;

static void *img_2_xunhuanmoshi_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void music_ui_create(music_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_main.body.border.width = 0;
	style0_cont_main.body.border.opa = 255;

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
	style0_cont_1.body.border.opa = 255;

	ui->cont_1 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_1, 215, 28);
	lv_obj_set_size(ui->cont_1, 4, 296);
	lv_cont_set_fit4(ui->cont_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_1, LV_CONT_STYLE_MAIN, &style0_cont_1);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_list, &lv_style_pretty);
	style0_cont_music_list.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_music_list.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_music_list.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_music_list.body.border.width = 0;

	ui->cont_music_list = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_music_list, 14, 33);
	lv_obj_set_size(ui->cont_music_list, 198, 45);
	lv_cont_set_fit4(ui->cont_music_list, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_list, LV_CONT_STYLE_MAIN, &style0_cont_music_list);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_music_start, &lv_style_transp);

	ui->label_music_start = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_music_start, "00:00:00");
	lv_label_set_long_mode(ui->label_music_start, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music_start, 224, 278);
	lv_obj_set_size(ui->label_music_start, 73, 23);
	lv_label_set_style(ui->label_music_start, LV_LABEL_STYLE_MAIN, &style0_label_music_start);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_5, &lv_style_pretty);
	style0_cont_5.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_5.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_5.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_5.body.border.width = 0;

	ui->cont_5 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_5, 228, 13);
	lv_obj_set_size(ui->cont_5, 240, 265);
	lv_cont_set_fit4(ui->cont_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_5, LV_CONT_STYLE_MAIN, &style0_cont_5);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_2 = lv_img_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->img_2, 58, 0);
	lv_obj_set_size(ui->img_2, 28, 26);
	img_2_xunhuanmoshi_png = (void *)mal_load_image(LV_IMAGE_PATH"xunhuanmoshi.png");
	lv_img_set_src(ui->img_2, img_2_xunhuanmoshi_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_4 = lv_label_create(ui->cont_5, NULL);
	lv_label_set_text(ui->label_4, "01/04");
	lv_label_set_long_mode(ui->label_4, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_4, 150, 0);
	lv_obj_set_size(ui->label_4, 70, 29);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1, &lv_style_pretty);
	style0_cont_music_1.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_music_1.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_music_1.body.radius = 0;
	style0_cont_music_1.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_music_1.body.border.width = 0;

	ui->cont_music_1 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_music_1, 3, 32);
	lv_obj_set_size(ui->cont_music_1, 39, 229);
	lv_cont_set_fit4(ui->cont_music_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1, LV_CONT_STYLE_MAIN, &style0_cont_music_1);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_2, &lv_style_pretty);
	style0_cont_music_1_2.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_2.body.radius = 0;
	style0_cont_music_1_2.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_2.body.border.width = 0;

	ui->cont_music_1_2 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_2, 7, 190);
	lv_obj_set_size(ui->cont_music_1_2, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_2, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_2, LV_CONT_STYLE_MAIN, &style0_cont_music_1_2);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_3, &lv_style_pretty);
	style0_cont_music_1_3.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_3.body.radius = 0;
	style0_cont_music_1_3.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_3.body.border.width = 0;

	ui->cont_music_1_3 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_3, 7, 170);
	lv_obj_set_size(ui->cont_music_1_3, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_3, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_3, LV_CONT_STYLE_MAIN, &style0_cont_music_1_3);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_4, &lv_style_pretty);
	style0_cont_music_1_4.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_4.body.radius = 0;
	style0_cont_music_1_4.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_4.body.border.width = 0;

	ui->cont_music_1_4 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_4, 7, 150);
	lv_obj_set_size(ui->cont_music_1_4, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_4, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_4, LV_CONT_STYLE_MAIN, &style0_cont_music_1_4);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_5, &lv_style_pretty);
	style0_cont_music_1_5.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_5.body.radius = 0;
	style0_cont_music_1_5.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_5.body.border.width = 0;

	ui->cont_music_1_5 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_5, 7, 130);
	lv_obj_set_size(ui->cont_music_1_5, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_5, LV_CONT_STYLE_MAIN, &style0_cont_music_1_5);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_6, &lv_style_pretty);
	style0_cont_music_1_6.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_6.body.radius = 0;
	style0_cont_music_1_6.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_6.body.border.width = 0;

	ui->cont_music_1_6 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_6, 7, 110);
	lv_obj_set_size(ui->cont_music_1_6, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_6, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_6, LV_CONT_STYLE_MAIN, &style0_cont_music_1_6);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_7, &lv_style_pretty);
	style0_cont_music_1_7.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_7.body.radius = 0;
	style0_cont_music_1_7.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_7.body.border.width = 0;

	ui->cont_music_1_7 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_7, 7, 90);
	lv_obj_set_size(ui->cont_music_1_7, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_7, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_7, LV_CONT_STYLE_MAIN, &style0_cont_music_1_7);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_8, &lv_style_pretty);
	style0_cont_music_1_8.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_8.body.radius = 0;
	style0_cont_music_1_8.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_8.body.border.width = 0;

	ui->cont_music_1_8 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_8, 7, 70);
	lv_obj_set_size(ui->cont_music_1_8, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_8, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_8, LV_CONT_STYLE_MAIN, &style0_cont_music_1_8);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_9, &lv_style_pretty);
	style0_cont_music_1_9.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_9.body.radius = 0;
	style0_cont_music_1_9.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_9.body.border.width = 0;

	ui->cont_music_1_9 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_9, 7, 50);
	lv_obj_set_size(ui->cont_music_1_9, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_9, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_9, LV_CONT_STYLE_MAIN, &style0_cont_music_1_9);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_10, &lv_style_pretty);
	style0_cont_music_1_10.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_10.body.radius = 0;
	style0_cont_music_1_10.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_10.body.border.width = 0;

	ui->cont_music_1_10 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_10, 7, 30);
	lv_obj_set_size(ui->cont_music_1_10, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_10, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_10, LV_CONT_STYLE_MAIN, &style0_cont_music_1_10);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_11, &lv_style_pretty);
	style0_cont_music_1_11.body.main_color = lv_color_hex(0xffff00);
	style0_cont_music_1_11.body.grad_color = lv_color_hex(0xffff00);
	style0_cont_music_1_11.body.radius = 0;
	style0_cont_music_1_11.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_11.body.border.width = 0;

	ui->cont_music_1_11 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_11, 7, 10);
	lv_obj_set_size(ui->cont_music_1_11, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_11, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_11, LV_CONT_STYLE_MAIN, &style0_cont_music_1_11);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_1_1, &lv_style_pretty);
	style0_cont_music_1_1.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_1_1.body.radius = 0;
	style0_cont_music_1_1.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_1_1.body.border.width = 0;

	ui->cont_music_1_1 = lv_cont_create(ui->cont_music_1, NULL);
	lv_obj_set_pos(ui->cont_music_1_1, 7, 210);
	lv_obj_set_size(ui->cont_music_1_1, 25, 10);
	lv_cont_set_fit4(ui->cont_music_1_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_1_1, LV_CONT_STYLE_MAIN, &style0_cont_music_1_1);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2, &lv_style_pretty);
	style0_cont_music_2.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_music_2.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_music_2.body.radius = 0;
	style0_cont_music_2.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_music_2.body.border.width = 0;

	ui->cont_music_2 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_music_2, 50, 32);
	lv_obj_set_size(ui->cont_music_2, 39, 230);
	lv_cont_set_fit4(ui->cont_music_2, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2, LV_CONT_STYLE_MAIN, &style0_cont_music_2);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_2, &lv_style_pretty);
	style0_cont_music_2_2.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_2.body.radius = 0;
	style0_cont_music_2_2.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_2.body.border.width = 0;

	ui->cont_music_2_2 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_2, 7, 190);
	lv_obj_set_size(ui->cont_music_2_2, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_2, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_2, LV_CONT_STYLE_MAIN, &style0_cont_music_2_2);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_3, &lv_style_pretty);
	style0_cont_music_2_3.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_3.body.radius = 0;
	style0_cont_music_2_3.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_3.body.border.width = 0;

	ui->cont_music_2_3 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_3, 8, 170);
	lv_obj_set_size(ui->cont_music_2_3, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_3, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_3, LV_CONT_STYLE_MAIN, &style0_cont_music_2_3);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_4, &lv_style_pretty);
	style0_cont_music_2_4.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_4.body.radius = 0;
	style0_cont_music_2_4.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_4.body.border.width = 0;

	ui->cont_music_2_4 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_4, 7, 150);
	lv_obj_set_size(ui->cont_music_2_4, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_4, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_4, LV_CONT_STYLE_MAIN, &style0_cont_music_2_4);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_5, &lv_style_pretty);
	style0_cont_music_2_5.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_5.body.radius = 0;
	style0_cont_music_2_5.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_5.body.border.width = 0;

	ui->cont_music_2_5 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_5, 7, 130);
	lv_obj_set_size(ui->cont_music_2_5, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_5, LV_CONT_STYLE_MAIN, &style0_cont_music_2_5);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_6, &lv_style_pretty);
	style0_cont_music_2_6.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_6.body.radius = 0;
	style0_cont_music_2_6.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_6.body.border.width = 0;

	ui->cont_music_2_6 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_6, 7, 110);
	lv_obj_set_size(ui->cont_music_2_6, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_6, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_6, LV_CONT_STYLE_MAIN, &style0_cont_music_2_6);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_7, &lv_style_pretty);
	style0_cont_music_2_7.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_7.body.radius = 0;
	style0_cont_music_2_7.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_7.body.border.width = 0;

	ui->cont_music_2_7 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_7, 7, 90);
	lv_obj_set_size(ui->cont_music_2_7, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_7, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_7, LV_CONT_STYLE_MAIN, &style0_cont_music_2_7);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_8, &lv_style_pretty);
	style0_cont_music_2_8.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_8.body.radius = 0;
	style0_cont_music_2_8.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_8.body.border.width = 0;

	ui->cont_music_2_8 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_8, 7, 70);
	lv_obj_set_size(ui->cont_music_2_8, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_8, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_8, LV_CONT_STYLE_MAIN, &style0_cont_music_2_8);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_9, &lv_style_pretty);
	style0_cont_music_2_9.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_9.body.radius = 0;
	style0_cont_music_2_9.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_9.body.border.width = 0;

	ui->cont_music_2_9 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_9, 7, 50);
	lv_obj_set_size(ui->cont_music_2_9, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_9, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_9, LV_CONT_STYLE_MAIN, &style0_cont_music_2_9);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_10, &lv_style_pretty);
	style0_cont_music_2_10.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_10.body.radius = 0;
	style0_cont_music_2_10.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_10.body.border.width = 0;

	ui->cont_music_2_10 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_10, 7, 30);
	lv_obj_set_size(ui->cont_music_2_10, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_10, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_10, LV_CONT_STYLE_MAIN, &style0_cont_music_2_10);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_11, &lv_style_pretty);
	style0_cont_music_2_11.body.main_color = lv_color_hex(0xffff00);
	style0_cont_music_2_11.body.grad_color = lv_color_hex(0xffff00);
	style0_cont_music_2_11.body.radius = 0;
	style0_cont_music_2_11.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_11.body.border.width = 0;

	ui->cont_music_2_11 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_11, 7, 10);
	lv_obj_set_size(ui->cont_music_2_11, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_11, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_11, LV_CONT_STYLE_MAIN, &style0_cont_music_2_11);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_2_1, &lv_style_pretty);
	style0_cont_music_2_1.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_2_1.body.radius = 0;
	style0_cont_music_2_1.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_2_1.body.border.width = 0;

	ui->cont_music_2_1 = lv_cont_create(ui->cont_music_2, NULL);
	lv_obj_set_pos(ui->cont_music_2_1, 7, 210);
	lv_obj_set_size(ui->cont_music_2_1, 25, 10);
	lv_cont_set_fit4(ui->cont_music_2_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_2_1, LV_CONT_STYLE_MAIN, &style0_cont_music_2_1);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3, &lv_style_pretty);
	style0_cont_music_3.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_music_3.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_music_3.body.radius = 0;
	style0_cont_music_3.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_music_3.body.border.width = 0;

	ui->cont_music_3 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_music_3, 94, 32);
	lv_obj_set_size(ui->cont_music_3, 39, 229);
	lv_cont_set_fit4(ui->cont_music_3, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3, LV_CONT_STYLE_MAIN, &style0_cont_music_3);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_2, &lv_style_pretty);
	style0_cont_music_3_2.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_2.body.radius = 0;
	style0_cont_music_3_2.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_2.body.border.width = 0;

	ui->cont_music_3_2 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_2, 7, 190);
	lv_obj_set_size(ui->cont_music_3_2, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_2, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_2, LV_CONT_STYLE_MAIN, &style0_cont_music_3_2);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_3, &lv_style_pretty);
	style0_cont_music_3_3.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_3.body.radius = 0;
	style0_cont_music_3_3.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_3.body.border.width = 0;

	ui->cont_music_3_3 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_3, 7, 170);
	lv_obj_set_size(ui->cont_music_3_3, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_3, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_3, LV_CONT_STYLE_MAIN, &style0_cont_music_3_3);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_4, &lv_style_pretty);
	style0_cont_music_3_4.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_4.body.radius = 0;
	style0_cont_music_3_4.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_4.body.border.width = 0;

	ui->cont_music_3_4 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_4, 7, 150);
	lv_obj_set_size(ui->cont_music_3_4, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_4, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_4, LV_CONT_STYLE_MAIN, &style0_cont_music_3_4);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_5, &lv_style_pretty);
	style0_cont_music_3_5.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_5.body.radius = 0;
	style0_cont_music_3_5.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_5.body.border.width = 0;

	ui->cont_music_3_5 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_5, 7, 130);
	lv_obj_set_size(ui->cont_music_3_5, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_5, LV_CONT_STYLE_MAIN, &style0_cont_music_3_5);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_6, &lv_style_pretty);
	style0_cont_music_3_6.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_6.body.radius = 0;
	style0_cont_music_3_6.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_6.body.border.width = 0;

	ui->cont_music_3_6 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_6, 7, 110);
	lv_obj_set_size(ui->cont_music_3_6, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_6, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_6, LV_CONT_STYLE_MAIN, &style0_cont_music_3_6);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_7, &lv_style_pretty);
	style0_cont_music_3_7.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_7.body.radius = 0;
	style0_cont_music_3_7.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_7.body.border.width = 0;

	ui->cont_music_3_7 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_7, 7, 90);
	lv_obj_set_size(ui->cont_music_3_7, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_7, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_7, LV_CONT_STYLE_MAIN, &style0_cont_music_3_7);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_8, &lv_style_pretty);
	style0_cont_music_3_8.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_8.body.radius = 0;
	style0_cont_music_3_8.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_8.body.border.width = 0;

	ui->cont_music_3_8 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_8, 7, 70);
	lv_obj_set_size(ui->cont_music_3_8, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_8, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_8, LV_CONT_STYLE_MAIN, &style0_cont_music_3_8);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_9, &lv_style_pretty);
	style0_cont_music_3_9.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_9.body.radius = 0;
	style0_cont_music_3_9.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_9.body.border.width = 0;

	ui->cont_music_3_9 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_9, 7, 50);
	lv_obj_set_size(ui->cont_music_3_9, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_9, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_9, LV_CONT_STYLE_MAIN, &style0_cont_music_3_9);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_10, &lv_style_pretty);
	style0_cont_music_3_10.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_10.body.radius = 0;
	style0_cont_music_3_10.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_10.body.border.width = 0;

	ui->cont_music_3_10 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_10, 7, 30);
	lv_obj_set_size(ui->cont_music_3_10, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_10, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_10, LV_CONT_STYLE_MAIN, &style0_cont_music_3_10);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_11, &lv_style_pretty);
	style0_cont_music_3_11.body.main_color = lv_color_hex(0xffff00);
	style0_cont_music_3_11.body.grad_color = lv_color_hex(0xffff00);
	style0_cont_music_3_11.body.radius = 0;
	style0_cont_music_3_11.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_11.body.border.width = 0;

	ui->cont_music_3_11 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_11, 7, 10);
	lv_obj_set_size(ui->cont_music_3_11, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_11, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_11, LV_CONT_STYLE_MAIN, &style0_cont_music_3_11);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_3_1, &lv_style_pretty);
	style0_cont_music_3_1.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_3_1.body.radius = 0;
	style0_cont_music_3_1.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_3_1.body.border.width = 0;

	ui->cont_music_3_1 = lv_cont_create(ui->cont_music_3, NULL);
	lv_obj_set_pos(ui->cont_music_3_1, 7, 210);
	lv_obj_set_size(ui->cont_music_3_1, 25, 10);
	lv_cont_set_fit4(ui->cont_music_3_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_3_1, LV_CONT_STYLE_MAIN, &style0_cont_music_3_1);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4, &lv_style_pretty);
	style0_cont_music_4.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_music_4.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_music_4.body.radius = 0;
	style0_cont_music_4.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_music_4.body.border.width = 0;

	ui->cont_music_4 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_music_4, 141, 33);
	lv_obj_set_size(ui->cont_music_4, 39, 229);
	lv_cont_set_fit4(ui->cont_music_4, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4, LV_CONT_STYLE_MAIN, &style0_cont_music_4);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_2, &lv_style_pretty);
	style0_cont_music_4_2.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_2.body.radius = 0;
	style0_cont_music_4_2.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_2.body.border.width = 0;

	ui->cont_music_4_2 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_2, 7, 190);
	lv_obj_set_size(ui->cont_music_4_2, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_2, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_2, LV_CONT_STYLE_MAIN, &style0_cont_music_4_2);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_3, &lv_style_pretty);
	style0_cont_music_4_3.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_3.body.radius = 0;
	style0_cont_music_4_3.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_3.body.border.width = 0;

	ui->cont_music_4_3 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_3, 7, 170);
	lv_obj_set_size(ui->cont_music_4_3, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_3, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_3, LV_CONT_STYLE_MAIN, &style0_cont_music_4_3);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_4, &lv_style_pretty);
	style0_cont_music_4_4.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_4.body.radius = 0;
	style0_cont_music_4_4.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_4.body.border.width = 0;

	ui->cont_music_4_4 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_4, 7, 150);
	lv_obj_set_size(ui->cont_music_4_4, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_4, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_4, LV_CONT_STYLE_MAIN, &style0_cont_music_4_4);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_5, &lv_style_pretty);
	style0_cont_music_4_5.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_5.body.radius = 0;
	style0_cont_music_4_5.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_5.body.border.width = 0;

	ui->cont_music_4_5 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_5, 7, 130);
	lv_obj_set_size(ui->cont_music_4_5, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_5, LV_CONT_STYLE_MAIN, &style0_cont_music_4_5);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_6, &lv_style_pretty);
	style0_cont_music_4_6.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_6.body.radius = 0;
	style0_cont_music_4_6.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_6.body.border.width = 0;

	ui->cont_music_4_6 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_6, 7, 110);
	lv_obj_set_size(ui->cont_music_4_6, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_6, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_6, LV_CONT_STYLE_MAIN, &style0_cont_music_4_6);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_7, &lv_style_pretty);
	style0_cont_music_4_7.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_7.body.radius = 0;
	style0_cont_music_4_7.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_7.body.border.width = 0;

	ui->cont_music_4_7 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_7, 7, 90);
	lv_obj_set_size(ui->cont_music_4_7, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_7, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_7, LV_CONT_STYLE_MAIN, &style0_cont_music_4_7);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_8, &lv_style_pretty);
	style0_cont_music_4_8.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_8.body.radius = 0;
	style0_cont_music_4_8.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_8.body.border.width = 0;

	ui->cont_music_4_8 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_8, 7, 70);
	lv_obj_set_size(ui->cont_music_4_8, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_8, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_8, LV_CONT_STYLE_MAIN, &style0_cont_music_4_8);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_9, &lv_style_pretty);
	style0_cont_music_4_9.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_9.body.radius = 0;
	style0_cont_music_4_9.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_9.body.border.width = 0;

	ui->cont_music_4_9 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_9, 7, 50);
	lv_obj_set_size(ui->cont_music_4_9, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_9, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_9, LV_CONT_STYLE_MAIN, &style0_cont_music_4_9);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_10, &lv_style_pretty);
	style0_cont_music_4_10.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_10.body.radius = 0;
	style0_cont_music_4_10.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_10.body.border.width = 0;

	ui->cont_music_4_10 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_10, 7, 30);
	lv_obj_set_size(ui->cont_music_4_10, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_10, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_10, LV_CONT_STYLE_MAIN, &style0_cont_music_4_10);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_11, &lv_style_pretty);
	style0_cont_music_4_11.body.main_color = lv_color_hex(0xffff00);
	style0_cont_music_4_11.body.grad_color = lv_color_hex(0xffff00);
	style0_cont_music_4_11.body.radius = 0;
	style0_cont_music_4_11.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_11.body.border.width = 0;

	ui->cont_music_4_11 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_11, 7, 10);
	lv_obj_set_size(ui->cont_music_4_11, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_11, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_11, LV_CONT_STYLE_MAIN, &style0_cont_music_4_11);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_4_1, &lv_style_pretty);
	style0_cont_music_4_1.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_4_1.body.radius = 0;
	style0_cont_music_4_1.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_4_1.body.border.width = 0;

	ui->cont_music_4_1 = lv_cont_create(ui->cont_music_4, NULL);
	lv_obj_set_pos(ui->cont_music_4_1, 7, 210);
	lv_obj_set_size(ui->cont_music_4_1, 25, 10);
	lv_cont_set_fit4(ui->cont_music_4_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_4_1, LV_CONT_STYLE_MAIN, &style0_cont_music_4_1);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5, &lv_style_pretty);
	style0_cont_music_5.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_music_5.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_music_5.body.radius = 0;
	style0_cont_music_5.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_music_5.body.border.width = 0;

	ui->cont_music_5 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_music_5, 186, 33);
	lv_obj_set_size(ui->cont_music_5, 39, 229);
	lv_cont_set_fit4(ui->cont_music_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5, LV_CONT_STYLE_MAIN, &style0_cont_music_5);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_2, &lv_style_pretty);
	style0_cont_music_5_2.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_2.body.radius = 0;
	style0_cont_music_5_2.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_2.body.border.width = 0;

	ui->cont_music_5_2 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_2, 7, 190);
	lv_obj_set_size(ui->cont_music_5_2, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_2, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_2, LV_CONT_STYLE_MAIN, &style0_cont_music_5_2);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_3, &lv_style_pretty);
	style0_cont_music_5_3.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_3.body.radius = 0;
	style0_cont_music_5_3.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_3.body.border.width = 0;

	ui->cont_music_5_3 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_3, 7, 170);
	lv_obj_set_size(ui->cont_music_5_3, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_3, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_3, LV_CONT_STYLE_MAIN, &style0_cont_music_5_3);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_4, &lv_style_pretty);
	style0_cont_music_5_4.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_4.body.radius = 0;
	style0_cont_music_5_4.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_4.body.border.width = 0;

	ui->cont_music_5_4 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_4, 7, 150);
	lv_obj_set_size(ui->cont_music_5_4, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_4, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_4, LV_CONT_STYLE_MAIN, &style0_cont_music_5_4);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_5, &lv_style_pretty);
	style0_cont_music_5_5.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_5.body.radius = 0;
	style0_cont_music_5_5.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_5.body.border.width = 0;

	ui->cont_music_5_5 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_5, 7, 130);
	lv_obj_set_size(ui->cont_music_5_5, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_5, LV_CONT_STYLE_MAIN, &style0_cont_music_5_5);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_6, &lv_style_pretty);
	style0_cont_music_5_6.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_6.body.radius = 0;
	style0_cont_music_5_6.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_6.body.border.width = 0;

	ui->cont_music_5_6 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_6, 7, 110);
	lv_obj_set_size(ui->cont_music_5_6, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_6, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_6, LV_CONT_STYLE_MAIN, &style0_cont_music_5_6);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_7, &lv_style_pretty);
	style0_cont_music_5_7.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_7.body.radius = 0;
	style0_cont_music_5_7.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_7.body.border.width = 0;

	ui->cont_music_5_7 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_7, 7, 90);
	lv_obj_set_size(ui->cont_music_5_7, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_7, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_7, LV_CONT_STYLE_MAIN, &style0_cont_music_5_7);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_8, &lv_style_pretty);
	style0_cont_music_5_8.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_8.body.radius = 0;
	style0_cont_music_5_8.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_8.body.border.width = 0;

	ui->cont_music_5_8 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_8, 7, 70);
	lv_obj_set_size(ui->cont_music_5_8, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_8, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_8, LV_CONT_STYLE_MAIN, &style0_cont_music_5_8);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_9, &lv_style_pretty);
	style0_cont_music_5_9.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_9.body.radius = 0;
	style0_cont_music_5_9.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_9.body.border.width = 0;

	ui->cont_music_5_9 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_9, 7, 50);
	lv_obj_set_size(ui->cont_music_5_9, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_9, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_9, LV_CONT_STYLE_MAIN, &style0_cont_music_5_9);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_10, &lv_style_pretty);
	style0_cont_music_5_10.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_10.body.radius = 0;
	style0_cont_music_5_10.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_10.body.border.width = 0;

	ui->cont_music_5_10 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_10, 7, 30);
	lv_obj_set_size(ui->cont_music_5_10, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_10, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_10, LV_CONT_STYLE_MAIN, &style0_cont_music_5_10);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_11, &lv_style_pretty);
	style0_cont_music_5_11.body.main_color = lv_color_hex(0xffff00);
	style0_cont_music_5_11.body.grad_color = lv_color_hex(0xffff00);
	style0_cont_music_5_11.body.radius = 0;
	style0_cont_music_5_11.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_11.body.border.width = 0;

	ui->cont_music_5_11 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_11, 7, 10);
	lv_obj_set_size(ui->cont_music_5_11, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_11, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_11, LV_CONT_STYLE_MAIN, &style0_cont_music_5_11);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_5_1, &lv_style_pretty);
	style0_cont_music_5_1.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_5_1.body.radius = 0;
	style0_cont_music_5_1.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_5_1.body.border.width = 0;

	ui->cont_music_5_1 = lv_cont_create(ui->cont_music_5, NULL);
	lv_obj_set_pos(ui->cont_music_5_1, 7, 210);
	lv_obj_set_size(ui->cont_music_5_1, 25, 10);
	lv_cont_set_fit4(ui->cont_music_5_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_5_1, LV_CONT_STYLE_MAIN, &style0_cont_music_5_1);
#endif // LV_USE_CONT

#ifdef LV_USE_LIST
	lv_style_copy(&style0_list_mp3, &lv_style_transp_fit);
	style0_list_mp3.body.main_color = lv_color_hex(0x4456c6);
	style0_list_mp3.body.grad_color = lv_color_hex(0x4456c6);
	style0_list_mp3.body.border.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style1_list_mp3, &lv_style_pretty);
	style1_list_mp3.body.main_color = lv_color_hex(0x4456c6);
	style1_list_mp3.body.grad_color = lv_color_hex(0x4456c6);
	style1_list_mp3.body.radius = 0;
	style1_list_mp3.body.border.color = lv_color_hex(0x4456c6);
	style1_list_mp3.body.border.width = 0;
	style1_list_mp3.body.border.opa = 255;
	style1_list_mp3.body.shadow.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style3_list_mp3, &lv_style_transp);
	style3_list_mp3.body.main_color = lv_color_hex(0x5596d8);
	style3_list_mp3.body.grad_color = lv_color_hex(0x5596d8);
	style3_list_mp3.body.radius = 0;
	style3_list_mp3.body.opa = 255;
	style3_list_mp3.body.border.color = lv_color_hex(0x000000);
	style3_list_mp3.body.border.width = 0;
	style3_list_mp3.body.border.part = 15;
	style3_list_mp3.body.border.opa = 255;
	style3_list_mp3.body.shadow.color = lv_color_hex(0x808080);
	style3_list_mp3.body.shadow.width = 0;
	style3_list_mp3.body.shadow.type = 1;
	style3_list_mp3.body.padding.top = 5;
	style3_list_mp3.body.padding.bottom = 5;
	style3_list_mp3.body.padding.left = 5;
	style3_list_mp3.body.padding.right = 5;
	style3_list_mp3.body.padding.inner = 5;
	style3_list_mp3.text.color = lv_color_hex(0xf0f0f0);
	style3_list_mp3.text.sel_color = lv_color_hex(0x5596d8);
	style3_list_mp3.text.font = &lv_font_roboto_16;
	style3_list_mp3.text.letter_space = 0;
	style3_list_mp3.text.line_space = 2;
	style3_list_mp3.text.opa = 255;
	style3_list_mp3.image.color = lv_color_hex(0xf0f0f0);
	style3_list_mp3.image.intense = 0;
	style3_list_mp3.image.opa = 255;

	lv_style_copy(&style4_list_mp3, &lv_style_btn_rel);
	style4_list_mp3.body.main_color = lv_color_hex(0x4456c6);
	style4_list_mp3.body.grad_color = lv_color_hex(0x4456c6);
	style4_list_mp3.body.radius = 0;
	style4_list_mp3.body.border.color = lv_color_hex(0x4456c6);
	style4_list_mp3.body.border.width = 0;
	style4_list_mp3.body.border.opa = 255;
	style4_list_mp3.text.line_space = 2;

	lv_style_copy(&style5_list_mp3, &lv_style_btn_pr);
	style5_list_mp3.body.main_color = lv_color_hex(0x101d6b);
	style5_list_mp3.body.grad_color = lv_color_hex(0x101d6b);
	style5_list_mp3.body.radius = 0;
	style5_list_mp3.body.border.color = lv_color_hex(0x101d6b);
	style5_list_mp3.body.border.width = 0;
	style5_list_mp3.body.border.opa = 255;
	style5_list_mp3.text.line_space = 2;

	ui->list_mp3 = lv_list_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->list_mp3, 27, 25);
	lv_obj_set_size(ui->list_mp3, 158, 286);
	lv_list_set_single_mode(ui->list_mp3, false);
	lv_list_set_scroll_propagation(ui->list_mp3, false);
	lv_list_set_edge_flash(ui->list_mp3, false);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_BG, &style0_list_mp3);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_SCRL, &style1_list_mp3);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_EDGE_FLASH, &style3_list_mp3);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_BTN_REL, &style4_list_mp3);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_BTN_PR, &style5_list_mp3);
#endif // LV_USE_LIST

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_music, &lv_style_pretty);
	style0_bar_music.body.grad_color = lv_color_hex(0xffffff);
	style0_bar_music.body.radius = 0;
	style0_bar_music.body.border.width = 0;
	style0_bar_music.body.border.opa = 255;

	lv_style_copy(&style1_bar_music, &lv_style_pretty_color);
	style1_bar_music.body.main_color = lv_color_hex(0xffff00);
	style1_bar_music.body.grad_color = lv_color_hex(0xffff00);
	style1_bar_music.body.radius = 0;
	style1_bar_music.body.border.color = lv_color_hex(0xffff00);
	style1_bar_music.body.border.width = 0;
	style1_bar_music.body.border.part = 0;
	style1_bar_music.body.border.opa = 255;

	ui->bar_music = lv_bar_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->bar_music, 223, 304);
	lv_obj_set_size(ui->bar_music, 251, 15);
	lv_bar_set_range(ui->bar_music, 0, 1000);
	lv_bar_set_value(ui->bar_music, 0, LV_ANIM_ON);
	lv_bar_set_anim_time(ui->bar_music, 1000);
	lv_bar_set_style(ui->bar_music, LV_BAR_STYLE_BG, &style0_bar_music);
	lv_bar_set_style(ui->bar_music, LV_BAR_STYLE_INDIC, &style1_bar_music);
#endif // LV_USE_BAR

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_music_totle, &lv_style_transp);

	ui->label_music_totle = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_music_totle, "00:00:00");
	lv_label_set_long_mode(ui->label_music_totle, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music_totle, 405, 278);
	lv_obj_set_size(ui->label_music_totle, 71, 23);
	lv_label_set_style(ui->label_music_totle, LV_LABEL_STYLE_MAIN, &style0_label_music_totle);
#endif // LV_USE_LABEL

}

void music_ui_destory(music_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_2_xunhuanmoshi_png);
}

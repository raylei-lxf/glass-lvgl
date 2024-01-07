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
static lv_style_t style0_cont_music_process;
static lv_style_t style0_cont_music_process_bak;
static lv_style_t style0_label_music_start;
static lv_style_t style0_label_music_totle;
static lv_style_t style0_label_music;
static lv_style_t style0_cont_2;
static lv_style_t style0_cont_3;
static lv_style_t style0_cont_4;
static lv_style_t style0_cont_5;
static lv_style_t style0_cont_6;
static lv_style_t style0_cont_7;
static lv_style_t style0_cont_8;
static lv_style_t style0_cont_9;
static lv_style_t style0_cont_10;
static lv_style_t style0_cont_11;
static lv_style_t style0_cont_12;
static lv_style_t style0_cont_13;
static lv_style_t style0_cont_14;
static lv_style_t style0_cont_15;
static lv_style_t style0_cont_16;
static lv_style_t style0_cont_17;
static lv_style_t style0_cont_18;
static lv_style_t style0_cont_19;
static lv_style_t style0_cont_20;
static lv_style_t style0_cont_30;
static lv_style_t style0_cont_21;
static lv_style_t style0_cont_22;
static lv_style_t style0_cont_24;
static lv_style_t style0_cont_25;
static lv_style_t style0_cont_26;
static lv_style_t style0_cont_31;
static lv_style_t style0_cont_32;
static lv_style_t style0_cont_33;
static lv_style_t style0_cont_34;
static lv_style_t style0_cont_23;
static lv_style_t style0_list_mp3;
static lv_style_t style1_list_mp3;
static lv_style_t style4_list_mp3;
static lv_style_t style5_list_mp3;

static void *img_xunhuan_xunhuanmoshi_png = NULL;

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
	lv_obj_set_pos(ui->cont_1, 224, 27);
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

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_process, &lv_style_pretty);
	style0_cont_music_process.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_process.body.radius = 0;
	style0_cont_music_process.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_process.body.border.width = 0;
	style0_cont_music_process.body.border.opa = 255;

	ui->cont_music_process = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_music_process, 240, 281);
	lv_obj_set_size(ui->cont_music_process, 215, 4);
	lv_cont_set_fit4(ui->cont_music_process, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_process, LV_CONT_STYLE_MAIN, &style0_cont_music_process);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_process_bak, &lv_style_pretty);
	style0_cont_music_process_bak.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_process_bak.body.radius = 0;
	style0_cont_music_process_bak.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_process_bak.body.border.width = 0;
	style0_cont_music_process_bak.body.border.opa = 255;

	ui->cont_music_process_bak = lv_cont_create(ui->cont_music_process, NULL);
	lv_obj_set_pos(ui->cont_music_process_bak, 0, 0);
	lv_obj_set_size(ui->cont_music_process_bak, 215, 4);
	lv_cont_set_fit4(ui->cont_music_process_bak, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_process_bak, LV_CONT_STYLE_MAIN, &style0_cont_music_process_bak);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_music_start, &lv_style_transp);
	style0_label_music_start.text.color = lv_color_hex(0xffffff);
	style0_label_music_start.text.sel_color = lv_color_hex(0xffffff);
	style0_label_music_start.text.line_space = 2;

	ui->label_music_start = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_music_start, "00:16");
	lv_label_set_long_mode(ui->label_music_start, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music_start, 237, 261);
	lv_obj_set_size(ui->label_music_start, 48, 21);
	lv_label_set_style(ui->label_music_start, LV_LABEL_STYLE_MAIN, &style0_label_music_start);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_music_totle, &lv_style_transp);
	style0_label_music_totle.text.color = lv_color_hex(0xffffff);
	style0_label_music_totle.text.sel_color = lv_color_hex(0xffffff);
	style0_label_music_totle.text.line_space = 2;

	ui->label_music_totle = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_music_totle, "02:58");
	lv_label_set_long_mode(ui->label_music_totle, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music_totle, 412, 261);
	lv_obj_set_size(ui->label_music_totle, 47, 23);
	lv_label_set_style(ui->label_music_totle, LV_LABEL_STYLE_MAIN, &style0_label_music_totle);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_music, &lv_style_transp);
	style0_label_music.text.color = lv_color_hex(0xffffff);
	style0_label_music.text.sel_color = lv_color_hex(0xffffff);
	style0_label_music.text.line_space = 2;

	ui->label_music = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_music, "01/03");
	lv_label_set_long_mode(ui->label_music, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music, 393, 25);
	lv_obj_set_size(ui->label_music, 60, 26);
	lv_label_set_style(ui->label_music, LV_LABEL_STYLE_MAIN, &style0_label_music);
#endif // LV_USE_LABEL

#ifdef LV_USE_IMG
	ui->img_xunhuan = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_xunhuan, 275, 22);
	lv_obj_set_size(ui->img_xunhuan, 28, 26);
	img_xunhuan_xunhuanmoshi_png = (void *)mal_load_image(LV_IMAGE_PATH"xunhuanmoshi.png");
	lv_img_set_src(ui->img_xunhuan, img_xunhuan_xunhuanmoshi_png);

#endif // LV_USE_IMG

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_2, &lv_style_pretty);
	style0_cont_2.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_2.body.radius = 0;
	style0_cont_2.body.border.color = lv_color_hex(0xffffff);
	style0_cont_2.body.border.width = 0;
	style0_cont_2.body.border.opa = 255;

	ui->cont_2 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_2, 236, 245);
	lv_obj_set_size(ui->cont_2, 30, 8);
	lv_cont_set_fit4(ui->cont_2, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_2, LV_CONT_STYLE_MAIN, &style0_cont_2);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_3, &lv_style_pretty);
	style0_cont_3.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_3.body.radius = 0;
	style0_cont_3.body.border.color = lv_color_hex(0xffffff);
	style0_cont_3.body.border.width = 0;
	style0_cont_3.body.border.opa = 255;

	ui->cont_3 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_3, 236, 225);
	lv_obj_set_size(ui->cont_3, 30, 8);
	lv_cont_set_fit4(ui->cont_3, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_3, LV_CONT_STYLE_MAIN, &style0_cont_3);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_4, &lv_style_pretty);
	style0_cont_4.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_4.body.radius = 0;
	style0_cont_4.body.border.color = lv_color_hex(0xffffff);
	style0_cont_4.body.border.width = 0;
	style0_cont_4.body.border.opa = 255;

	ui->cont_4 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_4, 236, 205);
	lv_obj_set_size(ui->cont_4, 30, 8);
	lv_cont_set_fit4(ui->cont_4, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_4, LV_CONT_STYLE_MAIN, &style0_cont_4);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_5, &lv_style_pretty);
	style0_cont_5.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_5.body.radius = 0;
	style0_cont_5.body.border.color = lv_color_hex(0xffffff);
	style0_cont_5.body.border.width = 0;
	style0_cont_5.body.border.opa = 255;

	ui->cont_5 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_5, 236, 185);
	lv_obj_set_size(ui->cont_5, 30, 8);
	lv_cont_set_fit4(ui->cont_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_5, LV_CONT_STYLE_MAIN, &style0_cont_5);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_6, &lv_style_pretty);
	style0_cont_6.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_6.body.radius = 0;
	style0_cont_6.body.border.color = lv_color_hex(0xffffff);
	style0_cont_6.body.border.width = 0;
	style0_cont_6.body.border.opa = 255;

	ui->cont_6 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_6, 236, 165);
	lv_obj_set_size(ui->cont_6, 30, 8);
	lv_cont_set_fit4(ui->cont_6, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_6, LV_CONT_STYLE_MAIN, &style0_cont_6);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_7, &lv_style_pretty);
	style0_cont_7.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_7.body.radius = 0;
	style0_cont_7.body.border.color = lv_color_hex(0xffffff);
	style0_cont_7.body.border.width = 0;
	style0_cont_7.body.border.opa = 255;

	ui->cont_7 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_7, 276, 245);
	lv_obj_set_size(ui->cont_7, 30, 8);
	lv_cont_set_fit4(ui->cont_7, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_7, LV_CONT_STYLE_MAIN, &style0_cont_7);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_8, &lv_style_pretty);
	style0_cont_8.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_8.body.radius = 0;
	style0_cont_8.body.border.color = lv_color_hex(0xffffff);
	style0_cont_8.body.border.width = 0;
	style0_cont_8.body.border.opa = 255;

	ui->cont_8 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_8, 276, 225);
	lv_obj_set_size(ui->cont_8, 30, 8);
	lv_cont_set_fit4(ui->cont_8, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_8, LV_CONT_STYLE_MAIN, &style0_cont_8);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_9, &lv_style_pretty);
	style0_cont_9.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_9.body.radius = 0;
	style0_cont_9.body.border.color = lv_color_hex(0xffffff);
	style0_cont_9.body.border.width = 0;
	style0_cont_9.body.border.opa = 255;

	ui->cont_9 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_9, 276, 205);
	lv_obj_set_size(ui->cont_9, 30, 8);
	lv_cont_set_fit4(ui->cont_9, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_9, LV_CONT_STYLE_MAIN, &style0_cont_9);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_10, &lv_style_pretty);
	style0_cont_10.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_10.body.radius = 0;
	style0_cont_10.body.border.color = lv_color_hex(0xffffff);
	style0_cont_10.body.border.width = 0;
	style0_cont_10.body.border.opa = 255;

	ui->cont_10 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_10, 276, 185);
	lv_obj_set_size(ui->cont_10, 30, 8);
	lv_cont_set_fit4(ui->cont_10, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_10, LV_CONT_STYLE_MAIN, &style0_cont_10);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_11, &lv_style_pretty);
	style0_cont_11.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_11.body.radius = 0;
	style0_cont_11.body.border.color = lv_color_hex(0xffffff);
	style0_cont_11.body.border.width = 0;
	style0_cont_11.body.border.opa = 255;

	ui->cont_11 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_11, 276, 165);
	lv_obj_set_size(ui->cont_11, 30, 8);
	lv_cont_set_fit4(ui->cont_11, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_11, LV_CONT_STYLE_MAIN, &style0_cont_11);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_12, &lv_style_pretty);
	style0_cont_12.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_12.body.radius = 0;
	style0_cont_12.body.border.color = lv_color_hex(0xffffff);
	style0_cont_12.body.border.width = 0;
	style0_cont_12.body.border.opa = 255;

	ui->cont_12 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_12, 316, 245);
	lv_obj_set_size(ui->cont_12, 30, 8);
	lv_cont_set_fit4(ui->cont_12, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_12, LV_CONT_STYLE_MAIN, &style0_cont_12);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_13, &lv_style_pretty);
	style0_cont_13.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_13.body.radius = 0;
	style0_cont_13.body.border.color = lv_color_hex(0xffffff);
	style0_cont_13.body.border.width = 0;
	style0_cont_13.body.border.opa = 255;

	ui->cont_13 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_13, 356, 245);
	lv_obj_set_size(ui->cont_13, 30, 8);
	lv_cont_set_fit4(ui->cont_13, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_13, LV_CONT_STYLE_MAIN, &style0_cont_13);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_14, &lv_style_pretty);
	style0_cont_14.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_14.body.radius = 0;
	style0_cont_14.body.border.color = lv_color_hex(0xffffff);
	style0_cont_14.body.border.width = 0;
	style0_cont_14.body.border.opa = 255;

	ui->cont_14 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_14, 396, 245);
	lv_obj_set_size(ui->cont_14, 30, 8);
	lv_cont_set_fit4(ui->cont_14, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_14, LV_CONT_STYLE_MAIN, &style0_cont_14);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_15, &lv_style_pretty);
	style0_cont_15.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_15.body.radius = 0;
	style0_cont_15.body.border.color = lv_color_hex(0xffffff);
	style0_cont_15.body.border.width = 0;
	style0_cont_15.body.border.opa = 255;

	ui->cont_15 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_15, 316, 225);
	lv_obj_set_size(ui->cont_15, 30, 8);
	lv_cont_set_fit4(ui->cont_15, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_15, LV_CONT_STYLE_MAIN, &style0_cont_15);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_16, &lv_style_pretty);
	style0_cont_16.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_16.body.radius = 0;
	style0_cont_16.body.border.color = lv_color_hex(0xffffff);
	style0_cont_16.body.border.width = 0;
	style0_cont_16.body.border.opa = 255;

	ui->cont_16 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_16, 316, 205);
	lv_obj_set_size(ui->cont_16, 30, 8);
	lv_cont_set_fit4(ui->cont_16, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_16, LV_CONT_STYLE_MAIN, &style0_cont_16);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_17, &lv_style_pretty);
	style0_cont_17.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_17.body.radius = 0;
	style0_cont_17.body.border.color = lv_color_hex(0xffffff);
	style0_cont_17.body.border.width = 0;
	style0_cont_17.body.border.opa = 255;

	ui->cont_17 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_17, 316, 185);
	lv_obj_set_size(ui->cont_17, 30, 8);
	lv_cont_set_fit4(ui->cont_17, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_17, LV_CONT_STYLE_MAIN, &style0_cont_17);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_18, &lv_style_pretty);
	style0_cont_18.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_18.body.radius = 0;
	style0_cont_18.body.border.color = lv_color_hex(0xffffff);
	style0_cont_18.body.border.width = 0;
	style0_cont_18.body.border.opa = 255;

	ui->cont_18 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_18, 356, 225);
	lv_obj_set_size(ui->cont_18, 30, 8);
	lv_cont_set_fit4(ui->cont_18, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_18, LV_CONT_STYLE_MAIN, &style0_cont_18);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_19, &lv_style_pretty);
	style0_cont_19.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_19.body.radius = 0;
	style0_cont_19.body.border.color = lv_color_hex(0xffffff);
	style0_cont_19.body.border.width = 0;
	style0_cont_19.body.border.opa = 255;

	ui->cont_19 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_19, 276, 145);
	lv_obj_set_size(ui->cont_19, 30, 8);
	lv_cont_set_fit4(ui->cont_19, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_19, LV_CONT_STYLE_MAIN, &style0_cont_19);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_20, &lv_style_pretty);
	style0_cont_20.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_20.body.radius = 0;
	style0_cont_20.body.border.color = lv_color_hex(0xffffff);
	style0_cont_20.body.border.width = 0;
	style0_cont_20.body.border.opa = 255;

	ui->cont_20 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_20, 236, 145);
	lv_obj_set_size(ui->cont_20, 30, 9);
	lv_cont_set_fit4(ui->cont_20, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_20, LV_CONT_STYLE_MAIN, &style0_cont_20);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_30, &lv_style_pretty);
	style0_cont_30.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_30.body.radius = 0;
	style0_cont_30.body.border.color = lv_color_hex(0xffffff);
	style0_cont_30.body.border.width = 0;
	style0_cont_30.body.border.opa = 255;

	ui->cont_30 = lv_cont_create(ui->cont_20, NULL);
	lv_obj_set_pos(ui->cont_30, 282, 242);
	lv_obj_set_size(ui->cont_30, 30, 8);
	lv_cont_set_fit4(ui->cont_30, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_30, LV_CONT_STYLE_MAIN, &style0_cont_30);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_21, &lv_style_pretty);
	style0_cont_21.body.main_color = lv_color_hex(0xe7e700);
	style0_cont_21.body.grad_color = lv_color_hex(0xe7e700);
	style0_cont_21.body.radius = 0;
	style0_cont_21.body.border.color = lv_color_hex(0xe7e700);
	style0_cont_21.body.border.width = 0;
	style0_cont_21.body.border.opa = 255;

	ui->cont_21 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_21, 434, 206);
	lv_obj_set_size(ui->cont_21, 30, 8);
	lv_cont_set_fit4(ui->cont_21, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_21, LV_CONT_STYLE_MAIN, &style0_cont_21);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_22, &lv_style_pretty);
	style0_cont_22.body.main_color = lv_color_hex(0xe7e700);
	style0_cont_22.body.grad_color = lv_color_hex(0xe7e700);
	style0_cont_22.body.radius = 0;
	style0_cont_22.body.border.color = lv_color_hex(0xe7e700);
	style0_cont_22.body.border.width = 0;
	style0_cont_22.body.border.opa = 255;

	ui->cont_22 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_22, 394, 184);
	lv_obj_set_size(ui->cont_22, 30, 8);
	lv_cont_set_fit4(ui->cont_22, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_22, LV_CONT_STYLE_MAIN, &style0_cont_22);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_24, &lv_style_pretty);
	style0_cont_24.body.main_color = lv_color_hex(0xe7e700);
	style0_cont_24.body.grad_color = lv_color_hex(0xe7e700);
	style0_cont_24.body.radius = 0;
	style0_cont_24.body.border.color = lv_color_hex(0xe7e700);
	style0_cont_24.body.border.width = 0;
	style0_cont_24.body.border.opa = 255;

	ui->cont_24 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_24, 356, 157);
	lv_obj_set_size(ui->cont_24, 30, 8);
	lv_cont_set_fit4(ui->cont_24, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_24, LV_CONT_STYLE_MAIN, &style0_cont_24);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_25, &lv_style_pretty);
	style0_cont_25.body.main_color = lv_color_hex(0xe7e700);
	style0_cont_25.body.grad_color = lv_color_hex(0xe7e700);
	style0_cont_25.body.radius = 0;
	style0_cont_25.body.border.color = lv_color_hex(0xe7e700);
	style0_cont_25.body.border.width = 0;
	style0_cont_25.body.border.opa = 255;

	ui->cont_25 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_25, 316, 132);
	lv_obj_set_size(ui->cont_25, 30, 8);
	lv_cont_set_fit4(ui->cont_25, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_25, LV_CONT_STYLE_MAIN, &style0_cont_25);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_26, &lv_style_pretty);
	style0_cont_26.body.main_color = lv_color_hex(0xe7e700);
	style0_cont_26.body.grad_color = lv_color_hex(0xe7e700);
	style0_cont_26.body.radius = 0;
	style0_cont_26.body.border.color = lv_color_hex(0xe7e700);
	style0_cont_26.body.border.width = 0;
	style0_cont_26.body.border.opa = 255;

	ui->cont_26 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_26, 277, 111);
	lv_obj_set_size(ui->cont_26, 30, 8);
	lv_cont_set_fit4(ui->cont_26, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_26, LV_CONT_STYLE_MAIN, &style0_cont_26);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_31, &lv_style_pretty);
	style0_cont_31.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_31.body.radius = 0;
	style0_cont_31.body.border.color = lv_color_hex(0xffffff);
	style0_cont_31.body.border.width = 0;
	style0_cont_31.body.border.opa = 255;

	ui->cont_31 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_31, 236, 125);
	lv_obj_set_size(ui->cont_31, 30, 9);
	lv_cont_set_fit4(ui->cont_31, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_31, LV_CONT_STYLE_MAIN, &style0_cont_31);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_32, &lv_style_pretty);
	style0_cont_32.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_32.body.radius = 0;
	style0_cont_32.body.border.color = lv_color_hex(0xffffff);
	style0_cont_32.body.border.width = 0;
	style0_cont_32.body.border.opa = 255;

	ui->cont_32 = lv_cont_create(ui->cont_31, NULL);
	lv_obj_set_pos(ui->cont_32, 282, 242);
	lv_obj_set_size(ui->cont_32, 30, 8);
	lv_cont_set_fit4(ui->cont_32, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_32, LV_CONT_STYLE_MAIN, &style0_cont_32);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_33, &lv_style_pretty);
	style0_cont_33.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_33.body.radius = 0;
	style0_cont_33.body.border.color = lv_color_hex(0xffffff);
	style0_cont_33.body.border.width = 0;
	style0_cont_33.body.border.opa = 255;

	ui->cont_33 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_33, 236, 105);
	lv_obj_set_size(ui->cont_33, 30, 9);
	lv_cont_set_fit4(ui->cont_33, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_33, LV_CONT_STYLE_MAIN, &style0_cont_33);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_34, &lv_style_pretty);
	style0_cont_34.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_34.body.radius = 0;
	style0_cont_34.body.border.color = lv_color_hex(0xffffff);
	style0_cont_34.body.border.width = 0;
	style0_cont_34.body.border.opa = 255;

	ui->cont_34 = lv_cont_create(ui->cont_33, NULL);
	lv_obj_set_pos(ui->cont_34, 282, 242);
	lv_obj_set_size(ui->cont_34, 30, 8);
	lv_cont_set_fit4(ui->cont_34, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_34, LV_CONT_STYLE_MAIN, &style0_cont_34);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_23, &lv_style_pretty);
	style0_cont_23.body.main_color = lv_color_hex(0xe7e700);
	style0_cont_23.body.grad_color = lv_color_hex(0xe7e700);
	style0_cont_23.body.radius = 0;
	style0_cont_23.body.border.color = lv_color_hex(0xe7e700);
	style0_cont_23.body.border.width = 0;
	style0_cont_23.body.border.opa = 255;

	ui->cont_23 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_23, 236, 66);
	lv_obj_set_size(ui->cont_23, 30, 8);
	lv_cont_set_fit4(ui->cont_23, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_23, LV_CONT_STYLE_MAIN, &style0_cont_23);
#endif // LV_USE_CONT

#ifdef LV_USE_LIST
	lv_style_copy(&style0_list_mp3, &lv_style_transp_fit);
	style0_list_mp3.body.main_color = lv_color_hex(0x4456c6);
	style0_list_mp3.body.grad_color = lv_color_hex(0x4456c6);
	style0_list_mp3.body.border.color = lv_color_hex(0x4456c6);
	style0_list_mp3.body.shadow.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style1_list_mp3, &lv_style_pretty);
	style1_list_mp3.body.main_color = lv_color_hex(0x4456c6);
	style1_list_mp3.body.grad_color = lv_color_hex(0x4456c6);
	style1_list_mp3.body.radius = 0;
	style1_list_mp3.body.border.color = lv_color_hex(0x4456c6);

	lv_style_copy(&style4_list_mp3, &lv_style_btn_rel);
	style4_list_mp3.body.main_color = lv_color_hex(0x4456c6);
	style4_list_mp3.body.grad_color = lv_color_hex(0x4456c6);
	style4_list_mp3.body.radius = 0;
	style4_list_mp3.body.border.color = lv_color_hex(0x4456c6);
	style4_list_mp3.body.border.opa = 255;
	style4_list_mp3.body.shadow.color = lv_color_hex(0x4456c6);
	style4_list_mp3.text.sel_color = lv_color_hex(0xffffff);
	style4_list_mp3.text.line_space = 2;

	lv_style_copy(&style5_list_mp3, &lv_style_btn_pr);
	style5_list_mp3.body.main_color = lv_color_hex(0x4456c6);
	style5_list_mp3.body.grad_color = lv_color_hex(0x4456c6);
	style5_list_mp3.body.radius = 0;
	style5_list_mp3.body.border.color = lv_color_hex(0x4456c6);
	style5_list_mp3.body.border.width = 0;
	style5_list_mp3.body.border.opa = 255;
	style5_list_mp3.body.shadow.color = lv_color_hex(0x4456c6);
	style5_list_mp3.text.line_space = 2;

	ui->list_mp3 = lv_list_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->list_mp3, 19, 31);
	lv_obj_set_size(ui->list_mp3, 190, 310);
	lv_list_set_single_mode(ui->list_mp3, true);
	lv_list_set_scroll_propagation(ui->list_mp3, false);
	lv_list_set_edge_flash(ui->list_mp3, false);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_BG, &style0_list_mp3);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_SCRL, &style1_list_mp3);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_BTN_REL, &style4_list_mp3);
	lv_list_set_style(ui->list_mp3, LV_LIST_STYLE_BTN_PR, &style5_list_mp3);
#endif // LV_USE_LIST

}

void music_ui_destory(music_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_xunhuan_xunhuanmoshi_png);
}

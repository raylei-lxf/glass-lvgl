/******************************************************************************
*    includes
******************************************************************************/
#include "ui_music.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_music;
static lv_style_t style0_cont_1;
static lv_style_t style0_cont_music_list;
static lv_style_t style0_cont_music_process;
static lv_style_t style0_cont_music_process_bak;
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

static void *img_music_title_tubiaoyinyue1_png = NULL;
static void *img_2_xunhuanmoshi_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void music_ui_create(music_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music, &lv_style_pretty);
	style0_cont_music.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_music.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_music.body.radius = 0;
	style0_cont_music.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_music.body.border.width = 0;
	style0_cont_music.body.border.opa = 255;

	ui->cont_music = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_music, 0, 0);
	lv_obj_set_size(ui->cont_music, 480, 360);
	lv_cont_set_fit4(ui->cont_music, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music, LV_CONT_STYLE_MAIN, &style0_cont_music);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_1, &lv_style_pretty);
	style0_cont_1.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_1.body.radius = 0;
	style0_cont_1.body.border.color = lv_color_hex(0xffffff);
	style0_cont_1.body.border.width = 0;
	style0_cont_1.body.border.opa = 255;

	ui->cont_1 = lv_cont_create(ui->cont_music, NULL);
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

	ui->cont_music_list = lv_cont_create(ui->cont_music, NULL);
	lv_obj_set_pos(ui->cont_music_list, 14, 33);
	lv_obj_set_size(ui->cont_music_list, 198, 45);
	lv_cont_set_fit4(ui->cont_music_list, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_music_list, LV_CONT_STYLE_MAIN, &style0_cont_music_list);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_music_title = lv_img_create(ui->cont_music_list, NULL);
	lv_obj_set_pos(ui->img_music_title, 9, 9);
	lv_obj_set_size(ui->img_music_title, 24, 27);
	img_music_title_tubiaoyinyue1_png = (void *)mal_load_image(LV_IMAGE_PATH"tubiaoyinyue1.png");
	lv_img_set_src(ui->img_music_title, img_music_title_tubiaoyinyue1_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_music_title = lv_label_create(ui->cont_music_list, NULL);
	lv_label_set_text(ui->label_music_title, "Text");
	lv_label_set_long_mode(ui->label_music_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music_title, 47, 7);
	lv_obj_set_size(ui->label_music_title, 114, 32);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_music_process, &lv_style_pretty);
	style0_cont_music_process.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_music_process.body.radius = 0;
	style0_cont_music_process.body.border.color = lv_color_hex(0xffffff);
	style0_cont_music_process.body.border.width = 0;
	style0_cont_music_process.body.border.opa = 255;

	ui->cont_music_process = lv_cont_create(ui->cont_music, NULL);
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
	ui->label_music_start = lv_label_create(ui->cont_music, NULL);
	lv_label_set_text(ui->label_music_start, "00:16");
	lv_label_set_long_mode(ui->label_music_start, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music_start, 237, 261);
	lv_obj_set_size(ui->label_music_start, 48, 21);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	ui->label_music_totle = lv_label_create(ui->cont_music, NULL);
	lv_label_set_text(ui->label_music_totle, "02:58");
	lv_label_set_long_mode(ui->label_music_totle, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music_totle, 411, 261);
	lv_obj_set_size(ui->label_music_totle, 47, 23);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_5, &lv_style_pretty);
	style0_cont_5.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_5.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_5.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_5.body.border.width = 0;

	ui->cont_5 = lv_cont_create(ui->cont_music, NULL);
	lv_obj_set_pos(ui->cont_5, 248, 30);
	lv_obj_set_size(ui->cont_5, 220, 208);
	lv_cont_set_fit4(ui->cont_5, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_5, LV_CONT_STYLE_MAIN, &style0_cont_5);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_2 = lv_img_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->img_2, 59, 22);
	lv_obj_set_size(ui->img_2, 28, 26);
	img_2_xunhuanmoshi_png = (void *)mal_load_image(LV_IMAGE_PATH"xunhuanmoshi.png");
	lv_img_set_src(ui->img_2, img_2_xunhuanmoshi_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_4 = lv_label_create(ui->cont_5, NULL);
	lv_label_set_text(ui->label_4, "01/04");
	lv_label_set_long_mode(ui->label_4, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_4, 115, 23);
	lv_obj_set_size(ui->label_4, 70, 29);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_6, &lv_style_pretty);
	style0_cont_6.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_6.body.radius = 0;
	style0_cont_6.body.border.color = lv_color_hex(0xffffff);
	style0_cont_6.body.border.width = 0;

	ui->cont_6 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_6, 18, 195);
	lv_obj_set_size(ui->cont_6, 25, 8);
	lv_cont_set_fit4(ui->cont_6, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_6, LV_CONT_STYLE_MAIN, &style0_cont_6);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_7, &lv_style_pretty);
	style0_cont_7.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_7.body.radius = 0;
	style0_cont_7.body.border.color = lv_color_hex(0xffffff);
	style0_cont_7.body.border.width = 0;

	ui->cont_7 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_7, 55, 194);
	lv_obj_set_size(ui->cont_7, 25, 8);
	lv_cont_set_fit4(ui->cont_7, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_7, LV_CONT_STYLE_MAIN, &style0_cont_7);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_8, &lv_style_pretty);
	style0_cont_8.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_8.body.radius = 0;
	style0_cont_8.body.border.color = lv_color_hex(0xffffff);
	style0_cont_8.body.border.width = 0;

	ui->cont_8 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_8, 128, 79);
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

	ui->cont_9 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_9, 17, 71);
	lv_obj_set_size(ui->cont_9, 25, 8);
	lv_cont_set_fit4(ui->cont_9, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_9, LV_CONT_STYLE_MAIN, &style0_cont_9);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_10, &lv_style_pretty);
	style0_cont_10.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_10.body.radius = 0;
	style0_cont_10.body.border.color = lv_color_hex(0xffffff);
	style0_cont_10.body.border.width = 0;

	ui->cont_10 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_10, 14, 98);
	lv_obj_set_size(ui->cont_10, 25, 8);
	lv_cont_set_fit4(ui->cont_10, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_10, LV_CONT_STYLE_MAIN, &style0_cont_10);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_11, &lv_style_pretty);
	style0_cont_11.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_11.body.radius = 0;
	style0_cont_11.body.border.color = lv_color_hex(0xffffff);
	style0_cont_11.body.border.width = 0;

	ui->cont_11 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_11, 13, 130);
	lv_obj_set_size(ui->cont_11, 25, 8);
	lv_cont_set_fit4(ui->cont_11, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_11, LV_CONT_STYLE_MAIN, &style0_cont_11);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_12, &lv_style_pretty);
	style0_cont_12.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_12.body.radius = 0;
	style0_cont_12.body.border.color = lv_color_hex(0xffffff);
	style0_cont_12.body.border.width = 0;

	ui->cont_12 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_12, 15, 158);
	lv_obj_set_size(ui->cont_12, 25, 8);
	lv_cont_set_fit4(ui->cont_12, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_12, LV_CONT_STYLE_MAIN, &style0_cont_12);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_13, &lv_style_pretty);
	style0_cont_13.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_13.body.radius = 0;
	style0_cont_13.body.border.color = lv_color_hex(0xffffff);
	style0_cont_13.body.border.width = 0;

	ui->cont_13 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_13, 56, 160);
	lv_obj_set_size(ui->cont_13, 25, 8);
	lv_cont_set_fit4(ui->cont_13, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_13, LV_CONT_STYLE_MAIN, &style0_cont_13);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_14, &lv_style_pretty);
	style0_cont_14.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_14.body.radius = 0;
	style0_cont_14.body.border.color = lv_color_hex(0xffffff);
	style0_cont_14.body.border.width = 0;

	ui->cont_14 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_14, 54, 130);
	lv_obj_set_size(ui->cont_14, 25, 8);
	lv_cont_set_fit4(ui->cont_14, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_14, LV_CONT_STYLE_MAIN, &style0_cont_14);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_15, &lv_style_pretty);
	style0_cont_15.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_15.body.radius = 0;
	style0_cont_15.body.border.color = lv_color_hex(0xffffff);
	style0_cont_15.body.border.width = 0;

	ui->cont_15 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_15, 55, 103);
	lv_obj_set_size(ui->cont_15, 25, 8);
	lv_cont_set_fit4(ui->cont_15, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_15, LV_CONT_STYLE_MAIN, &style0_cont_15);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_16, &lv_style_pretty);
	style0_cont_16.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_16.body.radius = 0;
	style0_cont_16.body.border.color = lv_color_hex(0xffffff);
	style0_cont_16.body.border.width = 0;

	ui->cont_16 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_16, 98, 195);
	lv_obj_set_size(ui->cont_16, 25, 8);
	lv_cont_set_fit4(ui->cont_16, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_16, LV_CONT_STYLE_MAIN, &style0_cont_16);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_17, &lv_style_pretty);
	style0_cont_17.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_17.body.radius = 0;
	style0_cont_17.body.border.color = lv_color_hex(0xffffff);
	style0_cont_17.body.border.width = 0;

	ui->cont_17 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_17, 138, 198);
	lv_obj_set_size(ui->cont_17, 25, 8);
	lv_cont_set_fit4(ui->cont_17, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_17, LV_CONT_STYLE_MAIN, &style0_cont_17);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_18, &lv_style_pretty);
	style0_cont_18.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_18.body.radius = 0;
	style0_cont_18.body.border.color = lv_color_hex(0xffffff);
	style0_cont_18.body.border.width = 0;

	ui->cont_18 = lv_cont_create(ui->cont_5, NULL);
	lv_obj_set_pos(ui->cont_18, 101, 156);
	lv_obj_set_size(ui->cont_18, 25, 8);
	lv_cont_set_fit4(ui->cont_18, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_18, LV_CONT_STYLE_MAIN, &style0_cont_18);
#endif // LV_USE_CONT

}

void music_ui_destory(music_ui_t *ui)
{
	lv_obj_del(ui->cont_music);
	mal_unload_image(img_music_title_tubiaoyinyue1_png);
	mal_unload_image(img_2_xunhuanmoshi_png);
}

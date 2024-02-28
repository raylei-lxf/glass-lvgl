/******************************************************************************
*    includes
******************************************************************************/
#include "ui_home.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_cont_tip;
static lv_style_t style0_cont_tip_line;

static void *img_player_video_png = NULL;
static void *img_photo_photo_png = NULL;
static void *img_music_music_png = NULL;
static void *img_file_wenjiajia_png = NULL;
static void *img_setting_shezhi_png = NULL;
static void *img_phone_shoujihulian_png = NULL;
static void *img_tip_tishi_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void home_ui_create(home_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_main.body.border.width = 1;
	style0_cont_main.body.shadow.color = lv_color_hex(0x4456c6);

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_player = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_player, 40, 20);
	lv_obj_set_size(ui->img_player, 95, 95);
	img_player_video_png = (void *)mal_load_image(LV_IMAGE_PATH"video.png");
	lv_img_set_src(ui->img_player, img_player_video_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_player = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_player, "Test");
	lv_label_set_long_mode(ui->label_player, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player, 60, 120);
	lv_obj_set_size(ui->label_player, 90, 30);
#endif // LV_USE_LABEL

#ifdef LV_USE_IMG
	ui->img_photo = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_photo, 188, 20);
	lv_obj_set_size(ui->img_photo, 95, 95);
	img_photo_photo_png = (void *)mal_load_image(LV_IMAGE_PATH"photo.png");
	lv_img_set_src(ui->img_photo, img_photo_photo_png);

#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	ui->img_music = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_music, 345, 20);
	lv_obj_set_size(ui->img_music, 95, 94);
	img_music_music_png = (void *)mal_load_image(LV_IMAGE_PATH"music.png");
	lv_img_set_src(ui->img_music, img_music_music_png);

#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	ui->img_file = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_file, 52, 175);
	lv_obj_set_size(ui->img_file, 78, 79);
	img_file_wenjiajia_png = (void *)mal_load_image(LV_IMAGE_PATH"wenjiajia.png");
	lv_img_set_src(ui->img_file, img_file_wenjiajia_png);

#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	ui->img_setting = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_setting, 204, 179);
	lv_obj_set_size(ui->img_setting, 74, 76);
	img_setting_shezhi_png = (void *)mal_load_image(LV_IMAGE_PATH"shezhi.png");
	lv_img_set_src(ui->img_setting, img_setting_shezhi_png);

#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	ui->img_phone = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_phone, 358, 178);
	lv_obj_set_size(ui->img_phone, 56, 79);
	img_phone_shoujihulian_png = (void *)mal_load_image(LV_IMAGE_PATH"shoujihulian.png");
	lv_img_set_src(ui->img_phone, img_phone_shoujihulian_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_photo = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_photo, "Test");
	lv_label_set_long_mode(ui->label_photo, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_photo, 208, 120);
	lv_obj_set_size(ui->label_photo, 90, 30);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	ui->label_music = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_music, "Test");
	lv_label_set_long_mode(ui->label_music, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music, 365, 120);
	lv_obj_set_size(ui->label_music, 90, 30);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	ui->label_file = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_file, "Test");
	lv_label_set_long_mode(ui->label_file, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file, 60, 260);
	lv_obj_set_size(ui->label_file, 90, 30);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	ui->label_setting = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_setting, "Test");
	lv_label_set_long_mode(ui->label_setting, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_setting, 208, 260);
	lv_obj_set_size(ui->label_setting, 90, 30);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	ui->label_phone = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_phone, "Test");
	lv_label_set_long_mode(ui->label_phone, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_phone, 365, 262);
	lv_obj_set_size(ui->label_phone, 90, 30);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_tip, &lv_style_pretty);
	style0_cont_tip.body.main_color = lv_color_hex(0x101d6b);
	style0_cont_tip.body.grad_color = lv_color_hex(0x101d6b);
	style0_cont_tip.body.border.width = 0;

	ui->cont_tip = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_tip, 88, 123);
	lv_obj_set_size(ui->cont_tip, 300, 174);
	lv_cont_set_fit4(ui->cont_tip, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_obj_set_hidden(ui->cont_tip,true);
	lv_cont_set_style(ui->cont_tip, LV_CONT_STYLE_MAIN, &style0_cont_tip);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	ui->label_tip_title = lv_label_create(ui->cont_tip, NULL);
	lv_label_set_text(ui->label_tip_title, "Text");
	lv_label_set_long_mode(ui->label_tip_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_title, 0, 34);
	lv_obj_set_size(ui->label_tip_title, 145, 30);
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
	lv_obj_set_pos(ui->img_tip, 5, 40);
	lv_obj_set_size(ui->img_tip, 23, 23);
	img_tip_tishi_png = (void *)mal_load_image(LV_IMAGE_PATH"tishi.png");
	lv_img_set_src(ui->img_tip, img_tip_tishi_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_tip_content = lv_label_create(ui->cont_tip, NULL);
	lv_label_set_text(ui->label_tip_content, "Text");
	lv_label_set_long_mode(ui->label_tip_content, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_content, 0, 0);
	lv_obj_set_size(ui->label_tip_content, 145, 69);
#endif // LV_USE_LABEL

}

void home_ui_destory(home_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_player_video_png);
	mal_unload_image(img_photo_photo_png);
	mal_unload_image(img_music_music_png);
	mal_unload_image(img_file_wenjiajia_png);
	mal_unload_image(img_setting_shezhi_png);
	mal_unload_image(img_phone_shoujihulian_png);
	mal_unload_image(img_tip_tishi_png);
}

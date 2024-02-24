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
static lv_style_t style0_img_player;
static lv_style_t style0_label_player;
static lv_style_t style0_img_photo;
static lv_style_t style0_img_music;
static lv_style_t style0_img_file;
static lv_style_t style0_label_photo;
static lv_style_t style0_label_music;
static lv_style_t style0_label_file;
static lv_style_t style0_label_setting;
static lv_style_t style0_label_phone;
static lv_style_t style0_cont_botton;
static lv_style_t style0_label_vol;
static lv_style_t style0_bar_vol_bag;
static lv_style_t style0_bar_vol_blue;
static lv_style_t style0_cont_tip;
static lv_style_t style0_label_tip_title;
static lv_style_t style0_cont_tip_line;
static lv_style_t style0_label_tip_content;

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
	lv_obj_set_size(ui->cont_main, 480, 355);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_player, &lv_style_plain);

	ui->img_player = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_player, 40, 20);
	lv_obj_set_size(ui->img_player, 95, 95);
	img_player_video_png = (void *)mal_load_image(LV_IMAGE_PATH"video.png");
	lv_img_set_src(ui->img_player, img_player_video_png);

	lv_img_set_style(ui->img_player, LV_IMG_STYLE_MAIN, &style0_img_player);
#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_player, &lv_style_transp);

	ui->label_player = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_player, "Test");
	lv_label_set_long_mode(ui->label_player, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_player, 60, 120);
	lv_obj_set_size(ui->label_player, 90, 30);
	lv_label_set_style(ui->label_player, LV_LABEL_STYLE_MAIN, &style0_label_player);
#endif // LV_USE_LABEL

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_photo, &lv_style_plain);

	ui->img_photo = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_photo, 188, 20);
	lv_obj_set_size(ui->img_photo, 95, 95);
	img_photo_photo_png = (void *)mal_load_image(LV_IMAGE_PATH"photo.png");
	lv_img_set_src(ui->img_photo, img_photo_photo_png);

	lv_img_set_style(ui->img_photo, LV_IMG_STYLE_MAIN, &style0_img_photo);
#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_music, &lv_style_plain);

	ui->img_music = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_music, 345, 20);
	lv_obj_set_size(ui->img_music, 95, 94);
	img_music_music_png = (void *)mal_load_image(LV_IMAGE_PATH"music.png");
	lv_img_set_src(ui->img_music, img_music_music_png);

	lv_img_set_style(ui->img_music, LV_IMG_STYLE_MAIN, &style0_img_music);
#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_file, &lv_style_plain);

	ui->img_file = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_file, 52, 175);
	lv_obj_set_size(ui->img_file, 78, 79);
	img_file_wenjiajia_png = (void *)mal_load_image(LV_IMAGE_PATH"wenjiajia.png");
	lv_img_set_src(ui->img_file, img_file_wenjiajia_png);

	lv_img_set_style(ui->img_file, LV_IMG_STYLE_MAIN, &style0_img_file);
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
	lv_style_copy(&style0_label_photo, &lv_style_transp);

	ui->label_photo = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_photo, "Test");
	lv_label_set_long_mode(ui->label_photo, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_photo, 208, 120);
	lv_obj_set_size(ui->label_photo, 90, 30);
	lv_label_set_style(ui->label_photo, LV_LABEL_STYLE_MAIN, &style0_label_photo);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_music, &lv_style_transp);

	ui->label_music = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_music, "Test");
	lv_label_set_long_mode(ui->label_music, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_music, 365, 120);
	lv_obj_set_size(ui->label_music, 90, 30);
	lv_label_set_style(ui->label_music, LV_LABEL_STYLE_MAIN, &style0_label_music);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_file, &lv_style_transp);

	ui->label_file = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_file, "Test");
	lv_label_set_long_mode(ui->label_file, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file, 60, 260);
	lv_obj_set_size(ui->label_file, 90, 30);
	lv_label_set_style(ui->label_file, LV_LABEL_STYLE_MAIN, &style0_label_file);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_setting, &lv_style_transp);

	ui->label_setting = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_setting, "Test");
	lv_label_set_long_mode(ui->label_setting, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_setting, 208, 260);
	lv_obj_set_size(ui->label_setting, 90, 30);
	lv_label_set_style(ui->label_setting, LV_LABEL_STYLE_MAIN, &style0_label_setting);
#endif // LV_USE_LABEL

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_phone, &lv_style_transp);

	ui->label_phone = lv_label_create(ui->cont_main, NULL);
	lv_label_set_text(ui->label_phone, "Test");
	lv_label_set_long_mode(ui->label_phone, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_phone, 365, 262);
	lv_obj_set_size(ui->label_phone, 90, 30);
	lv_label_set_style(ui->label_phone, LV_LABEL_STYLE_MAIN, &style0_label_phone);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_botton, &lv_style_pretty);
	style0_cont_botton.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_botton.body.radius = 0;
	style0_cont_botton.body.border.color = lv_color_hex(0xffffff);
	style0_cont_botton.body.shadow.color = lv_color_hex(0xffffff);

	ui->cont_botton = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_botton, 3, 327);
	lv_obj_set_size(ui->cont_botton, 473, 33);
	lv_cont_set_fit4(ui->cont_botton, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_botton, LV_CONT_STYLE_MAIN, &style0_cont_botton);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_vol, &lv_style_transp);
	style0_label_vol.text.color = lv_color_hex(0x444444);
	style0_label_vol.text.line_space = 2;

	ui->label_vol = lv_label_create(ui->cont_botton, NULL);
	lv_label_set_text(ui->label_vol, "VOL");
	lv_label_set_long_mode(ui->label_vol, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_vol, 6, 6);
	lv_obj_set_size(ui->label_vol, 94, 22);
	lv_label_set_style(ui->label_vol, LV_LABEL_STYLE_MAIN, &style0_label_vol);
#endif // LV_USE_LABEL

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_vol_bag, &lv_style_pretty);
	style0_bar_vol_bag.body.main_color = lv_color_hex(0x3244b5);
	style0_bar_vol_bag.body.grad_color = lv_color_hex(0x3244b5);
	style0_bar_vol_bag.body.radius = 0;
	style0_bar_vol_bag.body.opa = 0;
	style0_bar_vol_bag.body.border.color = lv_color_hex(0x3244b5);
	style0_bar_vol_bag.body.border.opa = 255;
	style0_bar_vol_bag.body.shadow.color = lv_color_hex(0xcccccc);

	ui->bar_vol_bag = lv_bar_create(ui->cont_botton, NULL);
	lv_obj_set_pos(ui->bar_vol_bag, 118, 6);
	lv_obj_set_size(ui->bar_vol_bag, 248, 21);
	lv_bar_set_range(ui->bar_vol_bag, 0, 100);
	lv_bar_set_value(ui->bar_vol_bag, 100, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_vol_bag, LV_BAR_STYLE_BG, &style0_bar_vol_bag);
#endif // LV_USE_BAR

#ifdef LV_USE_BAR
	lv_style_copy(&style0_bar_vol_blue, &lv_style_pretty);
	style0_bar_vol_blue.body.main_color = lv_color_hex(0xcccccc);
	style0_bar_vol_blue.body.grad_color = lv_color_hex(0xcccccc);
	style0_bar_vol_blue.body.radius = 0;
	style0_bar_vol_blue.body.border.color = lv_color_hex(0xcccccc);
	style0_bar_vol_blue.body.border.opa = 255;

	ui->bar_vol_blue = lv_bar_create(ui->bar_vol_bag, NULL);
	lv_obj_set_pos(ui->bar_vol_blue, 0, 0);
	lv_obj_set_size(ui->bar_vol_blue, 248, 21);
	lv_bar_set_range(ui->bar_vol_blue, 0, 100);
	lv_bar_set_value(ui->bar_vol_blue, 60, LV_ANIM_OFF);
	lv_bar_set_style(ui->bar_vol_blue, LV_BAR_STYLE_BG, &style0_bar_vol_blue);
#endif // LV_USE_BAR

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_tip, &lv_style_pretty);
	style0_cont_tip.body.main_color = lv_color_hex(0x101d6b);
	style0_cont_tip.body.grad_color = lv_color_hex(0x101d6b);
	style0_cont_tip.body.border.width = 0;

	ui->cont_tip = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_tip, 88, 122);
	lv_obj_set_size(ui->cont_tip, 300, 174);
	lv_cont_set_fit4(ui->cont_tip, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_obj_set_hidden(ui->cont_tip,true);
	lv_cont_set_style(ui->cont_tip, LV_CONT_STYLE_MAIN, &style0_cont_tip);
#endif // LV_USE_CONT

#ifdef LV_USE_LABEL
	lv_style_copy(&style0_label_tip_title, &lv_style_transp);

	ui->label_tip_title = lv_label_create(ui->cont_tip, NULL);
	lv_label_set_text(ui->label_tip_title, "Text");
	lv_label_set_long_mode(ui->label_tip_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_title, 0, 34);
	lv_obj_set_size(ui->label_tip_title, 145, 30);
	lv_label_set_style(ui->label_tip_title, LV_LABEL_STYLE_MAIN, &style0_label_tip_title);
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
	lv_style_copy(&style0_label_tip_content, &lv_style_transp);

	ui->label_tip_content = lv_label_create(ui->cont_tip, NULL);
	lv_label_set_text(ui->label_tip_content, "Text");
	lv_label_set_long_mode(ui->label_tip_content, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_tip_content, 0, 0);
	lv_obj_set_size(ui->label_tip_content, 145, 69);
	lv_label_set_style(ui->label_tip_content, LV_LABEL_STYLE_MAIN, &style0_label_tip_content);
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

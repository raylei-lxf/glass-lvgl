/******************************************************************************
*    includes
******************************************************************************/
#include "ui_photo.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_img_photo;
static lv_style_t style0_cont_1;

static void *img_photo_tutest_jpg = NULL;
static void *img_photo_show_photo_playering_baground_png = NULL;
static void *img_photo_ing_photo_playing_png = NULL;
static void *img_photo_line_photo_playing_line_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void photo_ui_create(photo_ui_t *ui)
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

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_photo, &lv_style_plain);

	ui->img_photo = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_photo, 0, 0);
	lv_obj_set_size(ui->img_photo, 480, 360);
	img_photo_tutest_jpg = (void *)mal_load_image(LV_IMAGE_PATH"tutest.jpg");
	lv_img_set_src(ui->img_photo, img_photo_tutest_jpg);

	lv_img_set_style(ui->img_photo, LV_IMG_STYLE_MAIN, &style0_img_photo);
#endif // LV_USE_IMG

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_1, &lv_style_pretty);
	style0_cont_1.body.opa = 0;
	style0_cont_1.body.border.opa = 0;

	ui->cont_1 = lv_cont_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->cont_1, 403, 4);
	lv_obj_set_size(ui->cont_1, 77, 43);
	lv_cont_set_fit4(ui->cont_1, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_1, LV_CONT_STYLE_MAIN, &style0_cont_1);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_photo_show = lv_img_create(ui->cont_1, NULL);
	lv_obj_set_pos(ui->img_photo_show, 0, 0);
	lv_obj_set_size(ui->img_photo_show, 71, 35);
	img_photo_show_photo_playering_baground_png = (void *)mal_load_image(LV_IMAGE_PATH"photo_playering_baground.png");
	lv_img_set_src(ui->img_photo_show, img_photo_show_photo_playering_baground_png);

#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	ui->img_photo_ing = lv_img_create(ui->img_photo_show, NULL);
	lv_obj_set_pos(ui->img_photo_ing, 13, 6);
	lv_obj_set_size(ui->img_photo_ing, 21, 24);
	img_photo_ing_photo_playing_png = (void *)mal_load_image(LV_IMAGE_PATH"photo_playing.png");
	lv_img_set_src(ui->img_photo_ing, img_photo_ing_photo_playing_png);

#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	ui->img_photo_line = lv_img_create(ui->img_photo_show, NULL);
	lv_obj_set_pos(ui->img_photo_line, 37, 17);
	lv_obj_set_size(ui->img_photo_line, 30, 2);
	img_photo_line_photo_playing_line_png = (void *)mal_load_image(LV_IMAGE_PATH"photo_playing_line.png");
	lv_img_set_src(ui->img_photo_line, img_photo_line_photo_playing_line_png);

#endif // LV_USE_IMG

}

void photo_ui_destory(photo_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
	mal_unload_image(img_photo_tutest_jpg);
	mal_unload_image(img_photo_show_photo_playering_baground_png);
	mal_unload_image(img_photo_ing_photo_playing_png);
	mal_unload_image(img_photo_line_photo_playing_line_png);
}

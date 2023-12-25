/******************************************************************************
*    includes
******************************************************************************/
#include "ui_photo.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_photo;
static lv_style_t style0_img_photo_show;
static lv_style_t style0_img_photo_ing;
static lv_style_t style0_img_photo_line;

static void *img_photo_show_photo_playering_baground_png = NULL;
static void *img_photo_ing_photo_playing_png = NULL;
static void *img_photo_line_photo_playing_line_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void photo_ui_create(photo_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_photo, &lv_style_pretty);
	style0_cont_photo.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_photo.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_photo.body.radius = 0;
	style0_cont_photo.body.border.color = lv_color_hex(0x4456c6);
	style0_cont_photo.body.border.width = 0;
	style0_cont_photo.body.border.opa = 255;

	ui->cont_photo = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_photo, 0, 0);
	lv_obj_set_size(ui->cont_photo, 480, 360);
	lv_cont_set_fit4(ui->cont_photo, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_photo, LV_CONT_STYLE_MAIN, &style0_cont_photo);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_photo_show, &lv_style_plain);

	ui->img_photo_show = lv_img_create(ui->cont_photo, NULL);
	lv_obj_set_pos(ui->img_photo_show, 397, 13);
	lv_obj_set_size(ui->img_photo_show, 71, 35);
	img_photo_show_photo_playering_baground_png = (void *)mal_load_image(LV_IMAGE_PATH"photo_playering_baground.png");
	lv_img_set_src(ui->img_photo_show, img_photo_show_photo_playering_baground_png);

	lv_img_set_style(ui->img_photo_show, LV_IMG_STYLE_MAIN, &style0_img_photo_show);
#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_photo_ing, &lv_style_plain);

	ui->img_photo_ing = lv_img_create(ui->img_photo_show, NULL);
	lv_obj_set_pos(ui->img_photo_ing, 5, 6);
	lv_obj_set_size(ui->img_photo_ing, 21, 24);
	img_photo_ing_photo_playing_png = (void *)mal_load_image(LV_IMAGE_PATH"photo_playing.png");
	lv_img_set_src(ui->img_photo_ing, img_photo_ing_photo_playing_png);

	lv_img_set_style(ui->img_photo_ing, LV_IMG_STYLE_MAIN, &style0_img_photo_ing);
#endif // LV_USE_IMG

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_photo_line, &lv_style_plain);

	ui->img_photo_line = lv_img_create(ui->img_photo_show, NULL);
	lv_obj_set_pos(ui->img_photo_line, 37, 17);
	lv_obj_set_size(ui->img_photo_line, 30, 2);
	img_photo_line_photo_playing_line_png = (void *)mal_load_image(LV_IMAGE_PATH"photo_playing_line.png");
	lv_img_set_src(ui->img_photo_line, img_photo_line_photo_playing_line_png);

	lv_img_set_style(ui->img_photo_line, LV_IMG_STYLE_MAIN, &style0_img_photo_line);
#endif // LV_USE_IMG

}

void photo_ui_destory(photo_ui_t *ui)
{
	lv_obj_del(ui->cont_photo);
	mal_unload_image(img_photo_show_photo_playering_baground_png);
	mal_unload_image(img_photo_ing_photo_playing_png);
	mal_unload_image(img_photo_line_photo_playing_line_png);
}

/******************************************************************************
*    includes
******************************************************************************/
#include "ui_file.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_file;
static lv_style_t style0_cont_file_line;
static lv_style_t style0_cont_file_photo;
static lv_style_t style0_cont_file_imge;
static lv_style_t style0_cont_file_video;

static void *img_file_title_file_title_png = NULL;
static void *img_file_photo_pictubiao1_png = NULL;
static void *img_file_imge_pictubiao_png = NULL;
static void *img_file_video_videotubiao_png = NULL;

/******************************************************************************
*    functions
******************************************************************************/
void file_ui_create(file_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_file, &lv_style_pretty);
	style0_cont_file.body.main_color = lv_color_hex(0x4456c6);
	style0_cont_file.body.grad_color = lv_color_hex(0x4456c6);
	style0_cont_file.body.radius = 0;
	style0_cont_file.body.border.color = lv_color_hex(0xffffff);
	style0_cont_file.body.border.width = 0;

	ui->cont_file = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_file, 0, 0);
	lv_obj_set_size(ui->cont_file, 480, 360);
	lv_cont_set_fit4(ui->cont_file, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_file, LV_CONT_STYLE_MAIN, &style0_cont_file);
#endif // LV_USE_CONT

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_file_line, &lv_style_pretty);
	style0_cont_file_line.body.grad_color = lv_color_hex(0xffffff);
	style0_cont_file_line.body.radius = 0;
	style0_cont_file_line.body.border.color = lv_color_hex(0xffffff);
	style0_cont_file_line.body.border.width = 0;

	ui->cont_file_line = lv_cont_create(ui->cont_file, NULL);
	lv_obj_set_pos(ui->cont_file_line, 0, 48);
	lv_obj_set_size(ui->cont_file_line, 480, 2);
	lv_cont_set_fit4(ui->cont_file_line, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_file_line, LV_CONT_STYLE_MAIN, &style0_cont_file_line);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_file_title = lv_img_create(ui->cont_file, NULL);
	lv_obj_set_pos(ui->img_file_title, 15, 7);
	lv_obj_set_size(ui->img_file_title, 35, 36);
	img_file_title_file_title_png = (void *)mal_load_image(LV_IMAGE_PATH"file_title.png");
	lv_img_set_src(ui->img_file_title, img_file_title_file_title_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_file_title = lv_label_create(ui->cont_file, NULL);
	lv_label_set_text(ui->label_file_title, "Text");
	lv_label_set_long_mode(ui->label_file_title, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file_title, 59, 9);
	lv_obj_set_size(ui->label_file_title, 115, 36);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_file_photo, &lv_style_pretty);
	style0_cont_file_photo.body.main_color = lv_color_hex(0x101d6b);
	style0_cont_file_photo.body.grad_color = lv_color_hex(0x101d6b);
	style0_cont_file_photo.body.radius = 0;
	style0_cont_file_photo.body.border.color = lv_color_hex(0xffffff);
	style0_cont_file_photo.body.border.width = 1;
	style0_cont_file_photo.body.border.opa = 255;

	ui->cont_file_photo = lv_cont_create(ui->cont_file, NULL);
	lv_obj_set_pos(ui->cont_file_photo, 5, 62);
	lv_obj_set_size(ui->cont_file_photo, 470, 43);
	lv_cont_set_fit4(ui->cont_file_photo, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_file_photo, LV_CONT_STYLE_MAIN, &style0_cont_file_photo);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_file_photo = lv_img_create(ui->cont_file_photo, NULL);
	lv_obj_set_pos(ui->img_file_photo, 10, 8);
	lv_obj_set_size(ui->img_file_photo, 30, 30);
	img_file_photo_pictubiao1_png = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao1.png");
	lv_img_set_src(ui->img_file_photo, img_file_photo_pictubiao1_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_file_photo = lv_label_create(ui->cont_file_photo, NULL);
	lv_label_set_text(ui->label_file_photo, "Text");
	lv_label_set_long_mode(ui->label_file_photo, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file_photo, 45, 5);
	lv_obj_set_size(ui->label_file_photo, 118, 33);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_file_imge, &lv_style_pretty);
	style0_cont_file_imge.body.main_color = lv_color_hex(0x101d6b);
	style0_cont_file_imge.body.grad_color = lv_color_hex(0x101d6b);
	style0_cont_file_imge.body.radius = 0;
	style0_cont_file_imge.body.border.color = lv_color_hex(0xffffff);
	style0_cont_file_imge.body.border.width = 1;
	style0_cont_file_imge.body.border.opa = 255;

	ui->cont_file_imge = lv_cont_create(ui->cont_file, NULL);
	lv_obj_set_pos(ui->cont_file_imge, 4, 115);
	lv_obj_set_size(ui->cont_file_imge, 470, 43);
	lv_cont_set_fit4(ui->cont_file_imge, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_file_imge, LV_CONT_STYLE_MAIN, &style0_cont_file_imge);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_file_imge = lv_img_create(ui->cont_file_imge, NULL);
	lv_obj_set_pos(ui->img_file_imge, 10, 8);
	lv_obj_set_size(ui->img_file_imge, 30, 30);
	img_file_imge_pictubiao_png = (void *)mal_load_image(LV_IMAGE_PATH"pictubiao.png");
	lv_img_set_src(ui->img_file_imge, img_file_imge_pictubiao_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_file_imge = lv_label_create(ui->cont_file_imge, NULL);
	lv_label_set_text(ui->label_file_imge, "Text");
	lv_label_set_long_mode(ui->label_file_imge, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file_imge, 45, 5);
	lv_obj_set_size(ui->label_file_imge, 118, 33);
#endif // LV_USE_LABEL

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_file_video, &lv_style_pretty);
	style0_cont_file_video.body.main_color = lv_color_hex(0x101d6b);
	style0_cont_file_video.body.grad_color = lv_color_hex(0x101d6b);
	style0_cont_file_video.body.radius = 0;
	style0_cont_file_video.body.border.color = lv_color_hex(0xffffff);
	style0_cont_file_video.body.border.width = 1;
	style0_cont_file_video.body.border.opa = 255;

	ui->cont_file_video = lv_cont_create(ui->cont_file, NULL);
	lv_obj_set_pos(ui->cont_file_video, 4, 168);
	lv_obj_set_size(ui->cont_file_video, 470, 43);
	lv_cont_set_fit4(ui->cont_file_video, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_file_video, LV_CONT_STYLE_MAIN, &style0_cont_file_video);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	ui->img_file_video = lv_img_create(ui->cont_file_video, NULL);
	lv_obj_set_pos(ui->img_file_video, 10, 8);
	lv_obj_set_size(ui->img_file_video, 30, 30);
	img_file_video_videotubiao_png = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao.png");
	lv_img_set_src(ui->img_file_video, img_file_video_videotubiao_png);

#endif // LV_USE_IMG

#ifdef LV_USE_LABEL
	ui->label_file_video = lv_label_create(ui->cont_file_video, NULL);
	lv_label_set_text(ui->label_file_video, "Text");
	lv_label_set_long_mode(ui->label_file_video, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(ui->label_file_video, 45, 5);
	lv_obj_set_size(ui->label_file_video, 118, 33);
#endif // LV_USE_LABEL

}

void file_ui_destory(file_ui_t *ui)
{
	lv_obj_del(ui->cont_file);
	mal_unload_image(img_file_title_file_title_png);
	mal_unload_image(img_file_photo_pictubiao1_png);
	mal_unload_image(img_file_imge_pictubiao_png);
	mal_unload_image(img_file_video_videotubiao_png);
}

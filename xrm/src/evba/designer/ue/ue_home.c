/******************************************************************************
*    includes
******************************************************************************/
#include "ui_home.h"
#include "ui_resource.h"
#include "public.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/******************************************************************************
*   marc 
******************************************************************************/
/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} home_ue_t;

typedef struct
{
	home_ui_t ui;
	home_ue_t ue;
} home_para_t;
static home_para_t *para = NULL;

void *img_src[6] = {NULL};
void *img_srcxz[6] = {NULL};

/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_HOME, WINDOW_HOME);
	}
}

static void home_ue_create(home_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void home_ue_destory(home_para_t *para)
{
	(void)para;
	return;
}


#define FOCUS_PLAYER  0
#define FOCUS_PHOTO  1
#define FOCUS_MUSIC  2
#define FOCUS_FILE  3
#define FOCUS_SETTING  4
#define FOCUS_HPONE  5
#define gbMax  6

static int guangbiao = 0;


lv_obj_t *get_guanbiao_widget(int gb)
{
	home_ui_t *ui = &para->ui;

	
	switch(guangbiao)
	{
		case FOCUS_PLAYER:
		return ui->img_player;
		case FOCUS_PHOTO:
		return ui->img_photo;
		case FOCUS_MUSIC:
		return ui->img_music;
		case FOCUS_FILE:
		return ui->img_file;
		case FOCUS_SETTING:
		return ui->img_setting;
		case FOCUS_HPONE:
		return ui->img_phone;
		default: return NULL;
	}
}

static void key_confirm_callback(void)
{
	app_info("......guangbiao = %d\n", guangbiao);
	if (guangbiao == FOCUS_PLAYER) {
    	switch_window(WINDOW_HOME, WINDOW_PLAYER);
	} else if (guangbiao == FOCUS_PHOTO) {
		switch_window(WINDOW_HOME, WINDOW_PHOTO);
	} else if (guangbiao == FOCUS_MUSIC) {
		switch_window(WINDOW_HOME, WINDOW_MUSIC);
	} else if (guangbiao == FOCUS_FILE) {
		switch_window(WINDOW_HOME, WINDOW_FILE);
	} else if (guangbiao == FOCUS_SETTING) {
		switch_window(WINDOW_HOME, WINDOW_SETTING);
	} else if (guangbiao == FOCUS_HPONE) {
		// switch_window(WINDOW_HOME, WINDOW_PHOTO);
	}	
}

static void key_left_callback(void)
{

	lv_img_set_src(get_guanbiao_widget(guangbiao), img_src[guangbiao]);

	guangbiao--;
	if(guangbiao < 0)
	{
	 	guangbiao = gbMax - 1;
	}
	
	app_info("guangbiao = %d\n", guangbiao);
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);

}


static void key_right_callback(void)
{

	lv_img_set_src(get_guanbiao_widget(guangbiao), img_src[guangbiao]);
	
	app_info("\n");
	guangbiao++;
	if(guangbiao >= gbMax)
	{
		guangbiao = 0;
	}
	
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);

}

void load_image()
{
	home_ui_t *ui = &para->ui;

	img_srcxz[0] = (void *)mal_load_image(LV_IMAGE_PATH"videoxuanzhong.png");
	img_srcxz[1] = (void *)mal_load_image(LV_IMAGE_PATH"photoxuanzhong.png");
	img_srcxz[2] = (void *)mal_load_image(LV_IMAGE_PATH"musicxuanzhong.png");
	img_srcxz[3] = (void *)mal_load_image(LV_IMAGE_PATH"wenjiajiaxuanzhong.png");
	img_srcxz[4] = (void *)mal_load_image(LV_IMAGE_PATH"shezhixuanzhong.png");
	img_srcxz[5] = (void *)mal_load_image(LV_IMAGE_PATH"shoujihulianxuanzhong.png");

	img_src[0] = lv_img_get_src(ui->img_player);
	img_src[1] = lv_img_get_src(ui->img_photo);
	img_src[2] = lv_img_get_src(ui->img_music);	
	img_src[3] = lv_img_get_src(ui->img_file);	
	img_src[4] = lv_img_get_src(ui->img_setting);	
	img_src[5] = lv_img_get_src(ui->img_phone);
}

void unload_image()
{
	mal_unload_image(img_srcxz[0]);
	mal_unload_image(img_srcxz[1]);
	mal_unload_image(img_srcxz[2]);
	mal_unload_image(img_srcxz[3]);
	mal_unload_image(img_srcxz[4]);
	mal_unload_image(img_srcxz[5]);
}

static int home_create(void)
{
	para = (home_para_t *)malloc(sizeof(home_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(home_para_t));

	para->ui.parent = lv_scr_act();
	home_ui_create(&para->ui);
	home_ue_create(para);

	load_image();
	
	lv_img_set_src(get_guanbiao_widget(guangbiao), img_srcxz[guangbiao]);
	key_callback_register(LV_KEY_1, key_confirm_callback);

	key_callback_register(LV_KEY_3, key_left_callback);
	key_callback_register(LV_KEY_4, key_right_callback);
	return 0;
}

static int home_destory(void)
{
	home_ue_destory(para);
	home_ui_destory(&para->ui);
	free(para);
	para = NULL;
	key_callback_unregister();

	unload_image();
	app_info("home_destory ........");
	return 0;
}

static int home_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int home_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t home_window = 
{
	.ops =
	{
		home_create,
		home_destory,
		home_show,
		home_hide
	}, 
	.data =
	{
		.id         = WINDOW_HOME, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_HOME(void)
{
	register_window(&home_window);
}

/******************************************************************************
*    includes
******************************************************************************/
#include "ui_photo.h"
#include "ui_resource.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} photo_ue_t;

typedef struct
{
	photo_ui_t ui;
	photo_ue_t ue;
} photo_para_t;
static photo_para_t *para = NULL;

char photo_name[512] = { 0 };
char photo_play_list[100][512] = { 0 };
int photo_index = 0;
int photo_max = 0;
/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_PHOTO, WINDOW_HOME);
	}
}

static void photo_ue_create(photo_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void photo_ue_destory(photo_para_t *para)
{
	(void)para;
	return;
}

static void photo_key_confire_callback(void)
{
    
}

static void photo_key_canel_callback(void)
{
    switch_window(WINDOW_PHOTO, WINDOW_PHOTO_LIST);
}

void *photo_play_srcxz[1] = {NULL};

static void photo_play_load_image(void) 
{
    photo_ui_t *ui = &para->ui;
    lv_obj_t *photo_play = para->ui.img_photo;

	photo_play_srcxz[0] = (void *)mal_load_image(photo_name);
    if(!photo_play_srcxz[0])
    {
        app_err("%s:photo is error\n", photo_name);
        return;
    }

    lv_img_dsc_t *dsc = photo_play_srcxz[0];
//如果图片太大则resize
    if(dsc->header.w > (LV_HOR_RES_MAX) || dsc->header.h > (LV_VER_RES_MAX))
    {
        dsc = resize_image(dsc, LV_HOR_RES_MAX, LV_VER_RES_MAX);
        app_info("w=%d h=%d\n", dsc->header.w, dsc->header.h);
        photo_play_srcxz[0] = dsc;
    }
    
    lv_img_set_src(photo_play, dsc);

//图片居中显示
    int pos_x, pos_y;
    pos_x = (LV_HOR_RES_MAX - dsc->header.w) / 2;
    pos_y = (LV_VER_RES_MAX - dsc->header.h) / 2;
    lv_obj_set_pos(ui->img_photo, pos_x, pos_y);
	lv_obj_set_size(ui->img_photo, dsc->header.w, dsc->header.h);

    lv_obj_move_foreground(para->ui.cont_1);
}


static void photo_play_unload_image(void)
{
    mal_unload_image(photo_play_srcxz[0]);
}

static void photo_key_left_callback(void)
{
    photo_play_unload_image();
    photo_index--;
    if (photo_index < 0) {
        photo_index = photo_max - 1;
    } 
    memset(photo_name, 0, sizeof(photo_name));
    sprintf(photo_name, "%s%s", "/mnt/app/", photo_play_list[photo_index]);
    photo_play_load_image();
}

static void photo_key_right_callback(void)
{
    photo_play_unload_image();
    photo_index++;
    if (photo_index >= photo_max) {
        photo_index = 0;
    }
    memset(photo_name, 0, sizeof(photo_name));
    sprintf(photo_name, "%s%s", "/mnt/app/", photo_play_list[photo_index]);
    photo_play_load_image();
}

static int photo_create(void)
{
	para = (photo_para_t *)malloc(sizeof(photo_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(photo_para_t));

	para->ui.parent = lv_scr_act();
	photo_ui_create(&para->ui);
	photo_ue_create(para);

    // lv_obj_t *tip = para->ui.img_photo_show;
    // lv_obj_set_top(tip, true);

    key_callback_register(LV_KEY_0, photo_key_confire_callback);
    key_callback_register(LV_KEY_4, photo_key_canel_callback);
    key_callback_register(LV_KEY_2, photo_key_left_callback);
    key_callback_register(LV_KEY_3, photo_key_right_callback);

    app_info("photo create......., photo_name = %s\n", photo_name);
    if (access(photo_name, F_OK) != -1) {
        photo_play_load_image();
        // lv_obj_t *photo_play = para->ui.img_photo;
        // lv_img_set_src(photo_play, photo_play_srcxz[0]);
        // lv_obj_set_hidden(photo_play, false);
    }
    
    for (int i = 0; i < photo_max; i++) {
        app_info("photo_play_list[%d] = %s\n", i, photo_play_list[i]);
    }
    app_info("photo_index = %d\n", photo_index);
    
	return 0;
}

static int photo_destory(void)
{
    key_callback_unregister();
	photo_ue_destory(para);
	photo_ui_destory(&para->ui);
	free(para);
	para = NULL;
    photo_play_unload_image();

	return 0;
}

static int photo_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int photo_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t photo_window = 
{
	.ops =
	{
		photo_create,
		photo_destory,
		photo_show,
		photo_hide
	}, 
	.data =
	{
		.id         = WINDOW_PHOTO, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_PHOTO(void)
{
	register_window(&photo_window);
}

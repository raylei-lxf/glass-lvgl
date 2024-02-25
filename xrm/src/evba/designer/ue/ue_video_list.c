/******************************************************************************
*    includes
******************************************************************************/
#include "ui_video_list.h"
#include "ui_resource.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "debug.h"
#include "player_int.h"

/******************************************************************************
*    datas
******************************************************************************/
LV_FONT_DECLARE(chinese)

typedef struct
{
	uint8_t id;
} video_list_ue_t;

typedef struct
{
	video_list_ui_t ui;
	video_list_ue_t ue;
} video_list_para_t;
static video_list_para_t *para = NULL;

void *video_img_srcxz[2] = {NULL};
extern player_t *t113_play;
/******************************************************************************
*    functions
******************************************************************************/
static int video_list_show(void);
static int video_list_hide(void);

#define MAX_VIDEO 100
static int is_playing = 0;
static int m_video_foucs = 0;
static int video_count = 0;
static char* video_Paths[MAX_VIDEO];

extern char player_name[512];

int get_video_list(void)
{
    const char* directory = "/mnt/app";  
    const char* formats[] = { ".mp4" }; 
    
    DIR* dir = opendir(directory);
    if (dir == NULL) {
        app_info("can't open  folderPath：%s\n", directory);
        return -11;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char* extension = strrchr(entry->d_name, '.');
            if (extension != NULL) {
                int i;
                for (i = 0; extension[i]; i++) {
                    extension[i] = tolower(extension[i]);
                }
                
                int num_formats = sizeof(formats) / sizeof(formats[0]);
                int found = 0;
                
                for (i = 0; i < num_formats; i++) {
                    if (strcasecmp(extension, formats[i]) == 0) {
                        found = i+1;
                        break;
                    }
                }
                
                if (found != 0) {
                    video_Paths[video_count] = strdup(entry->d_name);
                    video_count++;
                    if (video_count >= MAX_VIDEO) {
                        app_info("file max\n");
                        break;
                    }
                }
            }
        }
    }
    closedir(dir);
    for (int i = 0; i < video_count; i++) {
        app_info("files: %s\n", video_Paths[i]);
    }
    return 0;
}

void set_video_list(void)
{
    video_list_ui_t *ui = &para->ui;
    for (int i = 0; i < video_count; i++) {
        void *video_list = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao.png");
        lv_list_add_btn(ui->list_video, video_list, video_Paths[i]);
    }
}

static void video_load_image(void) 
{
    video_list_ui_t *ui = &para->ui;

	video_img_srcxz[0] = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao.png");
	video_img_srcxz[1] = (void *)mal_load_image(LV_IMAGE_PATH"videotubiao1.png");
}

static void video_unload_image(void)
{
    mal_unload_image(video_img_srcxz[0]);
	mal_unload_image(video_img_srcxz[1]);
}

void video_set_list_unfocus(lv_obj_t *list, int index)
{
	lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;
    focus_btn = lv_list_get_next_btn(list, NULL);
    for(i = 0; i < index; i++){
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);
	lv_img_set_src(focus_img, video_img_srcxz[0]);
}

void video_set_list_focus(lv_obj_t *list, int index)
{
    lv_obj_t *focus_btn = NULL;
    lv_obj_t *focus_img = NULL;
    int i = 0;

    focus_btn = lv_list_get_next_btn(list, NULL);
    for(i = 0; i < index; i++){
        focus_btn = lv_list_get_next_btn(list, focus_btn);
    }
    focus_img = lv_list_get_btn_img(focus_btn);

	lv_img_set_src(focus_img, video_img_srcxz[1]);
    lv_btn_set_state(focus_btn, LV_BTN_STATE_REL);
    lv_list_set_btn_selected(list, focus_btn);

    sprintf(player_name, "%s%s", "/mnt/app/", video_Paths[index]);
    app_info("player_name = %s\n", player_name);
}

static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_VIDEO_LIST, WINDOW_HOME);
	}
}

static void video_list_ue_create(video_list_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void video_list_ue_destory(video_list_para_t *para)
{
	(void)para;
	return;
}

static void video_key_confire_callback(void)
{
    // switch_window(WINDOW_VIDEO_LIST, WINDOW_PLAYER);
    if (t113_play != NULL && access(player_name , F_OK) != -1) {
		app_info("..........%s\n", player_name);
        // video_list_hide();
		system("dd if=/dev/zero of=/dev/fb0");
		tplayer_play_url(t113_play, player_name);
		tplayer_set_displayrect(t113_play, 0, 0, 480, 360);
		tplayer_play(t113_play);
        is_playing = 1;
	}
}

static void video_key_canel_callback(void)
{
    app_info("is_playing = %d\n", is_playing);
    if (is_playing == 0) {
        switch_window(WINDOW_VIDEO_LIST, WINDOW_HOME);
    } else {
        is_playing = 0;
        // tplayer_stop(t113_play);
        // tplayer_pause(t113_play);
		system("dd if=/dev/zero of=/dev/fb0");
        video_list_show();
    }
}

static void video_key_left_callback(void)
{
    if (is_playing == 0) {
        video_list_ui_t *ui = &para->ui;
        video_set_list_unfocus(ui->list_video, m_video_foucs);

        m_video_foucs++;
        if (m_video_foucs < 0) {
            m_video_foucs = video_count - 1;
        } else if (m_video_foucs >= video_count) {
            m_video_foucs = 0;
        }
        app_info(".......m_foucs = %d\n", m_video_foucs);
        if (video_count > 0) {
            video_set_list_focus(ui->list_video, m_video_foucs);
        }
    }
}

static void video_key_right_callback(void)
{
    if (is_playing == 0) {
    	video_list_ui_t *ui = &para->ui;
        video_set_list_unfocus(ui->list_video, m_video_foucs);

        m_video_foucs--;
        if (m_video_foucs < 0) {
            m_video_foucs = video_count - 1;
        } else if (m_video_foucs >= video_count) {
            m_video_foucs = 0;
        }
        app_info(".......m_foucs = %d\n", m_video_foucs);
        if (video_count > 0) {
            video_set_list_focus(ui->list_video, m_video_foucs);
        }
    }
}

static int video_list_create(void)
{
	para = (video_list_para_t *)malloc(sizeof(video_list_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(video_list_para_t));

	para->ui.parent = lv_scr_act();
	video_list_ui_create(&para->ui);
	video_list_ue_create(para);
	video_load_image();

	get_video_list();
	set_video_list();

	if (video_count > 0) {
        video_list_ui_t *ui = &para->ui;
        video_set_list_focus(ui->list_video, m_video_foucs);
    }

    static lv_style_t style_cn;
    lv_style_copy(&style_cn, &lv_style_pretty_color);
    style_cn.text.font = &chinese;
    style_cn.text.color = LV_COLOR_BLACK;

    lv_obj_set_style(para->ui.label_1, &style_cn);
    lv_label_set_text(para->ui.label_1, "视频");

    // tplayer_init(t113_play, CEDARX_PLAYER);
    key_callback_register(LV_KEY_0, video_key_confire_callback);
    key_callback_register(LV_KEY_4, video_key_canel_callback);

    key_callback_register(LV_KEY_2, video_key_left_callback);
    key_callback_register(LV_KEY_3, video_key_right_callback);

	return 0;
}

static int video_list_destory(void)
{
    key_callback_unregister();
	video_list_ue_destory(para);
	video_list_ui_destory(&para->ui);
	free(para);
	para = NULL;

	video_unload_image();

    for (int i = 0; i < video_count; i++) {
        free(video_Paths[i]);
    }
	video_count = 0;
	m_video_foucs = 0;

	return 0;
}

static int video_list_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int video_list_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t video_list_window = 
{
	.ops =
	{
		video_list_create,
		video_list_destory,
		video_list_show,
		video_list_hide
	}, 
	.data =
	{
		.id         = WINDOW_VIDEO_LIST, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_VIDEO_LIST(void)
{
	register_window(&video_list_window);
}


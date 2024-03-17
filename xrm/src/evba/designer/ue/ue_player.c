/******************************************************************************
*    includes
******************************************************************************/
#include "ui_player.h"
#include "ui_resource.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "player_int.h"
#include "debug.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} player_ue_t;

typedef struct
{
	player_ui_t ui;
	player_ue_t ue;
} player_para_t;

static player_para_t *para = NULL;
static int video_total_time = 0;
static int video_current_time = 0;
lv_task_t *player_task_id = NULL;
extern player_t *t113_play;

/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_PLAYER, WINDOW_HOME);
	}
}

static void player_ue_create(player_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void player_ue_destory(player_para_t *para)
{
	(void)para;
	return;
}

static void clean_screen(player_ui_t *ui)
{
	// open tplayerdemo || willow					// ??????Ƶ????ͼƬͼ?㣬pipeҪ??0
	lv_obj_t *scn = lv_scr_act();					// ????Ļ
	static lv_style_t scn_style;
	lv_style_copy(&scn_style, &lv_style_plain);
	scn_style.body.main_color.full = 0x00000000;
	scn_style.body.grad_color.full = 0x00000000;
	lv_obj_set_style(scn, &scn_style);

	static lv_style_t cont_style;
	lv_style_copy(&cont_style, &lv_style_plain);
	cont_style.body.main_color.full = 0x00000000;		// ??cont
	cont_style.body.grad_color.full = 0x00000000;
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &cont_style);
}

void video_player(void)
{
    int duration = 0;
    char duration_c[100] = { 0 };    
    char player_name[512] = {0};

    sprintf(player_name, "%s", media_file_get_path(VIDEO_TYPE, media_file_get_play_index(VIDEO_TYPE)));
	if (t113_play != NULL /*&& access(player_name , F_OK) != -1*/) {
		app_info("..........%s ", player_name);

        system("dd if=/dev/zero of=/dev/fb0");
        clean_screen(&para->ui);

		tplayer_play_url(t113_play, player_name);
		tplayer_set_displayrect(t113_play, 0, 0, LV_HOR_RES_MAX, LV_VER_RES_MAX);
        tplayer_volume(t113_play, read_menu_vol_value());
        tplayer_play(t113_play);
        tplayer_get_duration(t113_play, &duration);
        tplayer_set_looping(t113_play, true);
        video_total_time = duration;
        time_int_to_string(duration, duration_c);
        lv_label_set_text(para->ui.label_player_total, duration_c);
	}

}
//快退
static void key_left_callback(void)
{
    int current_pos = 0;

    if(t113_play == NULL)
    {
        return;
    }

    playerStatus status = tplayer_get_status(t113_play);
    if(status == PLAY_STATUS)
    {
        tplayer_get_current_pos(t113_play, &current_pos);
        current_pos -= 5;
        if(current_pos < 1)
        {
            current_pos = 1;
        }

        tplayer_seekto(t113_play, current_pos);
    }
}

//快进
static void key_right_callback(void)
{
    int current_pos = 0;


    if(t113_play == NULL)
    {
        return;
    }

    playerStatus status = tplayer_get_status(t113_play);
    if(status == PLAY_STATUS)
    {
        tplayer_get_current_pos(t113_play, &current_pos);
        current_pos += 5;
        if(current_pos > video_total_time)
        {
            current_pos = video_total_time;
        }
        tplayer_seekto(t113_play, current_pos);
    }
}

static void key_back_callback(void)
{
    switch_window(WINDOW_PLAYER, get_last_window_id());
}

static void key_confirm_callback(void)
{
	app_info("......\n");

    if(t113_play == NULL)
    {
        return;
    }

    playerStatus status = tplayer_get_status(t113_play);
    if (status == PLAY_STATUS) {
        tplayer_pause(t113_play);
    } else if (status == PAUSE_STATUS) {
        tplayer_play(t113_play);
    }

    // if(status == INIT_STATUS)
    // {
    //     video_player();   
    // }
}

static void player_ui_task(struct _lv_task_t *param)
{
	player_ui_t *ui = &para->ui;
	int current_pos = 0;
	int text_current[100] = { 0 };
    int bar_value = 0;

    playerStatus status = tplayer_get_status(t113_play);
    if (status == PLAY_STATUS) {
        
    	tplayer_get_current_pos(t113_play, &current_pos);
        bar_value = current_pos * 1000 / video_total_time;
        if (bar_value < 10) {
            bar_value = 10;
        }
	    time_int_to_string(current_pos, text_current);
	    lv_label_set_text(ui->label_player_current, text_current);
        // bar_value = current_pos * 100 / video_total_time;
        // app_info("current_pos = %d,video_total_time = %d, bar_value = %d\n",current_pos, video_total_time, bar_value);
        lv_bar_set_value(ui->bar_video, bar_value, LV_ANIM_ON); 
    } else if (status == COMPLETE_STATUS){
        lv_bar_set_value(ui->bar_video, 1000, LV_ANIM_ON);
    } else if (status == PAUSE_STATUS) {
    } else if (status == STOP_STATUS) {
    }
    if(status != PLAY_STATUS && status != PAUSE_STATUS)
    {
        app_info("status=%d\n", status);
    }

}

static int player_create(void)
{

	para = (player_para_t *)malloc(sizeof(player_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(player_para_t));

	para->ui.parent = lv_scr_act();
	player_ui_create(&para->ui);
	player_ue_create(para);
    video_player();
    player_task_id = lv_task_create(player_ui_task, 100, LV_TASK_PRIO_MID, NULL);  

    key_callback_register(LV_KEY_4, key_back_callback);
	key_callback_register(LV_KEY_0, key_confirm_callback);

	 key_callback_register(LV_KEY_2, key_left_callback);
	 key_callback_register(LV_KEY_3, key_right_callback);
	 key_mode_set(LV_KEY_3, 1);
	 key_mode_set(LV_KEY_2, 1);

	return 0;
}

static int player_destory(void)
{
    if (player_task_id != NULL) {
        lv_task_del(player_task_id);
    }
    if (t113_play != NULL) {
	    tplayer_stop(t113_play);
    }
	key_callback_unregister();
	player_ue_destory(para);
	player_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int player_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int player_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t player_window = 
{
	.ops =
	{
		player_create,
		player_destory,
		player_show,
		player_hide
	}, 
	.data =
	{
		.id         = WINDOW_PLAYER, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_PLAYER(void)
{
	register_window(&player_window);
}

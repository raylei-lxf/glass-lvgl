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

static void key_left_callback(void)
{

}

static void key_right_callback(void)
{
	
}

static void player_ue_destory(player_para_t *para)
{
	(void)para;
	return;
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


	key_callback_register(LV_KEY_3, key_left_callback);
	key_callback_register(LV_KEY_4, key_right_callback);

	return 0;
}

static int player_destory(void)
{
	player_ue_destory(para);
	player_ui_destory(&para->ui);
	free(para);
	para = NULL;
	
	key_callback_unregister();

	return 0;
}

static int player_show(void)
{
	lv_obj_set_hidden(para->ui.cont_player, 0);

	return 0;
}

static int player_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_player, 1);

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

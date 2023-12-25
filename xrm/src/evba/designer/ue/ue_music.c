/******************************************************************************
*    includes
******************************************************************************/
#include "ui_music.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} music_ue_t;

typedef struct
{
	music_ui_t ui;
	music_ue_t ue;
} music_para_t;
static music_para_t *para = NULL;


/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_MUSIC, WINDOW_HOME);
	}
}

static void music_ue_create(music_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void music_ue_destory(music_para_t *para)
{
	(void)para;
	return;
}

static int music_create(void)
{
	para = (music_para_t *)malloc(sizeof(music_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(music_para_t));

	para->ui.parent = lv_scr_act();
	music_ui_create(&para->ui);
	music_ue_create(para);

	return 0;
}

static int music_destory(void)
{
	music_ue_destory(para);
	music_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int music_show(void)
{
	lv_obj_set_hidden(para->ui.cont_music, 0);

	return 0;
}

static int music_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_music, 1);

	return 0;
}

static window_t music_window = 
{
	.ops =
	{
		music_create,
		music_destory,
		music_show,
		music_hide
	}, 
	.data =
	{
		.id         = WINDOW_MUSIC, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_MUSIC(void)
{
	register_window(&music_window);
}

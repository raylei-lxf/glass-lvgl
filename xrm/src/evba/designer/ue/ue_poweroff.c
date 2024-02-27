/******************************************************************************
*    includes
******************************************************************************/
#include "ui_poweroff.h"
#include "ui_resource.h"
#include "public.h"
#include "debug.h"

/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} poweroff_ue_t;

typedef struct
{
	poweroff_ui_t ui;
	poweroff_ue_t ue;
} poweroff_para_t;
static poweroff_para_t *para = NULL;


/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_POWEROFF, WINDOW_HOME);
	}
}

static void poweroff_ue_create(poweroff_para_t *para)
{
	return;
}

static void poweroff_ue_destory(poweroff_para_t *para)
{
	(void)para;
	return;
}

static int poweroff_create(void)
{
	para = (poweroff_para_t *)malloc(sizeof(poweroff_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(poweroff_para_t));

	para->ui.parent = lv_scr_act();
	poweroff_ui_create(&para->ui);
	poweroff_ue_create(para);

	ui_set_hidden(para->ui.cont_1, 1);
	return 0;
}

static int poweroff_destory(void)
{
	app_info("\n");
	poweroff_ue_destory(para);
	poweroff_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int poweroff_show(void)
{
	//lv_obj_set_hidden(para->ui.cont_main, 0);
	lv_obj_move_foreground(para->ui.cont_main);
	lv_obj_set_hidden(para->ui.cont_1, 0);
	return 0;
}

static int poweroff_hide(void)
{
	//lv_obj_set_hidden(para->ui.cont_main, 1);
	lv_obj_set_hidden(para->ui.cont_1, 1);
	return 0;
}

static window_t poweroff_window = 
{
	.ops =
	{
		poweroff_create,
		poweroff_destory,
		poweroff_show,
		poweroff_hide
	}, 
	.data =
	{
		.id         = WINDOW_POWEROFF, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_POWEROFF(void)
{
	register_window(&poweroff_window);
}

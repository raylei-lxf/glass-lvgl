/******************************************************************************
*    includes
******************************************************************************/
#include "ui_setting.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} setting_ue_t;

typedef struct
{
	setting_ui_t ui;
	setting_ue_t ue;
} setting_para_t;
static setting_para_t *para = NULL;


/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_SETTING, WINDOW_HOME);
	}
}

static void setting_ue_create(setting_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void setting_ue_destory(setting_para_t *para)
{
	(void)para;
	return;
}

static int setting_create(void)
{
	para = (setting_para_t *)malloc(sizeof(setting_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(setting_para_t));

	para->ui.parent = lv_scr_act();
	setting_ui_create(&para->ui);
	setting_ue_create(para);

	return 0;
}

static int setting_destory(void)
{
	setting_ue_destory(para);
	setting_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int setting_show(void)
{
	lv_obj_set_hidden(para->ui.cont_setting, 0);

	return 0;
}

static int setting_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_setting, 1);

	return 0;
}

static window_t setting_window = 
{
	.ops =
	{
		setting_create,
		setting_destory,
		setting_show,
		setting_hide
	}, 
	.data =
	{
		.id         = WINDOW_SETTING, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_SETTING(void)
{
	register_window(&setting_window);
}

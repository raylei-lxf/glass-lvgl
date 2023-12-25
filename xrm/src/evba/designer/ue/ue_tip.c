/******************************************************************************
*    includes
******************************************************************************/
#include "ui_tip.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} tip_ue_t;

typedef struct
{
	tip_ui_t ui;
	tip_ue_t ue;
} tip_para_t;
static tip_para_t *para = NULL;


/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_TIP, WINDOW_HOME);
	}
}

static void tip_ue_create(tip_para_t *para)
{
	// lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void tip_ue_destory(tip_para_t *para)
{
	(void)para;
	return;
}

static int tip_create(void)
{
	para = (tip_para_t *)malloc(sizeof(tip_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(tip_para_t));

	para->ui.parent = lv_scr_act();
	tip_ui_create(&para->ui);
	tip_ue_create(para);

	return 0;
}

static int tip_destory(void)
{
	tip_ue_destory(para);
	tip_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int tip_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int tip_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t tip_window = 
{
	.ops =
	{
		tip_create,
		tip_destory,
		tip_show,
		tip_hide
	}, 
	.data =
	{
		.id         = WINDOW_TIP, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_TIP(void)
{
	register_window(&tip_window);
}

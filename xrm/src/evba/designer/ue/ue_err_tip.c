/******************************************************************************
*    includes
******************************************************************************/
#include "ui_err_tip.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} err_tip_ue_t;

typedef struct
{
	err_tip_ui_t ui;
	err_tip_ue_t ue;
} err_tip_para_t;
static err_tip_para_t *para = NULL;


/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_ERR_TIP, WINDOW_HOME);
	}
}

static void err_tip_ue_create(err_tip_para_t *para)
{
	return;
}

static void err_tip_ue_destory(err_tip_para_t *para)
{
	(void)para;
	return;
}

static int err_tip_create(void)
{
	para = (err_tip_para_t *)malloc(sizeof(err_tip_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(err_tip_para_t));

	para->ui.parent = lv_scr_act();
	err_tip_ui_create(&para->ui);
	err_tip_ue_create(para);

	lv_obj_set_hidden(para->ui.cont_1, 1);
	return 0;
}

static int err_tip_destory(void)
{
	err_tip_ue_destory(para);
	err_tip_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int err_tip_show(void)
{
	lv_obj_move_foreground(para->ui.cont_main);
	lv_obj_set_hidden(para->ui.cont_1, 0);

	return 0;
}

static int err_tip_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_1, 1);

	return 0;
}

static window_t err_tip_window = 
{
	.ops =
	{
		err_tip_create,
		err_tip_destory,
		err_tip_show,
		err_tip_hide
	}, 
	.data =
	{
		.id         = WINDOW_ERR_TIP, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_ERR_TIP(void)
{
	register_window(&err_tip_window);
}

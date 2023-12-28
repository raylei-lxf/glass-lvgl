/******************************************************************************
*    includes
******************************************************************************/
#include "ui_photo.h"
#include "ui_resource.h"
#include "public.h"


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

	return 0;
}

static int photo_destory(void)
{
	photo_ue_destory(para);
	photo_ui_destory(&para->ui);
	free(para);
	para = NULL;

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

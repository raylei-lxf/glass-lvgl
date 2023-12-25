/******************************************************************************
*    includes
******************************************************************************/
#include "ui_test.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
typedef struct
{
	uint8_t id;
} test_ue_t;

typedef struct
{
	test_ui_t ui;
	test_ue_t ue;
} test_para_t;
static test_para_t *para = NULL;


/******************************************************************************
*    functions
******************************************************************************/
static void btn_back_home_event_cb(lv_obj_t * btn, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED)
	{
		switch_window(WINDOW_TEST, WINDOW_HOME);
	}
}

static void test_ue_create(test_para_t *para)
{
	lv_obj_set_event_cb(para->ui.btn_back_home, btn_back_home_event_cb);
	return;
}

static void test_ue_destory(test_para_t *para)
{
	(void)para;
	return;
}

static int test_create(void)
{
	para = (test_para_t *)malloc(sizeof(test_para_t));
	if(NULL == para) {
		return -1;
	}
	memset(para, 0, sizeof(test_para_t));

	para->ui.parent = lv_scr_act();
	test_ui_create(&para->ui);
	test_ue_create(para);

	return 0;
}

static int test_destory(void)
{
	test_ue_destory(para);
	test_ui_destory(&para->ui);
	free(para);
	para = NULL;

	return 0;
}

static int test_show(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 0);

	return 0;
}

static int test_hide(void)
{
	lv_obj_set_hidden(para->ui.cont_main, 1);

	return 0;
}

static window_t test_window = 
{
	.ops =
	{
		test_create,
		test_destory,
		test_show,
		test_hide
	}, 
	.data =
	{
		.id         = WINDOW_TEST, 
		.user_data  = NULL
	}
};

void REGISTER_WINDOW_TEST(void)
{
	register_window(&test_window);
}

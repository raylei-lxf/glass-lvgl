/******************************************************************************
*    includes
******************************************************************************/
#include "ui_phone.h"
#include "ui_resource.h"
#include "public.h"


/******************************************************************************
*    datas
******************************************************************************/
static lv_style_t style0_cont_main;
static lv_style_t style0_img_1;


/******************************************************************************
*    functions
******************************************************************************/
void phone_ui_create(phone_ui_t *ui)
{

#ifdef LV_USE_CONT
	lv_style_copy(&style0_cont_main, &lv_style_pretty);
	style0_cont_main.body.main_color = lv_color_hex(0xf4f4f4);
	style0_cont_main.body.grad_color = lv_color_hex(0xf4f4f4);
	style0_cont_main.body.radius = 0;
	style0_cont_main.body.opa = 0;
	style0_cont_main.body.border.width = 1;

	ui->cont_main = lv_cont_create(ui->parent, NULL);
	lv_obj_set_pos(ui->cont_main, 0, 0);
	lv_obj_set_size(ui->cont_main, 480, 360);
	lv_cont_set_fit4(ui->cont_main, LV_FIT_NONE, LV_FIT_NONE ,LV_FIT_NONE ,LV_FIT_NONE);
	lv_cont_set_style(ui->cont_main, LV_CONT_STYLE_MAIN, &style0_cont_main);
#endif // LV_USE_CONT

#ifdef LV_USE_IMG
	lv_style_copy(&style0_img_1, &lv_style_plain);

	ui->img_1 = lv_img_create(ui->cont_main, NULL);
	lv_obj_set_pos(ui->img_1, 0, 0);
	lv_obj_set_size(ui->img_1, 480, 357);
	lv_img_set_style(ui->img_1, LV_IMG_STYLE_MAIN, &style0_img_1);
#endif // LV_USE_IMG

}

void phone_ui_destory(phone_ui_t *ui)
{
	lv_obj_del(ui->cont_main);
}

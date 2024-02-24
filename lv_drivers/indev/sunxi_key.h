/**
 * @file: sunxi_key.h
 * @autor: huangyixiu
 * @url: huangyixiu@allwinnertech.com
 */
#ifndef SUNXI_KEY_H
#define SUNXI_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef LV_DRV_NO_CONF
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../../lv_drv_conf.h"
#endif
#endif

#if USE_SUNXI_KEY

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

enum {
	LV_KEY_0,
    LV_KEY_1,
	LV_KEY_2,
	LV_KEY_3,
	LV_KEY_4,
	LV_KEY_5,
	LV_KEY_6,
	LV_KEY_7,
	LV_KEY_8,
};
typedef uint8_t lv_key_nj_t;


typedef struct
{
    uint32_t key;     /**< For LV_INDEV_TYPE_KEYPAD the currently pressed key*/
    uint8_t state; /**< LV_INDEV_STATE_REL or LV_INDEV_STATE_PR*/
} lv_key_data_t;

void keydev_read_t(lv_key_data_t *data);

bool keydev_read_d(lv_key_data_t * data);

void keydev_init(void);
void keydev_uninit(void);
bool keydev_read(lv_indev_drv_t * drv, lv_indev_data_t * data);
void power_off_set(uint8_t value);

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

#ifndef __KEY_UI_H__
#define __KEY_UI_H__

#include "xrm_conf.h"
#include "mal_middle.h"
#include <time.h>
#include <sys/time.h>
#include "lvgl.h"
#include "uart.h"
#include <stdint.h>

typedef void (*key_callback)(void);
void key_callback_register(lv_key_nj_t key_num, key_callback func);
void key_callback_unregister(void);
void recovery_callback_register(void);
void key_mode_set(int key_num, int mode);

#endif

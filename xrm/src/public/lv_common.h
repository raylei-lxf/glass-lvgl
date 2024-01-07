#ifndef  __LV_COMMON_H__
#define  __LV_COMMON_H__

#include "xrm_conf.h"

#include "./../../lv_conf.h"
#include "./../../lv_drv_conf.h"
#include "./../../lvgl/lvgl.h"
#include "./../../lv_drivers/lv_drivers.h"
#if CONF_LV_EXAMPLE_ENABLE
#include "./../../lv_ex_conf.h"
#endif

#if CONF_LINUX_ENABLE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/statfs.h>
//#include <alsa/asoundlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <signal.h>
#include <assert.h>
#include <linux/input.h>
#include <pthread.h>
#include <time.h>

typedef __s8  s8;
typedef __u8  u8;
typedef __s16 s16;
typedef __u16 u16;
typedef __s32 s32;
typedef __u32 u32;
#endif


#endif


#ifndef _XRM_CONF_H_
#define _XRM_CONF_H_

/* select os */
#define CONF_LINUX_ENABLE	1

/*  lvgl example lib enable */
#define CONF_LV_EXAMPLE_ENABLE	0

/*  one lvgl  demo enable */
#define CONF_LV_DEMO_ENABLE	0

/* select debug level */
#define COM_ERR_ENABLE		1
#define COM_WARN_ENABLE		1
#define COM_INFO_ENABLE		1

#define BYTE_PER_PIXEL	4
/* add windowns */
typedef enum
{
    NONE = 0,
    WINDOW_HOME,
    WINDOW_SETTING,
    WINDOW_FILE,
    WINDOW_MUSIC,
    WINDOW_PHOTO,
    WINDOW_PLAYER,
    WINDOW_TIP,
    WINDOW_TEST,
    WINDOW_VERIFY,
    WINDOW_PHOTO_LIST,
    WINDOW_VIDEO_LIST,    
    WINDOW_MAX
} window_id_t;

#if COM_ERR_ENABLE
#define com_err(fmt,...) printf("err:<%s:%d>"fmt"\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define com_err(fmt,...) 
#endif

#if COM_WARN_ENABLE
#define com_warn(fmt,...) printf("warn:<%s:%d>"fmt"\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define com_warn(fmt,...) 
#endif

#if COM_INFO_ENABLE
#define com_info(fmt,...) printf("info:<%s:%d>"fmt"\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define com_info(fmt,...) 
#endif

/* select image path */
#define LV_IMAGE_PATH	"/usr/res/image/"

#endif

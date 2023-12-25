#ifndef __DEBUG__H
#define __DEBUG__H

#include <stdio.h>

#define APP_ERR
#define APP_WARN
#define APP_INFO

#ifdef APP_ERR
#define app_err(fmt,...) printf("err:<%s:%d>"fmt"\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define app_err(fmt,...) 
#endif

#ifdef APP_WARN
#define app_warn(fmt,...) printf("warn:<%s:%d>"fmt"\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define app_warn(fmt,...) 

#endif

#ifdef APP_INFO
#define app_info(fmt,...) printf("info:<%s:%d>"fmt"\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define app_info(fmt,...) 
#endif

#endif

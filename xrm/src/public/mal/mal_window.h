#ifndef __MAL_WINDOW_H__
#define __MAL_WINDOW_H__
#include "common.h"

typedef struct
{
	 int (*create)(void);
	 int (*destroy)(void);
	 int (*show)(void);
	 int (*hide)(void);
} window_ops_t;

typedef struct
{
	 window_id_t id;
	 void *user_data;
} window_data_t;

typedef struct
{
	window_ops_t ops;
	window_data_t data;
} window_t;

typedef struct
{
	long int cmd;
  	long int param[2];
} window_msg_t;

void window_head_init();
void window_head_uninit();
void register_window(window_t *window);
void unregister_window(window_t *window);
void create_window(window_id_t id);
void destory_window(window_id_t id);
void show_window(window_id_t id);
void hide_window(window_id_t id);
void switch_window(window_id_t old_id, window_id_t new_id);
void update_window(void);
window_id_t get_curr_window_id(void);

#define REGISTER_WINDOW(name)\
do{\
    extern void REGISTER_##name(void);\
    REGISTER_##name();\
}while(0)


#endif

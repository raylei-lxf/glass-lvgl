#include "mal_window.h"
#include "dbList.h"

db_list_t *window_head = NULL;
db_list_t *window_msg_head = NULL;
window_id_t curr_id;
window_id_t	last_id;

static int compare_by_id(void *dst, void *src)
{
	if(dst == NULL || src == NULL) {
		return -1;
	}

	window_t *dst_page = (window_t *)dst;
	window_id_t src_id = *((window_id_t *)src);
	if(src_id == dst_page->data.id) {
		return 0;
	}
	else {
		return -1;
	}
}

static void *find_window(window_id_t id)
{
	if (NULL != window_head) {
		return __db_list_search_node(window_head, (void *)&id, compare_by_id);
	}
}

void window_head_init()
{
	window_head = db_list_create("lv_win", 0);
	window_msg_head = db_list_create("lv_msg", 0);
}

void window_head_uninit()
{
	if (NULL != window_head) {
		__db_list_destory(window_head);
	}

	if (NULL != window_msg_head) {
		__db_list_destory(window_msg_head);
	}
}

void register_window(window_t *window)
{
	if (NULL != window_head && NULL != window) {
		__db_list_put_tail(window_head, window);
	}
}

void unregister_window(window_t *window)
{
	window_id_t id;
	if (NULL != window_head && NULL != window) {
		id = window->data.id;
		__db_list_search_and_pop(window_head, (void *)&id, compare_by_id);
	}	
}

void create_window(window_id_t id)
{
	window_t *window = (window_t *)find_window(id);
	if(window) {
		if (window->ops.create) {
			window->ops.create();
			curr_id = id;
		}
	}
}

void destory_window(window_id_t id)
{
	window_t *window = (window_t *)find_window(id);
	if(window) {
		if (window->ops.destroy) {
			window->ops.destroy();
		}
	}
}

window_id_t get_curr_window_id(void)
{
	return curr_id;
}

window_id_t get_last_window_id(void)
{
	return last_id;
}

void show_window(window_id_t id)
{
	window_t *window = (window_t *)find_window(id);
	if(window) {
		if (window->ops.show) {
			window->ops.show();
		}
	}
}

void hide_window(window_id_t id)
{
	window_t *window = (window_t *)find_window(id);
	if(window) {
		if (window->ops.hide) {
			window->ops.hide();
		}
	}
}

void switch_window(window_id_t old_id, window_id_t new_id)
{
	window_msg_t *p = NULL;
 	p = (window_msg_t *)malloc(sizeof(window_msg_t));
  	if(!p){
    	com_err("malloc failed!!!");
    	return;
  	}
	
  	p->cmd = 0;
  	p->param[0] = (long int)old_id;
  	p->param[1] = (long int)new_id;
	
 	__db_list_put_tail(window_msg_head, p);
	last_id = old_id;

  	return;
}

void update_window(void)
{
  	int empty;
  	window_msg_t *p;

  	empty = is_list_empty(window_msg_head);
  	if(empty){
    	return;
  	}

  	p = (window_msg_t *)__db_list_pop(window_msg_head);
  	destory_window((window_id_t)p->param[0]);
	//com_info("change windows from %d, to %d", (window_id_t)p->param[0], (window_id_t)p->param[1]);
  	create_window((window_id_t)p->param[1]);
  	free(p);
  	return;
}


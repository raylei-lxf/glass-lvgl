#ifndef __CONFIG_H
#define __CONFIG_H

typedef enum {
    E_CHINESE = 0,
    E_ENGLISH,
    E_MAX = 255
} E_LANGUAGE;

int param_config_init();

int change_language(E_LANGUAGE value);
E_LANGUAGE query_language(void);

int restore_factory(void);


#endif




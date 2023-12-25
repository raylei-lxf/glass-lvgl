#ifndef __UART_H__
#define	__UART_H__

#include <semaphore.h>

#include<pthread.h>
#include <stdint.h>

#define LCD_HEADER		0xF8
#define MPG5_HEADER		0xF9


#define DEVICR_TYPE_BROADCAST	0x00
#define DEVICR_TYPE_MPG5		0x31
#define DEVICR_TYPE_MPG6		0x39

struct packet_data{
	uint8_t header;
	uint8_t type;
	uint8_t len;
	uint8_t fun;
	uint8_t msg[128];
	uint8_t check;
};


#define WAIT_ACK_TIME	100

typedef struct __attribute__ ((packed))
{
	uint8_t state;
	uint8_t lcd_sta;
	uint16_t lcd_time;
	uint8_t res[9];
}func_2_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t fan_ye; //0  3 4
	uint8_t up_down;//0 1 2
}func_2_msg2_t;

typedef struct __attribute__ ((packed))
{
	uint8_t state;
	uint8_t main_page;
	uint8_t err_page;
	uint8_t err_page_time;
}func_2_msg3_t;

typedef struct __attribute__ ((packed))
{
	uint8_t wifi_state;
	uint8_t bt_state;
	uint8_t temp_state;
	uint8_t res;
}func_7_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t batt_state;
	uint8_t batt_pcnt;
	uint8_t inner_batt_state;
	uint8_t inner_batt_pcnt;
	uint8_t ex_batt_state;
	uint8_t ex_batt_pcnt;
	uint8_t sys_state;
	uint16_t time_H;
	uint8_t time_M;
	uint8_t in_time_H;
	uint8_t out_time_H;
	uint8_t res;
}func_11_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t chg_state;
	uint16_t chg_power;
	uint8_t dc_chg_state;
	uint16_t dc_chg_power;
	uint8_t ac_chg_state;
	uint16_t ac_chg_power;
	uint8_t tc_chg_state;
	uint16_t tc_chg_power;
	uint8_t res;
}func_61_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t dischg_state;
	uint16_t dischg_power;
	uint8_t dc_dischg_state;
	uint16_t dc_dischg_power;
	uint8_t ac_dischg_state;
	uint16_t ac_dischg_power;
	uint8_t ac_dischg_source;
	uint8_t res[3];
}func_81_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t res[3];
	uint8_t usba1_dischg_state;
	uint8_t usba1_dischg_power;
	uint8_t usba2_dischg_state;
	uint8_t usba2_dischg_power;
	uint8_t tc1_dischg_state;
	uint16_t tc1_dischg_power;
	uint8_t tc2_dischg_state;
	uint16_t tc2_dischg_power;
}func_83_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t cigar_dischg_state;
	uint16_t cigar_dischg_power;
	uint8_t res[10];
}func_84_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t error_code;
	uint8_t res1;
	uint8_t error_ac;
	uint8_t error_cigar;
	uint8_t res2;
	uint8_t error_usba1;
	uint8_t error_usba2;
	uint8_t error_tc1;
	uint8_t error_tc2;
	uint8_t res[4];
}func_91_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t info_code;
	uint8_t res[12];
}func_92_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t addr;
	uint8_t sn[14];
}func_93_msg_t;

typedef struct __attribute__ ((packed))
{
	uint8_t addr;
	uint8_t sn[14];
}func_94_msg_t;


#define LCD_MODE_LONG                  0x01
#define LCD_MODE_SHORT                 0x02
#define LCD_DEFAULT_MODE               LCD_MODE_SHORT


#define LCD_STA_DOING			0x01 //全亮模式
#define LCD_STA_SLEEPING		0x02 //暗淡模式
#define LCD_STA_CLOSING			0x03 //关闭模式

#define LCD_BRIGHT_REMAIN_TIME	300 //单位s
#define LCD_DIM_REMAIN_TIME	60 //单位s

struct packet_jiemian{

	uint8_t fun_num;
	func_2_msg_t fun2_msg1;
	func_2_msg2_t fun2_msg2;
	func_2_msg3_t fun2_msg3;
	func_7_msg_t fun7_msg;
	func_11_msg_t fun11_msg;
	func_61_msg_t fun61_msg;
	func_81_msg_t fun81_msg;
	func_83_msg_t fun83_msg;
	func_84_msg_t fun84_msg;
	func_91_msg_t fun91_msg;
	func_92_msg_t fun92_msg;
	func_93_msg_t fun93_msg;
	func_94_msg_t fun94_msg;
	int fun93_flag;
	int fun94_flag;
	int update_flag;
	int ack_flag;
	pthread_mutex_t mutex;
	pthread_mutex_t wmutex;
};

//void linux_uart_init(void);
//void linux_uart_deinit(void);
int linux_uart_write(uint8_t page, uint8_t *data, int len);

int linux_uart_init(void);
void linux_uart_deinit(void);
struct packet_jiemian *get_machine_data(void);

void lcd_uart_ack_fun2_01(void);
void lcd_uart_ack_fun2_03(uint8_t page,  uint8_t err_page, uint8_t err_page_time);

void lcd_uart_ack_fun61(void);
void lcd_uart_ack_fun81(void);
void lcd_uart_ack_fun83(void);
void lcd_uart_ack_fun91(void);

#endif


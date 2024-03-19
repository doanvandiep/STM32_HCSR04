#include "stm32f10x.h" 
#include "gp_drive.h"
enum edges
{
	RISE,FALL
};

enum timers{
	T,T1,T2,T3,T4
};
char get_timer_pin(char port, char pin);
TIM_TypeDef * get_timer_address(char port, char pin);
char get_channel(char port, char pin);


void TDelay_Micros(char timer, int microS);
void TDelay_Millis(char timer, int milliS);
void TDelay_Micro( int microS);
void TDelay_Milli( int milliS);
int get_time_micros(char timer);
int get_time_millis(char timer);
void timer_stop(char timer);
TIM_TypeDef * timer_start_micros(char timer, int microS);
void timer_irq_micro_start(char timer, int microS);
void timer_irq_millis_start(char timer, int microS);
void timer_irq_Rflag(char timer);
void timer_irq_stop(char timer);

void timer_compare_micro(char port, char pin, int arr, int compare);
void timer_compare_milli(char port, char pin, int arr, int compare);
void timer_pwm_micro(char port, char pin, int arr, int compare);
void timer_pwm_milli(char port, char pin, int arr, int compare);


char servo_180_deg(char port, char pin, int deg);
char servo_speed_CD(char port, char pin, int speed);
char servo_speed_CCD(char port, char pin, int speed);

void timer_capture_micro(char port,char pin,int arr,char EDGE);
int timer_get_capture_micro(char port, char pin);

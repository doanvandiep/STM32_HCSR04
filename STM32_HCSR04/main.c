#include "systick_time.h"
#include "lcd_1602_drive.h"
#include "help_func.h"
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

#include "time_driver.h"

#define PIN_LED GPIO_Pin_13
#define PIN_BUZ GPIO_Pin_2
int distance;
char myint[3];
char disp[3];
/*
SR04
PA8 -> TRI
PA9 -> ECHO
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA

PC13 -> LED
PA2 -> BUZZER
*/

// update init for 4 bit data transfer 
GPIO_InitTypeDef GPIO;
void LED_CONFIG(){				//Thiêt lâp Led báo hiêu
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = PIN_LED;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO);
}
void BEEP_CONFIG(void) {		//Thiêt lâp còi báo
    GPIO_InitTypeDef GPIO_BEEP;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_BEEP.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_BEEP.GPIO_Pin = GPIO_Pin_2;
    GPIO_BEEP.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_BEEP);
}
void Led_Buzzer(){
	GPIO_ResetBits(GPIOC,PIN_LED);		//Led ON
	GPIO_SetBits(GPIOA,PIN_BUZ);		//Buzzer ON
	DelayMs(100);
	GPIO_SetBits(GPIOC,PIN_LED);		//Led OFF
	GPIO_ResetBits(GPIOA,PIN_BUZ);		//Buzzer OFF
	DelayUs(10);	
}
void CheckLength(){
	W_GP(PA,8,HIGH);
	TDelay_Micro(10);
	W_GP(PA,8,LOW);
	while(R_GP(PA,9)==0){}
	timer_start_micros(T4,65000);
	while(R_GP(PA,9)){}
	distance=get_time_micros(T4)/58;
	TDelay_Milli(60);
}
int main(void)
{
	LED_CONFIG();
	BEEP_CONFIG();
	systick_init();// initialize the delay function (Must initialize)
	lcd_i2c_init(2);
	lcd_i2c_msg(2,1,0,"  Khoang Cach:  ");
	lcd_i2c_msg(2,2,0,"         cm    ");

	GPIO_SetBits(GPIOC,PIN_LED);		//Led OFF
	GPIO_ResetBits(GPIOA,PIN_BUZ);
	DelayUs(10);
	Digital_Output(PA,8);
	Digital_Input(PA,9);
	while(1)
	{	
		CheckLength();
		int2char(distance,myint);
		if (distance < 10) {
      GPIO_ResetBits(GPIOC, PIN_LED);
      DelayMs(100);
      disp[0] = ' ';
      disp[1] = ' ';
      disp[2] = myint[0];

      lcd_i2c_msg(2, 2, 5, disp);
			Led_Buzzer();
     } else if (distance < 100) {
       disp[0] = ' ';
       disp[1] = myint[0];
       disp[2] = myint[1];

       lcd_i2c_msg(2, 2, 5, disp);
			 DelayMs(100);
     } else {
       disp[0] = myint[0];
       disp[1] = myint[1];
       disp[2] = myint[2];

       lcd_i2c_msg(2, 2, 5, disp);
			 DelayMs(100);
     }
		str_empty(myint);
		
	}
}


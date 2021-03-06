// Vzorov? projekt 
#include "stm8s.h"
#include "milis.h"
#include "stdio.h"
#include "spse_stm8.h"
#include "stm8_hd44780.h"





#define tlacitko_1 GPIO_ReadInputPin(GPIOC,GPIO_PIN_6)
#define tlacitko_2 GPIO_ReadInputPin(GPIOC,GPIO_PIN_7)
#define delka_stlaceni 500


const uint16_t perioda01=10;
uint16_t posledni_cas=0;
uint16_t sekundy=0;
uint16_t milisekundy=0;
uint16_t minuty=0;
uint16_t mezicas01=0;
uint16_t mezicas02=0;
uint16_t mezicas03=0;
uint8_t textove_pole[32];
uint16_t delka_stisku=0;
uint16_t x=0;
uint16_t y=0;
uint16_t pauza=0;

void stopky(void);
void displej(void);



void main(void){
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovat MCU na 16MHz
	GPIO_Init(GPIOC,GPIO_PIN_6,GPIO_MODE_IN_PU_NO_IT);
	GPIO_Init(GPIOC,GPIO_PIN_7,GPIO_MODE_IN_PU_NO_IT);
	
	init_milis(); 
	lcd_init();
	
	lcd_gotoxy(10,0);//star? se zobrazen? textu a symbol? na displej.
	lcd_puts(":");
	lcd_gotoxy(13,0);
	lcd_puts(".");
	lcd_gotoxy(10,1);//star? se zobrazen? textu a symbol? na displej.
	lcd_puts(":");
	lcd_gotoxy(13,1);
	lcd_puts(".");
	lcd_gotoxy(4,0);
	lcd_puts("cas ");
	lcd_gotoxy(0,1);
	lcd_puts("mezicas ");
	
	displej();
	
	while(1){

		
		if ((tlacitko_1!=RESET)&&(x==0)){
			x=1;
			delka_stisku=milis();
	  }
	  if ((tlacitko_1==RESET)&&(x==1)){
			x=0;
		  if (milis()-delka_stisku<delka_stlaceni){
				
				pauza++;
				posledni_cas = milis();
				if (pauza>1){
					pauza=0;
				}
			}
    }
		if ((x==1)&&(milis()-delka_stisku>=delka_stlaceni)){
			//reset
			sekundy=0;
			milisekundy=0;
			minuty=0;
			mezicas01=0;
			mezicas02=0;
			mezicas03=0;
			displej();
			pauza=0;
		}
		if (pauza==1){
			stopky();
		}
		if ((tlacitko_2!=RESET)&&(y==0)){
			y=1;
			sprintf(textove_pole,"%02u",mezicas02);
			lcd_gotoxy(11,1);
			lcd_puts(textove_pole);
			sprintf(textove_pole,"%02u",mezicas03);
			lcd_gotoxy(8,1);
			lcd_puts(textove_pole);
			sprintf(textove_pole,"%02u",mezicas01);
			lcd_gotoxy(14,1);
			lcd_puts(textove_pole);
			displej();
	  }
	  if ((tlacitko_2==RESET)&&(y==1)){
			y=0;
    }
	}
}

void stopky (void){
   if(milis() - posledni_cas >= perioda01){//zde je funkce, kter? se star? o chod stopek.
    posledni_cas = milis(); 
	  milisekundy=milisekundy+1;
		mezicas01=milisekundy;
			if(milisekundy>99){
				milisekundy=0;
				sekundy=sekundy+1;
				mezicas02=sekundy;
				if(sekundy>59){
					sekundy=0;
					minuty=minuty+1;
					mezicas03=minuty;
				}
		  }
		displej();
	} 
}
void displej(void){
	sprintf(textove_pole,"%02u",sekundy);
  lcd_gotoxy(11,0);
	lcd_puts(textove_pole);
	sprintf(textove_pole,"%02u",minuty);
	lcd_gotoxy(8,0);
	lcd_puts(textove_pole);
	sprintf(textove_pole,"%02u",milisekundy);
	lcd_gotoxy(14,0);
	lcd_puts(textove_pole);
	
	sprintf(textove_pole,"%02u",mezicas02);
	lcd_gotoxy(11,1);
	lcd_puts(textove_pole);
	sprintf(textove_pole,"%02u",mezicas03);
	lcd_gotoxy(8,1);
	lcd_puts(textove_pole);
	sprintf(textove_pole,"%02u",mezicas01);
	lcd_gotoxy(14,1);
	lcd_puts(textove_pole);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file namenumber
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */


     /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
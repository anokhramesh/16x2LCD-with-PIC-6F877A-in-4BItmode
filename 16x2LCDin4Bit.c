
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
#include <xc.h>
#define _XTAL_FREQ 20000000
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_ON & CPD_OFF & WRT_OFF & CP_OFF);
#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2
void lcd_cmd(unsigned char cmd)
{
	PORTB  = (cmd & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 0;
    __delay_ms(2);
	EN = 0;
	PORTB  = ((cmd<<4) & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 0;
    __delay_ms(2);
	EN = 0;	
}

void lcd_data(unsigned char data)
{
   	PORTB  = (data & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 1;
    __delay_ms(2);
	EN = 0;
	PORTB  = ((data<<4) & 0xF0) ; 
	EN = 1;
    RW = 0;
	RS = 1;
    __delay_ms(2);
	EN = 0;	
}

void lcd_init()
{
    lcd_cmd(0x28); // 4bit mode and 16 columns and 2 rows of lcd
    lcd_cmd(0x0C);
    lcd_cmd(0x06); // auto increment 
    lcd_cmd(0x01); // clearscreen
}

void lcd_string(const unsigned char *str,unsigned char num)  
{
    unsigned char i;
    for(i=0;i<num;i++)
    {
      lcd_data(str[i]);  
        
    }
}






void main(void)    

{
    TRISB = 0x00; // ALL the PORTB Pins Configured as OUTPUTS
    lcd_init();
    while(1)
    {
      lcd_cmd(0x83);
      lcd_string("SUBSCRIBE",9);
      lcd_cmd(0xC0);
      lcd_string("ANOKHAUTOMATION",15);
    }
    return;
}
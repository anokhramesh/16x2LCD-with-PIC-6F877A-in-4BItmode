/*Program for Display String on 16x2 LCD in 4 Bit Mode
 * connect RB0 pin of PIC16F877A to RS pin of 16x2 LCD Screen
 * connect RB1 pin of PIC16F877A to RW pin of 16x2 LCD Screen
 * connect RB2 pin of PIC16F877A to E(enable) pin of 16x2 LCD Screen
 * connect RB4 pin of PIC16F877A to D4 pin of 16x2 LCD Screen
 * connect RB5 pin of PIC16F877A to D5 pin of 16x2 LCD Screen
 * connect RB6 pin of PIC16F877A to D6 pin of 16x2 LCD Screen
 * connect RB7 pin of PIC16F877A to D7 pin of 16x2 LCD Screen
*/
#include <xc.h>
#define _XTAL_FREQ 20000000
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_ON & CPD_OFF & WRT_OFF & CP_OFF);//PIC configuration Bit setting
#define RS PORTBbits.RB0// defined RB0 Pin as RS
#define RW PORTBbits.RB1// defined RB1 Pin as RW
#define EN PORTBbits.RB2// defined RB2 Pin as EN

void lcd_cmd(unsigned char cmd)//Function for Writing  Command to LCD
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

void lcd_data(unsigned char data)// Function for Writing  Data to LCD
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

void lcd_init()// Function for LCD Initialization
{
    lcd_cmd(0x28); //command for turn LCD to 4bit mode and 16 columns and 2 rows.
    lcd_cmd(0x0C);//command for Cursor OFF,Display ON
    lcd_cmd(0x06); //command for auto increment 
    lcd_cmd(0x01); //command for clear screen
}

void lcd_string(const unsigned char *str,unsigned char num)  // function for Printing strings to the LCD
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
    lcd_init();//calling the LCD Initialization Function
    while(1)
    {
      lcd_cmd(0x83);//command for go to First Raw,3rd column
      //lcd_cmd(0x80);//command for go to First Raw,1st column of LCD
      lcd_string("SUBSCRIBE",9);//command for Print String
      lcd_cmd(0xC0);//command for go to second Raw,1st column of LCD
      lcd_string("ANOKHAUTOMATION",15);//command for Print String
    }
    return;
}
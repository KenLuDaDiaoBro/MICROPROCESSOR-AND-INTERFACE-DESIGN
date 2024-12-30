#include <regx51.h> //include header file for 8051
#define TH0_init 60 //TH0_init= 256 - 250
#define TL0_init 176 //TL0_init = 256 - 250
#define Timer0_int_exe_time 10 //the parameter can be changed

int counter;

void main( ) 
{
	IE = 0x82; //enable timer0 interrupt
	IP = 0x02; //timer0 interrupt has high priority
	TCON = 0x10; //enable timer0
	TMOD = 0x09; //set timer0 to mode 2(8-bits and auto-reload)
	TL0 = TL0_init; 
	TH0 = TH0_init; //set TH0 & TL0
	P2 = 0xFE;
	P3_2 = 0;
	while(1);
}

void timer0_interrupt(void) interrupt 1
{
    counter++;
    if (counter >= Timer0_int_exe_time)
    {
      P2 = P2 << 1;
			P2 += 1; // Shift left and set LSB
      if (P2 == 0xFF) 
			{
				P2 -= 1;
			}
      counter = 0; // Reset counter
    }
}
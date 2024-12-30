#include <regx51.h>
int Light_Bulb;

void main( )
{
	IT0 = 0; //enable a low-level signal on externalinterrupt
	EX0 = 1; //enable INT0
	EA = 1; //enable interrupt
	P3_4 = 0; //WR=0,clean the data
	P3_4 = 1; //WR=1,analog convert to digital
	P2 = 0;
	while(1); //infinite loop
}

void int_0(void)interrupt 0 //INT0 interrupt function
{
	P3_5 = 0; //RD=0,readthe digital data
	Light_Bulb = (P1 + 1) / 32;
	switch(Light_Bulb)
	{
		case 0:
			P2 = 255;
			break;
		
		case 1:
			P2 = 254;
			break;
		
		case 2:
			P2 = 252;
			break;
		
		case 3:
			P2 = 248;
			break;
		
		case 4:
			P2 = 240;
			break;
		
		case 5:
			P2 = 224;
			break;
		
		case 6:
			P2 = 192;
			break;
		
		case 7:
			P2 = 128;
			break;
		
		case 8:
			P2 = 0;
			break;
		
		default:
			P2 = 255;
			break;
	}

	P3_5 = 1; //RD=1
	P3_4 = 0; //WR=0,clean the data
	P3_4 = 1; //WR=1,analog convert to digital
}
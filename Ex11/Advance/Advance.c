#include<reg51.h>          // Include the header file for 8051 microcontroller, defines hardware registers like P0, P1, etc.
void delay (int);
void turn ();

code char one_phase[] = {0x01, 0x02, 0x04, 0x08};
code char two_phase[] = {0x0C, 0x06, 0x03, 0x09};
int dir, delay_time, Resistence;

void main() 
{
    delay_time = 1000;
    dir = 1;
    while(1) 
		{
        turn();
    }
}

void turn() 
{
    int x;                // Declare loop index variable
		Resistence = (P2 + 1) / 32;
		switch(Resistence)
		{
			case 0:
				delay_time = 2000;
				break;
			
			case 1:
				delay_time = 1800;
				break;
			
			case 2:
				delay_time = 1600;
				break;
			
			case 3:
				delay_time = 1400;
				break;
			
			case 4:
				delay_time = 1200;
				break;
			
			case 5:
				delay_time = 1000;
				break;
			
			case 6:
				delay_time = 800;
				break;
			
			case 7:
				delay_time = 600;
				break;
			
			case 8:
				delay_time = 400;
				break;
			
			default:
				delay_time = 1000;
				break;
		}
	
    if (dir == 1) 
		{
        for (x = 0; x < 4; x++) 
				{
            P1 = one_phase[x];             // Send control signal to P1 pins to control the motor
            delay(delay_time);             // Delay to stabilize the signal
				}
    } 
		else 
		{
        for (x = 0; x < 4; x++) 
				{
            P1 = two_phase[x];             // Send control signal to P1 pins to control the motor
            delay(delay_time);             // Delay to stabilize the signal
        }
    }
}

// Delay function
void delay(int t) 
{
    while(t--);           // Simple decrementing loop for delay until t reaches 0
}
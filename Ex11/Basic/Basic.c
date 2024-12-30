#include<reg51.h>          // Include the header file for 8051 microcontroller, defines hardware registers like P0, P1, etc.
void delay (int);
void turn ();

code char one_phase[] = {0x01, 0x02, 0x04, 0x08};
code char two_phase[] = {0x0C, 0x06, 0x03, 0x09};
int dir, delay_time;

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
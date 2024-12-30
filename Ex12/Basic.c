#include <regx51.h>
void delay(unsigned int);

void main()
{
	while(1)
	{
		P1_0 = 0;
		delay(50000);
		P1_0 = 0;
		delay(50000);
	}
}

void delay(unsigned int t)
{
	while(t--);
}
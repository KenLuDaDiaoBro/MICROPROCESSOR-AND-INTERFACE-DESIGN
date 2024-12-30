#include <regx51.h>

char receive_value;            // Variable to store received data
char *Correct = "\r\ncorrect\r\n";
char *Wrong = "\r\nwrong\r\n";
char *School_Num = "E94116067";
char ans[9];
int Index = 0;

// UART initialization function
void init_uart(void)
{
    SCON = 0x50;               // Set UART mode 1 (8-bit UART)
    TMOD = 0x20;               // Set Timer 1 to mode 2 (8-bit auto-reload)
    TH1 = 0xE6;                // Set baud rate to 1200
    TR1 = 1;                   // Start Timer 1
}

void send_message(char *alphabt)
{
		while(*alphabt != '\0')
		{
				SBUF = *alphabt;
				while(TI == 0);
				TI = 0;
				alphabt++;
		}
}

int check()
{
		int i = 0;
		int pass = 1;
		for(i = 0 ; i < 9 ; i++)
		{
				if(ans[i] != *(School_Num + i)) pass = 0;
				ans[i] = '\0';
		}
		if(pass) return 1;
		else return 0;
}

void main()
{
    init_uart();               // Initialize UART
    while (1)
    {
        if (RI)                // Check the receive interrupt flag (polling method)
        {
            RI = 0;            // Clear the receive interrupt flag
            receive_value = SBUF; // Read the received data from the serial buffer
            P2 = receive_value;   // Display the received data on Port 2
						if(P2 == 127 && Index > 0) Index--;
						else if((P2 == 13) || (48 <= P2 && P2 <= 57) || (65 <= P2 && P2 <= 90) || (97 <= P2 && P2 <= 122))
						{
								ans[Index] = P2;
								Index++;
								if((Index >= 9) || (P2 == 13))
								{
										int result = check();
										Index = 0;
										if(result) send_message(Correct);
										else send_message(Wrong);
								}
						}
        }
    }
}
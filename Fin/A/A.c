#include <regx51.h>
void print_msg(char *);  // Function to print a string to the LCD
void write(char, int);   // Function to send commands or data to the LCD
void delay(unsigned int); // Function to introduce delay

char receive_value;            // Variable to store received data
char *On = "\r\nLCD on\r\n";
char *Off = "\r\nLCD off\r\n";
char *Wrong = "\r\nwrong\r\n";
char *School_Num = "E94116067";
char *Shutdown = "Shutdown";
char ans[9];
int Index = 0;
int open = 0;

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

int check1()
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

int check2()
{
		int i = 0;
		int pass = 1;
		for(i = 0 ; i < 8 ; i++)
		{
				if(ans[i] != *(Shutdown + i)) pass = 0;
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
								if(open)
								{
										if((Index >= 8) || (P2 == 13))
										{
												int result = check2();
												Index = 0;
												if(result)
												{
														send_message(Off);
														P1_0 = 1;
														open = 0;
												}
												else send_message(Wrong);
										}
								}
								else
								{
										if((Index >= 9) || (P2 == 13))
										{
												int result = check1();
												Index = 0;
												if(result)
												{
														send_message(On);
														P1_0 = 0;
														open = 1;
												}
												else send_message(Wrong);
										}
								}
						}
        }
    }
}

// Function to display a string on the LCD
void print_msg(char *msg) 
{
    for (; *msg != '\0'; msg++) // Iterates through the character array
        write(*msg, 1);         // Sends characters to the LCD in "data mode" (RS=1)
}

// Function to send a command or data to the LCD
void write(char cmd, int rs_value) 
{
    P2 = cmd;        // Set command or data (cmd) on Port 1
    P1_6 = rs_value; // Set RS (Register Select): 0 for command, 1 for data
    P1_7 = 1;        // ENABLE high to latch data into the LCD
    delay(100);      // Delay to stabilize the ENABLE signal
    P1_7 = 0;        // ENABLE low to complete the operation
}

// Function to introduce delay
void delay(unsigned int i) 
{
    while (i--); // Simple delay loop; time depends on clock speed
}
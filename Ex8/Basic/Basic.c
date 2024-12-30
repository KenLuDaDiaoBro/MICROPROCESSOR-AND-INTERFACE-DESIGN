#include <regx51.h>

void init_uart();       // Function to initialize UART
char receive_value;     // Variable to store received data

void main()
{
    init_uart();  // Initialize UART
    while (1);    // Infinite loop to keep the program running
}

void init_uart()
{
    SCON = 0x50;  // Set UART in mode 1 (8-bit UART)
    TMOD = 0x20;  // Timer1 in mode 2 (8-bit auto-reload)
    TH1 = 0xE6;   // Set baud rate to 1200
    TR1 = 1;      // Start Timer1
    IE = 0x90;    // Enable UART interrupt (EA and ES)
}

// UART Interrupt Service Routine
void uart_isr(void) interrupt 4
{
		while(RI == 0);
		RI = 0;  // Clear receive interrupt flag
		receive_value = SBUF;  // Read received data from the buffer
		P2 = receive_value;    // Display received data on Port 2

		if (receive_value == 'q')
		{
				SBUF = receive_value;  // Echo back received data
				while (TI == 0);       // Wait for transmission to complete
				TI = 0;                // Clear transmission interrupt flag
		}
}

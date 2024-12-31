#include <regx51.h>
void print_msg(char *);  // Function to print a string to the LCD
void write(char, int);   // Function to send commands or data to the LCD
void delay(unsigned int); // Function to introduce delay

char receive_value;            // Variable to store received data
char *Sm = "smile";
int Index = 0;
int re = 0;
int PP;
int i;

// UART initialization function
void init_uart(void)
{
    SCON = 0x50;               // Set UART mode 1 (8-bit UART)
    TMOD = 0x20;               // Set Timer 1 to mode 2 (8-bit auto-reload)
    TH1 = 0xE6;                // Set baud rate to 1200
    TR1 = 1;                   // Start Timer 1
}

void main()
{
		init_uart();               // Initialize UART
		P1_0 = 0;
		delay(1000000);
		write(0x38, 0); // Set LCD to 8-bit mode, 2-line display, 5x7 dot format
    write(0x0F, 0); // Turn on display, enable cursor, set cursor to blink
    write(0x06, 0); // Increment cursor position after data write
	
		 // Set CGRAM address for custom character (start at 0x40 for the first custom character)
    write(0x40, 0);
    
    // Write 8 rows of pixel data for the custom character
    write(0x00, 1);
    write(0x0A, 1);
    write(0x1F, 1);
    write(0x1F, 1);
    write(0x0E, 1);
    write(0x04, 1);
    write(0x00, 1);
    write(0x00, 1); // Row 8 (cursor): Leave this row empty
	
		write(0x48, 0);
	
		write(0x00, 1);
    write(0x0A, 1);
    write(0x0A, 1);
    write(0x00, 1);
    write(0x11, 1);
    write(0x0E, 1);
    write(0x00, 1);
    write(0x00, 1); 
	
    write(0x01, 0); // Clear display and return the cursor to home position
    write(0x80, 0); // Set DDRAM address to 0x00 (beginning of the first line)
		print_msg("               ");
    write(0x00, 1);
		write(0xC0, 0); // Set DDRAM address to 0x00 (beginning of the first line)
    
    while (1)
    {
        if (RI)                // Check the receive interrupt flag (polling method)
        {
            RI = 0;            // Clear the receive interrupt flag
            receive_value = SBUF; // Read the received data from the serial buffer
            PP = receive_value;   // Display the received data on Port 2
						write(PP, 1);
						if(PP == 127 && Index > 0) Index--;
						else if((PP == 13) || (48 <= PP && PP <= 57) || (65 <= PP && PP <= 90) || (97 <= PP && PP <= 122))
						{
								if(PP == 's' && re == 0) re++;
								else if(PP == 'm' && re == 1) re++;
								else if(PP == 'i' && re == 2) re++;
								else if(PP == 'l' && re == 3) re++;
								else if(PP == 'e' && re == 4)
								{
										write(0x38, 0); // Set LCD to 8-bit mode, 2-line display, 5x7 dot format
										write(0x0F, 0); // Turn on display, enable cursor, set cursor to blink
										write(0x06, 0); // Increment cursor position after data write
										write(0x01, 0); // Clear display and return the cursor to home position
										write(0x80, 0); // Set DDRAM address to 0x00 (beginning of the first line)
										write(0x01, 1);
										write(0xC0, 0);
								}
								else re = 0;
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
#include <regx51.h> // Include the 8051 microcontroller header file

void print_msg(char *);  // Function to print a string to the LCD
void write(char, int);   // Function to send commands or data to the LCD
void delay(unsigned int); // Function to introduce delay

void main() 
{
		P1_0 = 0;
		delay(1000000);
    write(0x38, 0); // Set LCD to 8-bit mode, 2-line display, 5x7 dot format
    write(0x0F, 0); // Turn on display, enable cursor, set cursor to blink
    write(0x06, 0); // Increment cursor position after data write
    write(0x01, 0); // Clear display and return the cursor to home position
    write(0x80, 0); // Set DDRAM address to 0x00 (beginning of the first line)
    while (1) // Infinite loop to keep the program runningwhile(1)
		{
				delay(50000);
				if(P0 < 130)
				{
						write(0x38, 0); // Set LCD to 8-bit mode, 2-line display, 5x7 dot format
						write(0x0F, 0); // Turn on display, enable cursor, set cursor to blink
						write(0x06, 0); // Increment cursor position after data write
						write(0x01, 0); // Clear display and return the cursor to home position
						write(0x80, 0); // Set DDRAM address to 0x00 (beginning of the first line)
						print_msg("LOW"); // Display the string "Hello, world!" on the LCD
				}	
				else 
				{
						write(0x38, 0); // Set LCD to 8-bit mode, 2-line display, 5x7 dot format
						write(0x0F, 0); // Turn on display, enable cursor, set cursor to blink
						write(0x06, 0); // Increment cursor position after data write
						write(0x01, 0); // Clear display and return the cursor to home position
						write(0x80, 0); // Set DDRAM address to 0x00 (beginning of the first line)
						print_msg("HIGH");
				}
				if(P0 >= 250)
				{
						write(0xC0, 0);
						print_msg("finish");
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

#include "io.h" //By including io.h we can use the outb function defined in io.s
#include "framebuffer.h" //Include the framebuffer header file for function declarations

#pragma region Framebuffer
char *fb = (char *) 0x000B8000; 


 struct Command{
     const char* name;
     int (*funct) (void);
     const int length;
 };

#pragma region Color Settings

unsigned int BG_COLOR = COLOR_BLACK;
unsigned int FG_COLOR = COLOR_WHITE;

void setBGColor(int color)
{
    switch (color)
    {
        case 0:
        BG_COLOR = COLOR_BLACK;
        break;
        case 1:
        BG_COLOR = COLOR_BLUE;
        break;
        case 2:
        BG_COLOR = COLOR_GREEN;
        break;
        case 3:
        BG_COLOR = COLOR_CYAN;
        break;
        case 4:
        BG_COLOR = COLOR_RED;
        break;
        case 5:
        BG_COLOR = COLOR_MAGENTA;
        break;
        case 6:
        BG_COLOR = COLOR_BROWN;
        break;
        case 7:
        BG_COLOR = COLOR_LIGHT_GREY;
        break;
        case 8:
        BG_COLOR = COLOR_DARK_GREY;
        break;
        case 9:
        BG_COLOR = COLOR_LIGHT_BLUE;
        break;
        case 10:
        BG_COLOR = COLOR_LIGHT_GREEN;
        break;
        case 11:
        BG_COLOR = COLOR_LIGHT_CYAN;
        break;
        case 12:
        BG_COLOR = COLOR_LIGHT_RED;
        
        break;
        case 13:
        BG_COLOR = COLOR_LIGHT_MAGENTA;
        break;
        case 14:
        BG_COLOR = COLOR_LIGHT_BROWN;
        break;
        case 15:
        BG_COLOR = COLOR_BLACK;
        break;
        
        
        
        default:
        BG_COLOR = COLOR_BLACK;
        break;
    }
}

int changeColor()
{
    unsigned int color = FG_COLOR + (unsigned int)1;
    if (color > COLOR_WHITE)
    {
        color = COLOR_BLACK;
    }
    setFGColor(color);
    fb_new_line();
    return 0;
}

void setFGColor(int color)
{
    switch (color)
    {
        case 0:
        FG_COLOR = COLOR_BLACK;
        break;
        case 1:
        FG_COLOR = COLOR_BLUE;
        break;
        case 2:
        FG_COLOR = COLOR_GREEN;
        break;
        case 3:
        FG_COLOR = COLOR_CYAN;
        break;
        case 4:
        FG_COLOR = COLOR_RED;
        break;
        case 5:
        FG_COLOR = COLOR_MAGENTA;
        break;
        case 6:
        FG_COLOR = COLOR_BROWN;
        break;
        case 7:
        FG_COLOR = COLOR_LIGHT_GREY;
        break;
        case 8:
        FG_COLOR = COLOR_DARK_GREY;
        break;
        case 9:
        FG_COLOR = COLOR_LIGHT_BLUE;
        break;
        case 10:
        FG_COLOR = COLOR_LIGHT_GREEN;
        break;
        case 11:
        FG_COLOR = COLOR_LIGHT_CYAN;
        break;
        case 12:
        FG_COLOR = COLOR_LIGHT_RED;
        
        break;
        case 13:
        FG_COLOR = COLOR_LIGHT_MAGENTA;
        break;
        case 14:
        FG_COLOR = COLOR_LIGHT_BROWN;
        break;
        case 15:
        FG_COLOR = COLOR_WHITE;
        break;
        
        
        
        default:
        FG_COLOR = COLOR_BLACK;
        break;
    }
}
#pragma endregion

/** fb_write_cell:
 * Writes a character with the given foreground and background to position i
 * in the framebuffer.
 *
 * @param i The location in the framebuffer
 * @param c The character
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

#pragma endregion

#pragma region Cursor Movement

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/** fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}
//This region moves the cursor to a new position and outputs the correct data to the screen

#pragma endregion
#pragma region Serial Baud Rate Configuration

/* The I/O ports */
/* All the I/O ports are calculated relative to the data port. This is because
* all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
* order, but they start at different values.
*/
#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)
/* The I/O port commands */
/* SERIAL_LINE_ENABLE_DLAB:
* Tells the serial port to expect first the highest 8 bits on the data port,
* then the lowest 8 bits will follow
*/
#define SERIAL_LINE_ENABLE_DLAB 0x80
/** serial_configure_baud_rate:
* Sets the speed of the data being sent. The default speed of a serial
* port is 115200 bits/s. The argument is a divisor of that number, hence
* the resulting speed becomes (115200 / divisor) bits/s.
*
* @param com The COM port to configure
* @param divisor The divisor
*/
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com),
    SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
    (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
    divisor & 0x00FF);
}


//This region configures the serial ports for inputs and outputs
#pragma endregion
#pragma region Serial Line Configuration

/** serial_configure_line:
* Configures the line of the given serial port. The port is set to have a
* data length of 8 bits, no parity bits, one stop bit and break control
* disabled.
*
* @param com The serial port to configure
*/
void serial_configure_line(unsigned short com)
{
/* Bit: | 7 | 6 | 5 4 3 | 2 | 1 0 |
* Content: | d | b | prty | s | dl |
* Value: | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
*/
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

//This sets the standard for communication over the ports
#pragma endregion
#pragma region Serial Buffer 
    /** serial_is_transmit_fifo_empty:
    * Checks whether the transmit FIFO queue is empty or not for the given COM
    * port.
    *
    * @param com The COM port
    * @return 0 if the transmit FIFO queue is not empty
    * 1 if the transmit FIFO queue is empty
    */
    int serial_is_transmit_fifo_empty(unsigned int com)
    {
        /* 0x20 = 0010 0000 */
        return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
    }
    // This section checks if the buffer is empty so data can be sent
#pragma endregion

/// @brief Compares two command arrays by going through their values
/// @param s1 The template that s2 is compared to
/// @param s2 
/// @return returns 0 if they are the same
int compareCommands(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

unsigned short getpositionCursor()
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    unsigned short high = inb(FB_DATA_PORT);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    unsigned short low = inb(FB_DATA_PORT);
    return (high << 8) | low;
}

#pragma region Clear
int write_OSname()
{
    char *name = "BruvOS:";
    fb_write(name, 7);
    return 0;
}

int fb_clear()
{
    fb_move(0,0);
    int endpos = (80 * 25);
    for(int i = 0; i < endpos; i++)
    {
        fb_write_cell(getpositionCursor()*2, ' ', FG_COLOR, BG_COLOR);
        fb_move_cursor(getpositionCursor() + (unsigned short) 1);
    }
    fb_move(0,0);
    setBGColor(COLOR_BLACK);
    setFGColor(COLOR_GREEN);
    fb_write("Welcome to MYOS!",16);
    fb_new_line();
    return 0;
}
#pragma endregion

#pragma region Move

int fb_move(unsigned short x, unsigned short y)
{
    unsigned short pos = (y * 80) + x;
    fb_move_cursor(pos);
    return 0;
}

#pragma endregion




#pragma region Backspace
int fb_backspace()
{
    unsigned short pos = getpositionCursor();
    if (pos < ((pos/ 80)* 80) + (unsigned int)8)
    {
        return 0;
    }
    else
    {
        fb_move_cursor(pos - (unsigned short) 1);
        fb_write_cell(pos*2, ' ', FG_COLOR, BG_COLOR);
        return 0;
    }
}

#pragma endregion

#pragma region Reading from Framebuffer

char getc(int pos)
{
    char val = fb[pos*2];
    return val;
    
}

void readline(int row, char *line)
{
    int base = row * 80;   // row offset in cells
    int i = 0;
    
    for (int col = 0; col < 80; col++)
    {
        char c = getc(base + col);
        if (c == '\n' || c == '\0')
        {
            break;  // stop at newline or null
        }
        line[i++] = c;
    }
    
    line[i] = '\0'; // Null-terminate string
}

#pragma endregion

#pragma region Shuffle

int fb_shuffle()
{
    //Reads the current lines into a buffer and writes them over the previous line
    char line[80];
    for(int fbrow = 1; fbrow < 25; fbrow++)
    {
        readline(fbrow, line);
        fb_move(0, fbrow -1);
        fb_write(line, 80);
    }
    
    //clears the bottom line for the user
    fb_move(0,24);
    for(int fbcol = 0; fbcol < 80; fbcol++)
    {
        fb_write_cell((24 * 80 + fbcol) * 2, ' ', FG_COLOR, BG_COLOR);
    }   
    fb_move(0,24);
    write_OSname();
    return 0;
}

int checkBounds()
{
    int pos = getpositionCursor();
    if (pos > (80*25)-1)
    {
        fb_shuffle();
        return 0;
    }
    else
    {
        return 0;
    }
}
#pragma endregion

#pragma region Write


int fb_write(char *buf, unsigned int len)
{
    
    for(int i = 0; i < (int)len; i++)
    {
        fb_write_cell(getpositionCursor() *2, buf[i], FG_COLOR, BG_COLOR);
        fb_move_cursor(getpositionCursor()+ (unsigned short) 1);   
    }
    checkBounds();
    return 0;
}
#pragma endregion

#pragma region New Line
int fb_new_line()
{
    int pos = getpositionCursor();
    int row = pos / 80;
    row++;
    fb_move(0, row);
    write_OSname();
    checkBounds();
    return 0;
}
#pragma endregion

#pragma region Commands Initialisation
int write_OSVersion()
{
    char *name = "BruvOS 1.0 - Max Jones";
    fb_new_line();
    fb_write(name, 23);
    fb_new_line();
    return 0;
}

const int numCommands = 3;
struct Command commands[3]={
    {"clear" , fb_clear, 5},
    {"version" ,write_OSVersion, 7},
    {"color" , changeColor, 5}
};
#pragma endregion


int processCommand(char command[], int length)
{
    int hasExecuted = -1;
    if(length > 0)
    {
        //checks the length of each command and the command mataches that it checks it if not it doesnt to save time and memory
        for(int i = 0; i < numCommands; i++)
        {
            if(commands[i].length == length)
            {
                if(compareCommands(commands[i].name,command) == 0)
                {
                    commands[i].funct();
                    hasExecuted = 0;
                }
            }
        }
        if(hasExecuted == -1)
        {
            fb_new_line();
            fb_write("Unknown Command", 15);
            fb_new_line();
        }
    }
   
    return 0;
}


int readCommand()
{
    int offset = 7; //Offset of the myOS
    char input[80];
    int row = (getpositionCursor() / 80); 
    int pos = (row * 80) + offset; //gets the row
    char character = getc(pos);
    int index = 0;
    while (character != ' ' && character != '\0' && index < 79)
    {
        input[index] = character;
        index++;
        pos++;
        character = getc(pos);
    }
    if(index > 0)
    {
        char command[index+1];
        for(int i = 0; i < index; i++)
        {
            command[i] = input[i];
        }
        command[index] = '\0';
        
        processCommand(command, index);
    }
    else
    {
        fb_new_line();
        fb_write("Unknown Command(NULL)", 21);
        fb_new_line();
    }
    return 0;

}



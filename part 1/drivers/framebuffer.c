#include "../source/io.h" //By including io.h we can use the outb function defined in io.s
#include "framebuffer.h" //Include the framebuffer header file for function declarations


#pragma region Framebuffer
char *fb = (char *) 0x000B8000; 

#pragma region Color
#define COLOR_BLACK 0x0
#define COLOR_BLUE 0x1
#define COLOR_GREEN 0x2
#define COLOR_CYAN 0x3
#define COLOR_RED 0x4
#define COLOR_MAGENTA 0x5
#define COLOR_BROWN 0x6
#define COLOR_LIGHT_GREY 0x7
#define COLOR_DARK_GREY 0x8
#define COLOR_LIGHT_BLUE 0x9
#define COLOR_LIGHT_GREEN 0xA
#define COLOR_LIGHT_CYAN 0xB
#define COLOR_LIGHT_RED 0xC
#define COLOR_LIGHT_MAGENTA 0xD
#define COLOR_LIGHT_BROWN 0xE
#define COLOR_WHITE 0xF

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
        BG_COLOR = COLOR_LIGHT_CYAN;
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



unsigned short getpositionCursor()
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    unsigned short high = inb(FB_DATA_PORT);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    unsigned short low = inb(FB_DATA_PORT);
    return (high << 8) | low;
}


int fb_write(char *buf, unsigned int len)
{

    for(int i = 0; i < (int)len; i++)
    {
        fb_write_cell(getpositionCursor() *2, buf[i], FG_COLOR, BG_COLOR);
        fb_move_cursor(getpositionCursor()+ (unsigned short) 1);   
    }
    
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
}

int fb_move(unsigned short x, unsigned short y)
{
   unsigned short pos = (y * 80) + x;
   fb_move_cursor(pos);
}

int fb_new_line()
{
    int pos = getpositionCursor();
    int row = pos / 80;
    row++;
    fb_move(0, row);
}
#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

    int fb_clear();

    int fb_write(char *buf, unsigned int len); // provides an interface to write the buffer and length to the screen

    int fb_move(unsigned short x, unsigned short y); // provides an interface to move the cursor to the x and y position on the screen

    int fb_new_line();
    
    void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
    unsigned short getpositionCursor();
    int fb_new_line();

    int fb_backspace();
    void setFGColor(int color);
    void setBGColor(int color);
    char getc();
    
    int readCommand();

    int changeColor();

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

#endif

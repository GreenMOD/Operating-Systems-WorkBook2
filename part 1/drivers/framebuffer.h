#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

    int fb_clear();

    int fb_write(char *buf, unsigned int len); // provides an interface to write the buffer and length to the screen

    int fb_move(unsigned short x, unsigned short y); // provides an interface to move the cursor to the x and y position on the screen

    int fb_new_line();


#endif

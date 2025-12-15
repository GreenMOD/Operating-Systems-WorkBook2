#include "source/io.h"
#include "drivers/framebuffer.h"


int sum_of_three(int arg1, int arg2, int arg3)
{
    return (arg1 + arg2 + arg3);
}


int twentyFour()
{
    int msg = 36; //The EAX is in hexadecimal hence 36 == 24
    return msg;
}


int times_two(int x, int multiple)
{
    return x * multiple;
}


int main()
{
    fb_clear();
    fb_write("Hello, World", (unsigned int) 12);
    fb_new_line();
    fb_write("Sum of 1 + 2 + 3: ",18);
    char num = (sum_of_three(1,2,3));
    fb_write(num, 1);


    return 0;
}






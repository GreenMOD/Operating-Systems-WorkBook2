#include "drivers/io.h"
#include "drivers/framebuffer.h"
#include "drivers/hardware_interrupt_enabler.h"
#include "drivers/type.h"
#include "drivers/keyboard.h"
#include "drivers/interrupts.h"
#include "drivers/pic.h"



char sum_of_three(int arg1, int arg2, int arg3)
{
    return (arg1 + arg2 + arg3) + ('0');
}


int sixtySeven()
{ 
    return 67;
}


char times_two(int x, int multiple)
{
    return x * multiple;
}


int main()
{
    interrupts_install_idt(); //Install the Interrupt Descriptor Table (IDT) for handling interrupts
    pic_remap(0x20, 0x28);//Remap PIC to avoid conflicts with CPU exceptions
    enable_hardware_interrupts(); //Enable hardware interrupts (so we can use the keyboard)

    fb_clear();

    return 0;
}






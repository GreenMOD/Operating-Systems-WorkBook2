global loader ; entry symbol for ELF (Executable and Linkable Format)
extern twentyFour
extern times_two
extern sum_of_three
MAGIC_NUMBER equ 0x1BADB002 ; defines a constant
FLAGS equ 0x0 ; multiboot FLAGS
CHECKSUM equ -MAGIC_NUMBER ; A validation check magic + checksum + flags should be == 0
KERNEL_STACK_SIZE equ 4096 ; size of stack in bytes



    section .bss
        align 4 ; align at 4 bytes
        kernel_stack: ; label points to beginning of memory
            resb KERNEL_STACK_SIZE ; reserve stack for the kernel
            mov esp, kernel_stack + KERNEL_STACK_SIZE ; set the stack pointer to the top of the stack

    section .text
        align 4  ; accessing a 32 bit word if not 4 byte algined will cause a access violation exception
        dd MAGIC_NUMBER ; writes the magic number to the machine code
        dd FLAGS ; writes the flags to the machine
        dd CHECKSUM ; writes the checksum to the machine
    
    loader: ;loader label 
    .loop:
        
        jmp .loop   ;loops forever

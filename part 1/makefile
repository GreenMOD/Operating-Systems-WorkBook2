make build: ./source/link.ld #Compiles the loader and links it to create the kernel.elf file then creates an iso image
	gcc -m32 -c kmain.c -o kmain.o
	gcc -m32 -c ./drivers/framebuffer.c -o framebuffer.o
	nasm -f elf loader.asm -o loader.o
	nasm -f elf source/io.s -o io.o
	ld -T ./source/link.ld -melf_i386 loader.o kmain.o io.o framebuffer.o -o ./iso/boot/kernel.elf
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso


make run:
	qemu-system-i386 -display curses -monitor telnet::45454,server,nowait -serial mon:stdio -boot d -cdrom os.iso -m 32 -d cpu -D logQ.txt


make clean: 
	rm kmain.o loader.o io.o os.iso logQ.txt framebuffer.o iso/boot/kernel.elf


make new: 
	make build
	make run

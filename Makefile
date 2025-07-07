final : 4_makefile_project.elf

main.o : main.c
  arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnull main.c -o main.o
stm32_startup.o : stm32_startup.c
  arm-none-eabi-gcc -c mcpu=cortex-m4 -mthumb -std=gnull stm32_startup.c -o stm32_startup.o
4_makefile_project.elf : main.o stm32_startu.o
  arm-none-eabi-gcc -nostdlib -T stm32_ls.ld *.o -o 4_makefile_project.elf -W1 -Map=4_makefile_project.map
load :
  openocd -f board/st_nucleo_f4.cfg
clean:
del    -f *.o *.elf *.map

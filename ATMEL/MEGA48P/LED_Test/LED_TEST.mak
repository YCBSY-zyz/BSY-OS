CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -D_EE_EXTIO -DATMega48  -l -g -MHasMul -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x1000 -bfunc_lit:0x34.0x1000 -dram_end:0x2ff -bdata:0x100.0x2ff -dhwstk_size:30 -beeprom:0.256 -fihx_coff -S2
FILES = bsy_os.o led.o Led_Test.o putchar.o 

LED_TEST:	$(FILES)
	$(CC) -o LED_TEST $(LFLAGS) @LED_TEST.lk  
bsy_os.o: .\bsy_os.h C:\iccv7avr\include\stdlib.h C:\iccv7avr\include\_const.h C:\iccv7avr\include\limits.h C:\iccv7avr\include\iom48pv.h C:\iccv7avr\include\_iom48v.h C:\iccv7avr\include\stdio.h C:\iccv7avr\include\stdarg.h
bsy_os.o:	bsy_os.c
	$(CC) -c $(CFLAGS) bsy_os.c
led.o: .\led.h C:\iccv7avr\include\iom48pv.h C:\iccv7avr\include\_iom48v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\bsy_os.h C:\iccv7avr\include\stdlib.h C:\iccv7avr\include\_const.h C:\iccv7avr\include\limits.h
led.o:	led.c
	$(CC) -c $(CFLAGS) led.c
Led_Test.o: .\led_test.h C:\iccv7avr\include\iom48pv.h C:\iccv7avr\include\_iom48v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h C:\iccv7avr\include\eeprom.h .\bsy_os.h C:\iccv7avr\include\stdlib.h C:\iccv7avr\include\_const.h C:\iccv7avr\include\limits.h .\led.h
Led_Test.o:	Led_Test.c
	$(CC) -c $(CFLAGS) Led_Test.c
putchar.o: C:\iccv7avr\include\io8515v.h C:\iccv7avr\include\stdio.h C:\iccv7avr\include\stdarg.h C:\iccv7avr\include\_const.h
putchar.o:	putchar.c
	$(CC) -c $(CFLAGS) putchar.c

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0034   0004 =      4. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0034  __func_lit_start
       0038  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0038   0175 =    373. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0038  __lit_start
       0038  __ctype
       01AD  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   01AD   0046 =     70. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       01AD  __idata_start
       01F3  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   01F4   0E06 =   3590. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       00FA  __start
       00FA  __text_start
       011B  _exit
       011C  _Bsy_Os_Init
       0137  _Task_Schedule
       017D  _Task_Init
       0194  _Search_Node
       01B8  _Task_Add
       0221  _Task_Del
       0238  _Task_Manager
       028A  _timer2_ovf_isr
       02BB  _Led_Run
       02CC  _Task_led0
       02E6  _port_init
       02EB  _main
       02F5  _putchar$device_specific$
       030A  _memcpy
       0318  _memset
       0323  push_arg4
       0325  push_arg2
       0328  mod16u
       032A  div16u
       032B  xdiv16u
       0344  pop_xgset003C
       0349  pop_xgset00FC
       0350  pop_xgsetF0FC
       035B  push_xgsetF0FC
       035D  push_xgset30FC
       035F  push_xgset00FC
       0361  push_xgset003C
       0366  push_xgsetF00C
       036D  pop_xgsetF00C
       0374  push_xgsetF03C
       037D  pop_xgsetF03C
       0386  xicall
       038F  mpy16s
       03A3  __NewHeap
       03BB  _calloc
       03DC  _malloc
       045E  _realloc
       048B  __Merge
       055E  _free
       056E  _itoa
       05F0  _utoa
       0645  _islower
       0653  _toupper
       0669  __print
       07D0  _printf
       07E7  __assert
       07FD  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100   0046 =     70. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  _cur_thread
       0100  __data_start
       0101  _delay_cnt
       0103  _ledFlag
       0146  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0146   0028 =     40. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0146  _root
       0146  __bss_start
       0148  _LED0_Task_Handle
       0151  ___FreeList
       016C  __textmode
       016E  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0014 =     20. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
bsy_os.o	[ bsy_os.c ]
led.o	[ led.c ]
Led_Test.o	[ Led_Test.c ]
putchar.o	[ putchar.c ]
<library>	[ memcpy.s, memset.s, asave.s, div16u.s, gpop2.s, gpop3.s, gpop5.s, gpush.s, gpushz.s, gpushb.s, icall.s ]
[ mpy16s.s, newheap.s, freelist.s, alloc.s, itoa.s, utoa.s, islower.s, ctype.s, toupper.s, _printf.s ]
[ printf.s, textmode.s, assert.s ]

User Global Definitions

ram_end = 0x2ff
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x34
data = 0x100
eeprom:0.256


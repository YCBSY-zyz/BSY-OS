/* This putchar works with the 8515 UART. It will work with other devices
 * if their UART registers use the same names.  If the UART IO locations
 * are different from the 8515, then you will also have to change the
 * #include header file statement.
 *
 * This works with all the classic AVRs and some of the Mega devices as is.
 */
#include <io8515v.h>
#include <stdio.h>

extern int _textmode;

int putchar(char c)
{
    if (_textmode && c == '\n')
        putchar('\r');
    while ((USR & 0x20) == 0)   // UDRE, data register empty
        ;
    UDR = c;
    return c;
}



#ifndef   __LED_H_
#define   __LED_H_

#include   <iom48pv.h>
#include   <macros.h>


#define  led0_on     (PORTC |= BIT(PC2))
#define  led0_off    (PORTC &= ~BIT(PC2))

#define  led1_on     (PORTC |= BIT(PC3))
#define  led1_off    (PORTC &= ~BIT(PC3))

#define  led2_on     (PORTC |= BIT(PC4))
#define  led2_off    (PORTC &= ~BIT(PC4))


extern void Task_led0(void);




#endif



/*****************************************************************************
                     Microchip Technology Incorporated

    FileName:        key.h
    Dependencies:    See Includes Section
    Processor:       PIC24, PIC32

Copyright � 2009-2013 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

******************************************************************************/
#ifndef KEY_H
#define KEY_H
#include <stdbool.h>
#include <stdint.h>
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    uint8_t id;

    union
    {
        struct
        {
            uint8_t mode      :4;
            uint8_t state     :1;
        };

        uint8_t flags;
    };

    uint16_t time;
    
    uint16_t time_last_off; //if now is released, counting released time; if now is pressing, store last time released time(only for treble action)
    uint8_t last_action;    //KEY_EVENT_PRIMARY or KEY_EVENT_SECONDARY or KEY_EVENT_DOUBLE_CLICK 
}
KEY_STATE;

////////////////////////////////////////////////////////////////////////////////

#define KEY_MODE_DISABLED       0
#define KEY_MODE_CONTINUOUS     1
#define KEY_MODE_AUTOREPEAT     2
#define KEY_MODE_SINGLE_ACTION  3
#define KEY_MODE_DUAL_ACTION    4
#define KEY_MODE_TREBLE_ACTION  5

#define KEY_EVENT_PRIMARY           1        //KEY_MODE_CONTINUOUS,KEY_MODE_AUTOREPEAT,KEY_MODE_SINGLE_ACTION,KEY_MODE_DUAL_ACTION.TREBLE action don't use this event
#define KEY_EVENT_SECONDARY         2        //KEY_MODE_DUAL_ACTION, KEY_MODE_TREBLE_ACTION support this event
#define KEY_EVENT_DOUBLE_CLICK      3        //KEY_MODE_TREBLE_ACTION support only
#define KEY_EVENT_SECONDARY_RELEASED    5       //KEY_MODE_DUAL_ACTION, assit to KEY_EVENT_SECONDARY event
#define KEY_EVENT_LONG_TIME_HOLD   0x10    //event that KEY is holding for many seconds
#define KEY_EVENT_NOT_HANDLE        0xFF

#define KEY_SINGLE_ACTION_DELAY     1000     // all in ms
#define KEY_AUTOREPEAT_DELAY        500
#define KEY_AUTOREPEAT_RATE         200     // = 5 per sec
#define KEY_TREBLE_ACTION_OFF_DELAY 200

#define KEY_LONG_ACTION_DELAY     2000     // all in ms


#define KEY_TASK_PERIOD         100

/* key list definetion relative to ADC value */
#define KEYT            50      /* adc tolerance */
#define KEY0            1023    // 1023 = 0x3FF   /* no key status */

#define KEY1            20       /* adc value */ // 0.3v  Vref 3.30v
#define KEY2            129      //0.4171
#define KEY3            281     // 0.90
#define KEY4            442     // 1.42
#define KEY5            618     // 1.99






////////////////////////////////////////////////////////////////////////////////

// TODO change codes
enum{
	KEY_ID_POWER,
	KEY_ID_BT,
    KEY_ID_PLAY_PAUSE,
    KEY_ID_BROADCAST,
    KEY_ID_VOL_UP,
    KEY_ID_VOL_DN,
};

////////////////////////////////////////////////////////////////////////////////
void KEY_Timer1MS_event(void);
void KEY_Initialize (void );
void KEY_Task ( void );
void KEY_Process ( KEY_STATE *key, uint16_t time );

extern void KEY_Handler ( uint8_t key, uint8_t event );

bool Is_KeyWorking(void);


////////////////////////////////////////////////////////////////////////////////
#endif


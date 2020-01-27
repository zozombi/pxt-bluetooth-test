 /**
*/


#include "pxt.h"
#include "MicroBitUARTService.h"
#include <cstdint>
#include <math.h>

using namespace pxt;
MicroBitUARTService *uart;



namespace BTlight {
    // #define MICROBIT_SD_GATT_TABLE_SIZE             0x500
    


    //%
    void BT_init(void) {
        uart = new MicroBitUARTService(*uBit.ble, 32, 32); 
        uBit.display.scroll("AVM");    
    }

    //%
    uint16_t BT_send(int16_t ADCVal) {
        return ADCVal * .976;
    }
} 
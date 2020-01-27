 /**
*/


#include "pxt.h"
// #include "MicroBitUARTService.h"
#include <cstdint>
#include <math.h>

using namespace pxt;

namespace BTlight {
    //%
    void BT_init(void) {
        // MicroBitUARTService *uart;
        // uart = new MicroBitUARTService(*uBit.ble, 32, 32); 
        uBit.display.scroll("AVM");    
        // release_fiber();
    }

    //%
    uint16_t BT_send(int16_t ADCVal) {
        return ADCVal * .976;
    }
} 
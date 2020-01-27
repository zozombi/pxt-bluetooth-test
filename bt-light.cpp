 /**
*/
#include "pxt.h"
#include "MicroBitUARTService.h"
#include <cstdint>
#include <math.h>

using namespace pxt;
MicroBitUARTService *uart;

namespace BTlight {
    //%
    void onConnected(MicroBitEvent e) {
        uBit.display.scroll("C");
    }


    //%
    uint16_t BT_init(int x) {
        uart = new MicroBitUARTService(*uBit.ble, 32, 32); 
        uBit.display.scroll("AVM"); 
        uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);   
        release_fiber();
        return 111111;
    }

    //%
    uint16_t BT_send(int16_t ADCVal) {
        return ADCVal * .976;
    }
} 
 /**
*/


#include "pxt.h"
#include "MicroBitUARTService.h"
#include <cstdint>
#include <math.h>

using namespace pxt;
MicroBitUARTService *uart;

namespace BTlight {
    /*
    *
    */
    //%
    uint16_t BT_send(int16_t ADCVal) {

        return ADCVal * .976;
    }
} 
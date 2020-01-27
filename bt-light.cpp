 /**
*/


#include "pxt.h"
#include <cstdint>
#include <math.h>

using namespace pxt;

namespace BTlight {
    /*
    *
    */
    //%
    uint16_t BT_send(int16_t ADCVal) {

        return ADCVal * .976;
    }
} 
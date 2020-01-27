/**
*/


/**
 * Functions to operate the bluetooth
 */

enum BTtype {
    UART = 1,
    neco = 2,
}

//% color=#f44242 icon="\uf185"
namespace BTlight {
    /**
    *
    */
    //% weight=30 blockId="BTlight_BTinit" block="init UART"
    export function BTinit() {
        BT_init(0);
    }
    //% weight=30 blockId="BTlight_BTsend" block="send UART"
    export function BTsend(packet: number): number {
        return 2;
    }
}

/**
 * Function used for simulator, actual implementation is in gatorlight.cpp
 */
//% shim=BTlight::BT_send
function BT_send(ADCVal: number) {
    // Fake function for simulator
    return 0
}
//% shim=BTlight::BT_init
function BT_init(x: number) {
    // Fake function for simulator
    return 0;
}
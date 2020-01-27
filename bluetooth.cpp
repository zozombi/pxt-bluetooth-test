#include "pxt.h"
#include "MESEvents.h"
#include "MicroBitUARTService.h"
#include "BLEHF2Service.h"

using namespace pxt;

/**
 * Support for additional bt services.
 */
//% color=#0082FB weight=96 icon="\uf294"
namespace bt {
    MicroBitUARTService *uart = NULL;
    BLEHF2Service* pHF2 = NULL;

    //%
    void __log(String msg) {
        if (NULL == pHF2)
            pHF2 = new BLEHF2Service(*uBit.ble);
        pHF2->sendSerial(msg->getUTF8Data(), msg->getUTF8Size(), false);
    }

    /**
    *  Starts the bt accelerometer service
    */
    //% help=bt/start-accelerometer-service
    //% blockId=bt_start_accelerometer_service block="bt accelerometer service"
    //% parts="bt" weight=90 blockGap=8
    void startAccelerometerService() {
        new MicroBitAccelerometerService(*uBit.ble, uBit.accelerometer);        
    }   

    /**
    *  Starts the bt button service
    */
    //% help=bt/start-button-service
    //% blockId=bt_start_button_service block="bt button service" blockGap=8
    //% parts="bt" weight=89
    void startButtonService() {
        new MicroBitButtonService(*uBit.ble);      
    }

    /**
    *  Starts the bt IO pin service.
    */
    //% help=bt/start-io-pin-service
    //% blockId=bt_start_io_pin_service block="bt io pin service" blockGap=8
    //% parts="bt" weight=88
    void startIOPinService() {
        new MicroBitIOPinService(*uBit.ble, uBit.io);
    }

    /**
    *  Starts the bt LED service
    */
    //% help=bt/start-led-service
    //% blockId=bt_start_led_service block="bt led service" blockGap=8
    //% parts="bt" weight=87
    void startLEDService() {
        new MicroBitLEDService(*uBit.ble, uBit.display);
    }

    /**
    *  Starts the bt temperature service
    */
    //% help=bt/start-temperature-service
    //% blockId=bt_start_temperature_service block="bt temperature service" blockGap=8
    //% parts="bt" weight=86
    void startTemperatureService() {    
        new MicroBitTemperatureService(*uBit.ble, uBit.thermometer);        
    }

    /**
    *  Starts the bt magnetometer service
    */
    //% help=bt/start-magnetometer-service
    //% blockId=bt_start_magnetometer_service block="bt magnetometer service"
    //% parts="bt" weight=85
    void startMagnetometerService() {    
        new MicroBitMagnetometerService(*uBit.ble, uBit.compass); 
    }


    /**
    *  Starts the bt UART service
    */
    //% help=bt/start-uart-service
    //% blockId=bt_start_uart_service block="bt uart service"
    //% parts="bt" advanced=true
    void startUartService() {
        if (uart) return;
        // 61 octet buffer size is 3 x (MTU - 3) + 1
        // MTU on nRF51822 is 23 octets. 3 are used by Attribute Protocol header data leaving 20 octets for payload
        // So we allow a RX buffer that can contain 3 x max length messages plus one octet for a terminator character
        uart = new MicroBitUARTService(*uBit.ble, 61, 60);
    }
    
    //%
    void uartWriteString(String data) {
        startUartService();
    	uart->send(MSTR(data));
    }    

    //%
    String uartReadUntil(String del) {
        startUartService();
        return PSTR(uart->readUntil(MSTR(del)));
    }    


    /**
    * Sends a buffer of data via bt UART
    */
    //%
    void uartWriteBuffer(Buffer buffer) {
        startUartService();
        uart->send(buffer->data, buffer->length);
    }

    /**
    * Reads buffered UART data into a buffer
    */
    //%
    Buffer uartReadBuffer() {
        startUartService();
        int bytes = uart->rxBufferedSize();
        auto buffer = mkBuffer(NULL, bytes);
        int read = uart->read(buffer->data, buffer->length);
        // read failed
        if (read < 0) {
            decrRC(buffer);
            return mkBuffer(NULL, 0);
        }
        // could not fill the buffer
        if (read != buffer->length) {
            auto tmp = mkBuffer(buffer->data, read); 
            decrRC(buffer); 
            buffer = tmp;
        }
        return buffer;
    }

    /**
    * Registers an event to be fired when one of the delimiter is matched.
    * @param delimiters the characters to match received characters against.
    */
    //% help=bt/on-uart-data-received
    //% weight=18 blockId=bt_on_data_received block="bt|on data received %delimiters=serial_delimiter_conv"
    void onUartDataReceived(String delimiters, Action body) {
      startUartService();
      uart->eventOn(MSTR(delimiters));
      registerWithDal(MICROBIT_ID_BLE_UART, MICROBIT_UART_S_EVT_DELIM_MATCH, body);
    }

    /**
     * Register code to run when the micro:bit is connected to over bt
     * @param body Code to run when a bt connection is established
     */
    //% help=bt/on-bt-connected weight=20
    //% blockId=bt_on_connected block="on bt connected" blockGap=8
    //% parts="bt"
    void onbtConnected(Action body) {
        registerWithDal(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, body);
    }    

     /**
     * Register code to run when a bt connection to the micro:bit is lost
     * @param body Code to run when a bt connection is lost
     */
    //% help=bt/on-bt-disconnected weight=19
    //% blockId=bt_on_disconnected block="on bt disconnected"
    //% parts="bt"
    void onbtDisconnected(Action body) {
        registerWithDal(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, body);
    } 

    const int8_t CALIBRATED_POWERS[] = {-49, -37, -33, -28, -25, -20, -15, -10};
    /**
    * Advertise an Eddystone URL
	* @param url the url to transmit. Must be no longer than the supported eddystone url length, eg: "https://makecode.com"
	* @param power power level between 0 and 7, eg: 7
    * @param connectable true to keep bt connectable for other services, false otherwise.
    */
    //% blockId=eddystone_advertise_url block="bt advertise url %url|with power %power|connectable %connectable"
    //% parts=bt weight=11 blockGap=8
    //% help=bt/advertise-url blockExternalInputs=1
    void advertiseUrl(String url, int power, bool connectable) {
#if CONFIG_ENABLED(MICROBIT_BLE_EDDYSTONE_URL)
        power = min(MICROBIT_BLE_POWER_LEVELS-1, max(0, power));
        int8_t level = CALIBRATED_POWERS[power];
        uBit.bleManager.advertiseEddystoneUrl(MSTR(url), level, connectable);
        uBit.bleManager.setTransmitPower(power);
#endif
    }

    /**
    * Advertise an Eddystone UID
	* @param nsAndInstance 16 bytes buffer of namespace (bytes 0-9) and instance (bytes 10-15)
	* @param power power level between 0 and 7, eg: 7
    * @param connectable true to keep bt connectable for other services, false otherwise.
    */
    //% parts=bt weight=12 advanced=true
    void advertiseUidBuffer(Buffer nsAndInstance, int power, bool connectable) {
#if CONFIG_ENABLED(MICROBIT_BLE_EDDYSTONE_UID)        
        auto buf = nsAndInstance;
        if (buf->length != 16) return;

        power = min(MICROBIT_BLE_POWER_LEVELS-1, max(0, power));
        int8_t level = CALIBRATED_POWERS[power];
        uBit.bleManager.advertiseEddystoneUid((const char*)buf->data, (const char*)buf->data + 10, level, connectable);
#endif
    }

    /**
    * Sets the bt transmit power between 0 (minimal) and 7 (maximum).
    * @param power power level between 0 (minimal) and 7 (maximum), eg: 7.
    */
    //% parts=bt weight=5 help=bt/set-transmit-power advanced=true
    //% blockId=bt_settransmitpower block="bt set transmit power %power"
    void setTransmitPower(int power) {
        uBit.bleManager.setTransmitPower(min(MICROBIT_BLE_POWER_LEVELS-1, max(0, power)));
    }

    /**
    * Stops advertising Eddystone end points
    */
    //% blockId=eddystone_stop_advertising block="bt stop advertising"
    //% parts=bt weight=10
    //% help=bt/stop-advertising advanced=true
    void stopAdvertising() {
        uBit.bleManager.stopAdvertising();
    } 
}
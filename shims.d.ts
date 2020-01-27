// Auto-generated. Do not edit.


    /**
     * Support for additional bt services.
     */
    //% color=#0082FB weight=96 icon="\uf294"
declare namespace bt {

    /**
     *  Starts the bt accelerometer service
     */
    //% help=bt/start-accelerometer-service
    //% blockId=bt_start_accelerometer_service block="bt accelerometer service"
    //% parts="bt" weight=90 blockGap=8 shim=bt::startAccelerometerService
    function startAccelerometerService(): void;

    /**
     *  Starts the bt button service
     */
    //% help=bt/start-button-service
    //% blockId=bt_start_button_service block="bt button service" blockGap=8
    //% parts="bt" weight=89 shim=bt::startButtonService
    function startButtonService(): void;

    /**
     *  Starts the bt IO pin service.
     */
    //% help=bt/start-io-pin-service
    //% blockId=bt_start_io_pin_service block="bt io pin service" blockGap=8
    //% parts="bt" weight=88 shim=bt::startIOPinService
    function startIOPinService(): void;

    /**
     *  Starts the bt LED service
     */
    //% help=bt/start-led-service
    //% blockId=bt_start_led_service block="bt led service" blockGap=8
    //% parts="bt" weight=87 shim=bt::startLEDService
    function startLEDService(): void;

    /**
     *  Starts the bt temperature service
     */
    //% help=bt/start-temperature-service
    //% blockId=bt_start_temperature_service block="bt temperature service" blockGap=8
    //% parts="bt" weight=86 shim=bt::startTemperatureService
    function startTemperatureService(): void;

    /**
     *  Starts the bt magnetometer service
     */
    //% help=bt/start-magnetometer-service
    //% blockId=bt_start_magnetometer_service block="bt magnetometer service"
    //% parts="bt" weight=85 shim=bt::startMagnetometerService
    function startMagnetometerService(): void;

    /**
     *  Starts the bt UART service
     */
    //% help=bt/start-uart-service
    //% blockId=bt_start_uart_service block="bt uart service"
    //% parts="bt" advanced=true shim=bt::startUartService
    function startUartService(): void;

    /**
     * Sends a buffer of data via bt UART
     */
    //% shim=bt::uartWriteBuffer
    function uartWriteBuffer(buffer: Buffer): void;

    /**
     * Reads buffered UART data into a buffer
     */
    //% shim=bt::uartReadBuffer
    function uartReadBuffer(): Buffer;

    /**
     * Registers an event to be fired when one of the delimiter is matched.
     * @param delimiters the characters to match received characters against.
     */
    //% help=bt/on-uart-data-received
    //% weight=18 blockId=bt_on_data_received block="bt|on data received %delimiters=serial_delimiter_conv" shim=bt::onUartDataReceived
    function onUartDataReceived(delimiters: string, body: () => void): void;

    /**
     * Register code to run when the micro:bit is connected to over bt
     * @param body Code to run when a bt connection is established
     */
    //% help=bt/on-bt-connected weight=20
    //% blockId=bt_on_connected block="on bt connected" blockGap=8
    //% parts="bt" shim=bt::onbtConnected
    function onbtConnected(body: () => void): void;

    /**
     * Register code to run when a bt connection to the micro:bit is lost
     * @param body Code to run when a bt connection is lost
     */
    //% help=bt/on-bt-disconnected weight=19
    //% blockId=bt_on_disconnected block="on bt disconnected"
    //% parts="bt" shim=bt::onbtDisconnected
    function onbtDisconnected(body: () => void): void;

    /**
     * Advertise an Eddystone URL
     * @param url the url to transmit. Must be no longer than the supported eddystone url length, eg: "https://makecode.com"
     * @param power power level between 0 and 7, eg: 7
     * @param connectable true to keep bt connectable for other services, false otherwise.
     */
    //% blockId=eddystone_advertise_url block="bt advertise url %url|with power %power|connectable %connectable"
    //% parts=bt weight=11 blockGap=8
    //% help=bt/advertise-url blockExternalInputs=1 shim=bt::advertiseUrl
    function advertiseUrl(url: string, power: int32, connectable: boolean): void;

    /**
     * Advertise an Eddystone UID
     * @param nsAndInstance 16 bytes buffer of namespace (bytes 0-9) and instance (bytes 10-15)
     * @param power power level between 0 and 7, eg: 7
     * @param connectable true to keep bt connectable for other services, false otherwise.
     */
    //% parts=bt weight=12 advanced=true shim=bt::advertiseUidBuffer
    function advertiseUidBuffer(nsAndInstance: Buffer, power: int32, connectable: boolean): void;

    /**
     * Sets the bt transmit power between 0 (minimal) and 7 (maximum).
     * @param power power level between 0 (minimal) and 7 (maximum), eg: 7.
     */
    //% parts=bt weight=5 help=bt/set-transmit-power advanced=true
    //% blockId=bt_settransmitpower block="bt set transmit power %power" shim=bt::setTransmitPower
    function setTransmitPower(power: int32): void;

    /**
     * Stops advertising Eddystone end points
     */
    //% blockId=eddystone_stop_advertising block="bt stop advertising"
    //% parts=bt weight=10
    //% help=bt/stop-advertising advanced=true shim=bt::stopAdvertising
    function stopAdvertising(): void;
}


    /**
     */

declare namespace BTlight {
}

// Auto-generated. Do not edit. Really.

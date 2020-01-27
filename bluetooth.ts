/// <reference no-default-lib="true"/>
/**
 * Support for additional bt services.
 */
//% color=#007EF4 weight=96 icon="\uf294"
namespace bt {
    export let NEW_LINE = "\r\n";

    /**
     * Internal use
     */
    //% shim=bt::__log
    export function __log(msg: string) {
        return;
    }
    console.addListener(function (msg) { __log(msg) });

    /**
    *  Writes to the bt UART service buffer. From there the data is transmitted over bt to a connected device.
    */
    //% help=bt/uart-write-string weight=80
    //% blockId=bt_uart_write block="bt uart|write string %data" blockGap=8
    //% parts="bt" shim=bt::uartWriteString advanced=true
    export function uartWriteString(data: string): void {
        console.log(data)
    }

    /**
    *  Writes to the bt UART service buffer. From there the data is transmitted over bt to a connected device.
    */
    //% help=bt/uart-write-line weight=79
    //% blockId=bt_uart_line block="bt uart|write line %data" blockGap=8
    //% parts="bt" advanced=true
    export function uartWriteLine(data: string): void {
        uartWriteString(data + serial.NEW_LINE);
    }

    /**
     * Prints a numeric value to the serial
     */
    //% help=bt/uart-write-number weight=79
    //% weight=89 blockGap=8 advanced=true
    //% blockId=bt_uart_writenumber block="bt uart|write number %value"
    export function uartWriteNumber(value: number): void {
        uartWriteString(value.toString());
    }

    /**
     * Writes a ``name: value`` pair line to the serial.
     * @param name name of the value stream, eg: x
     * @param value to write
     */
    //% weight=88 weight=78
    //% help=bt/uart-write-value advanced=true
    //% blockId=bt_uart_writevalue block="bt uart|write value %name|= %value"
    export function uartWriteValue(name: string, value: number): void {
        uartWriteString((name ? name + ":" : "") + value + NEW_LINE);
    }

    /**
     *  Reads from the bt UART service buffer, returning its contents when the specified delimiter character is encountered.
     */
    //% help=bt/uart-read-until weight=75
    //% blockId=bt_uart_read block="bt uart|read until %del=serial_delimiter_conv"
    //% parts="bt" shim=bt::uartReadUntil advanced=true
    export function uartReadUntil(del: string): string {
        // dummy implementation for simulator
        return ""
    }

    /**
    * Advertise an Eddystone UID
    * @param ns 4 last bytes of the namespace uid
    * @param instance 4 last bytes of the instance uid
    * @param power power level between 0 and 7, eg: 7
    * @param connectable true to keep bt connectable for other services, false otherwise.
    */
    //% blockId=eddystone_advertise_uid block="bt advertise UID|namespace (bytes 6-9)%ns|instance (bytes 2-6)%instance|with power %power|connectable %connectable"
    //% parts=bt weight=12 blockGap=8
    //% help=bt/advertise-uid blockExternalInputs=1
    export function advertiseUid(ns: number, instance: number, power: number, connectable: boolean) {
        const buf = pins.createBuffer(16);
        buf.setNumber(NumberFormat.Int32BE, 6, ns);
        buf.setNumber(NumberFormat.Int32BE, 12, instance);
        bt.advertiseUidBuffer(buf, power, connectable);
    }
}

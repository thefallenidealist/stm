/*
* -------------------------------------------------------------------------------------------------
* "THE BEER-WARE LICENSE" (Revision 42):
* <propaliidealist@gmail.com> wrote this file. As long as you retain this notice you can do whatever
* you want with this stuff. If we meet some day, and you think this stuff is worth it, you can buy
* me a beer in return. Johnny Sorocil 
* -------------------------------------------------------------------------------------------------
*/

// possible newer version on github.com/fallenidealist ... TODO
// for newer version check ...

/*

   Opis
   	Ovo je repo koji demonstrira koristenje raznih HW uredjaja
	HW uredjaji:
		GLCD ILI9341
		nRF24L01	wireless transiver
		EEPROM AT24C32 
		Flash W25Q	TODO
		BMP180 baro and termometer
		external I2C RTC
		ESP8266 WLAN	// TODO provjerit tocan naziv

	Internal STM32 devices
		RTC


	Otic u examples folder, npr examples/nRF i tamo napravit make (GNU make
	required)

*/

/*
   text editor settings:
   vim set tw=100:sw=4:ts=4:	// TODO provjerit
   textwidth=100
*/

/*
   Third party libraries:
   	ST firmware (located under src/lib dir)
	ARM CMSIS // TODO koji tocno fajlovi


   */

/*
   Toolchan
   	Tested on Unixoid with CLI tools

   ARM toolchain
   	clang 3.6
	gcc-arm binutils
	newlib from gcc-arm package
	openOCD (needed for gmake upload to work)
   AVR toolchain
    // TODO
*/

/*
   Tested on HW:
   	STM32F407 (ARM Cortex-M4F (as Cortex-M3))
	STM32F103	// TODO
	ATmega8 (AVR8)	// TODO
	ATmega328
	ATmega16
	// TODO opisat HW fuseve od AVRa, frekvenciju
*/

/*
   How to build
   	cd repo/examples/blinky && gmake upload		(if you are using OpenOCD)


*/

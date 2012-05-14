/* Teensy RawHID example
 * http://www.pjrc.com/teensy/rawhid.html
 * Copyright (c) 2009 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above description, website URL and copyright notice and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include "usb_rawhid.h"
#include "analog.h"
#include "uart.h"

#define BAUD_RATE 9600

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

#define BUFFER_SIZE 64

uint8_t buffer[BUFFER_SIZE];

int main(void)
{
	int8_t r;
	uint8_t i;

	CPU_PRESCALE(CPU_16MHz);
	uart_init(BAUD_RATE);

	// Initialize the USB, and then wait for the host to set configuration.
	// If the Teensy is powered without a PC connected to the USB port,
	// this will wait forever.
	usb_init();
	while (!usb_configured()) /* wait */ ;

	// Configure port B for input
	DDRB = 0x00;
	PORTB = 0x00;

	// Configure unused pins for output to save power
	DDRC=0xF;
	DDRE=0xF;
	DDRF=0xF;


	// Turn on LED
	PORTD |= (1<<6);

	// Wait for Speakjet to be ready
	while(!(PINB & 0x01));

	while (1) {

		// if received data, do something with it
		r = usb_rawhid_recv(buffer, 0);
		if (r > 0) {
			
			for (i = 0; i < r; i++) {
				while(PINB & (1 << 1));

				// If special end-of-buffer byte has been reached, break
				// as there's no more data to read
				if (buffer[i] == 255) {
					break;
				}

				// Write byte to Speakjet
				uart_putchar(buffer[i]);
			}

			usb_rawhid_send(buffer, 50);
		}
	}
}

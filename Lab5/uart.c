/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include "uart.h"
#include <stdint.h>


void uart_init(void){
	//TODO
  //enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= 0b00000010;

  //enable clock to UART1
  SYSCTL_RCGCUART_R |= 0b00000010;

  //wait for GPIOB and UART1 peripherals to be ready
  while (SYSCTL_PRGPIO_R & 0b00000010 == 0) {};
  while (SYSCTL_PRUART_R & 0b00000010 == 0) {};

  //enable alternate functions on port B pins
  GPIO_PORTB_AFSEL_R |= 0b00000011;

  //enable digital functionality on port B pins
  GPIO_PORTB_DEN_R |= 0b00000011;

  //enable UART1 Rx and Tx on port B pins
  GPIO_PORTB_PCTL_R = 0x00000011;

  //calculate baud rate
  uint16_t iBRD = 0x08; //use equations     Cable: 0x68     Wifi: 0x08
  uint16_t fBRD = 43; //use equations     Cable: 0x0B     Wifi: 43

  //turn off UART1 while setting it up
  UART1_CTL_R &= 0xFFF7;

  //set baud rate
  //note: to take effect, there must be a write to LCRH after these assignments
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
  //note: this write to LCRH must be after the BRD assignments
  UART1_LCRH_R = 0x00000060;

  //use system clock as source
  //note from the datasheet UARTCCC register description:
  //field is 0 (system clock) by default on reset
  //Good to be explicit in your code
  UART1_CC_R = 0x0;

  //re-enable UART1 and also enable RX, TX (three bits)
  //note from the datasheet UARTCTL register description:
  //RX and TX are enabled by default on reset
  //Good to be explicit in your code
  UART1_CTL_R = 0x0301;

}

void uart_sendChar(char data){
	while((UART1_FR_R & 0x20) != 0){}

	UART1_DR_R = data;

}

char uart_receive(void){
    char rdata;

    while((UART1_FR_R & 0x10) != 0){}

    rdata = (char)UART1_DR_R;

    return rdata;
}

void uart_sendStr(const char *data){
	//TODO for reference see lcd_puts from lcd.c file
}

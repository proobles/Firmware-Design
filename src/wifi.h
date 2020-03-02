/*
 * wifi.h
 *
 * Created: 2/5/2020 9:02:35 PM
 *  Author: pauli
 */ 

#ifndef WIFI_H_
#define WIFI_H_

#include <asf.h>
#include <string.h>

#define BOARD_ID_USART             ID_USART0
#define WIFI_USART                 USART0
#define BOARD_USART_BAUDRATE       115200
#define USART_Handler              USART0_Handler
#define USART_IRQn                 USART0_IRQn

#define ALL_INTERRUPT_MASK  0xffffffff

/** USART1 pin RX */
#define PIN_USART1_RXD    {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART1_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

/** USART1 pin TX */
#define PIN_USART1_TXD    {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART1_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

/** USART1 pin CTS */
#define PIN_USART1_CTS    {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART1_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

/** USART1 pin RTS */
#define PIN_USART1_RTS    {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_RTS_IDX        (PIO_PA7_IDX)
#define PIN_USART1_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

#define PUSH_BUTTON_ID                 ID_PIOA
#define PUSH_BUTTON_PIO                PIOA
#define PUSH_BUTTON_PIN_MSK            PIO_PA22
#define PUSH_BUTTON_ATTR               PIO_IT_RISE_EDGE

volatile uint32_t button_flag;

#define command_complete_ID                 ID_PIOA
#define command_complete_PIO                PIOA
#define command_complete_PIN_MSK            PIO_PA13
#define command_complete_ATTR               PIO_IT_RISE_EDGE

volatile uint32_t command_complete;

void configure_usart_wifi(void);
void configure_wifi_comm_pin(void);
void process_incoming_byte_wifi(uint8_t in_byte);
void process_data_wifi();
void write_image_to_file(void)

volatile char input_line_wifi[1000];
volatile uint32_t received_byte_wifi;
volatile unsigned int input_pos_wifi;

int start_transfer = 0;
int no_stream = 0;

#endif
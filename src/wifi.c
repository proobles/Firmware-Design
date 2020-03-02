/*
 * wifi.c
 *
 * Created: 2/5/2020 9:02:06 PM
 *  Author: pauli
 */ 

#include <asf.h>
#include <wifi.h>
#include <camera.h>

volatile uint32_t button_flag = false;
volatile uint32_t received_byte_wifi = 0;
volatile unsigned int input_pos_wifi = 0;
int count = 0;
void wifi_USART_Handler(void) //1
{
	uint32_t ul_status;

	/* Read USART status. */
	ul_status = usart_get_status(WIFI_USART);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_RXBUFF) {
		usart_read(WIFI_USART, &received_byte_wifi);
		process_incoming_byte_wifi((uint8_t)received_byte_wifi);
	}
}

void process_incoming_byte_wifi(uint8_t in_byte) {//2
	input_line_wifi[input_pos_wifi++] = in_byte;
}

void wifi_command_response_handler(uint32_t ul_id, uint32_t ul_mask)//3
{
	unused(ul_id);
	unused(ul_mask);
	process_data_wifi();
	for (int jj = 0;jj<1000;jj++) input_line_wifi[jj] = 0;
	input_pos_wifi = 0;
}

void process_data_wifi() {//4
	if (strstr(input_line_wifi, "start transfer")) {
		start_transfer = 1;
	}
	if (strstr(input_line_wifi, "none")) {
		no_stream = 1;
	}
}
void wifi_web_setup_handler(uint32_t ul_id, uint32_t ul_mask)//5
{
	unused(ul_id);
	unused(ul_mask);
	button_flag = true;
	
}
void configure_usart_wifi(void)//6
{
	gpio_configure_pin(PIN_USART1_RXD_IDX, PIN_USART1_RXD_FLAGS);
	gpio_configure_pin(PIN_USART1_TXD_IDX, PIN_USART1_TXD_FLAGS);
	gpio_configure_pin(PIN_USART1_CTS_IDX, PIN_USART1_CTS_FLAGS);
	//gpio_configure_pin(PIN_USART1_RTS_IDX, PIN_USART1_RTS_FLAGS);
	
	static uint32_t ul_sysclk;
	const sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};

	/* Get peripheral clock. */
	ul_sysclk = sysclk_get_peripheral_hz();

	/* Enable peripheral clock. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART. */
	usart_init_hw_handshaking(WIFI_USART, &usart_console_settings, ul_sysclk);

	/* Disable all the interrupts. */
	usart_disable_interrupt(WIFI_USART, ALL_INTERRUPT_MASK);
	
	/* Enable TX & RX function. */
	usart_enable_tx(WIFI_USART);
	usart_enable_rx(WIFI_USART);
	
	usart_enable_interrupt(WIFI_USART, US_IER_RXRDY);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
}

void configure_wifi_comm_pin(void)//7
pmc_enable_periph_clk(command_complete_ID);
	/* Adjust PIO debounce filter using a 10 Hz filter. */
	pio_set_debounce_filter(command_complete_PIO, command_complete_PIN_MSK, 10);
	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(command_complete_PIO, command_complete_ID, command_complete_PIN_MSK,
			PUSH_BUTTON_ATTR, wifi_command_response_handler);
			
	NVIC_EnableIRQ((IRQn_Type)command_complete_ID);
	
	pio_enable_interrupt(command_complete_PIO, command_complete_PIN_MSK);
}

void configure_wifi_web_setup_pin(void){//8
	pmc_enable_periph_clk(PUSH_BUTTON_ID);
	/* Adjust PIO debounce filter using a 10 Hz filter. */
	pio_set_debounce_filter(PUSH_BUTTON_PIO, PUSH_BUTTON_PIN_MSK, 10);
	/* Initialize PIO interrupt handler, see PIO definition in conf_board.h
	**/
	pio_handler_set(PUSH_BUTTON_PIO, PUSH_BUTTON_ID, PUSH_BUTTON_PIN_MSK,
			PUSH_BUTTON_ATTR, wifi_web_setup_handler);
			
	NVIC_EnableIRQ((IRQn_Type)PUSH_BUTTON_ID);
	
	pio_enable_interrupt(PUSH_BUTTON_PIO, PUSH_BUTTON_PIN_MSK);
}

void write_wifi_command(char* comm, uint8_t cnt)//9
{
	usart_write_line(WIFI_USART, comm);
	while (count<cnt)
	{
		if (command_complete == true){
			break;
		}
		delay_ms(1000);
		count++;
	}
}

void write_image_to_file(void)//10
{
	char image_transfer_str[15] = "image_transfer ";
	char image_len_str[4];
	char image_transfer_comm[19];
	char sub_buff[4];
	int start_pos;
	int	end_pos;
	
	if (find_image_len())
	{	int image_len_int = find_image_len();
		sprintf(image_len_str,"%d",image_len_int);
		strcat(image_transfer_comm,image_transfer_str);
		strcat(image_transfer_comm,image_len_str);
		write_wifi_command(image_transfer_comm,2);
		for(int ii=0; ii<=IM_BUFFSIZE-4;ii+4){
			int sub_buff_pos=0; //substring of buffer
			while (sub_buff_pos<4){
				sub_buff[sub_buff_pos] = im_buff[sub_buff_pos+ii];
			}
			if (strstr(sub_buff,JPEG_START)){
				start_pos = ii;
				end_pos = start_pos + image_len_int-1;
			}
		process_data_wifi();
		if (start_transfer==1){
		for (int jj=start_pos; jj<=end_pos; jj++){
			usart_write_line(WIFI_USART,&im_buff[jj]);
		}	
		delay_ms(1000);
		}
		start_transfer=0;
	}
}
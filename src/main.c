/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <wifi.h>
#include <camera.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
while(1){
	
}

	//reset the wifi module
	//wait for the connection
	//if wifi web setup flag is true
		// place wifi chip in setup mode
		//clear flag
	//else wait for connection
	
	//main loop:
	//if not connected and wifi web setup flag is true
		// put the wifi chip into web setup mode
		// clear the wifi web setup flag
	// if not connected to network
		//
		ffd8 ffd9
		length in between
}

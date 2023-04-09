/*
 * BMSH.cpp
 *
 *  Created on: 25 dic. 2022
 *      Author: alejandro
 */

#include "Examples/examples.hpp"

int main(void) {

	BMSH bmsh = BMSH(SPI::spi3);
	STLIB::start();

	bmsh.wake_up();

//	update_configuration2(bmsh);
//	read_gpio(bmsh);
//	read_voltages(bmsh);
	balance_batteries(bmsh);

	while(1){};
}

void Error_Handler(void) {
	ErrorHandler("HAL error handler triggered");
}

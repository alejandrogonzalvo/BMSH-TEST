/*
 * BMSH.cpp
 *
 *  Created on: 25 dic. 2022
 *      Author: alejandro
 */

#include "Examples/examples.hpp"

int main(void) {

	BMSH bmsh = BMSH(SPI::spi3);
	STLIB::start(Nucleo);

	bmsh.wake_up();

	Time::register_high_precision_alarm(100, [&](){
		bmsh.send_command(BMS::COMMAND::READ_CONFIGURATION_REGISTER_GROUP);
	});

	while(1){};
}

void Error_Handler(void) {
	ErrorHandler("HAL error handler triggered");
}

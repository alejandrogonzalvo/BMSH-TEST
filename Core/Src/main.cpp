/*
 * BMSH.cpp
 *
 *  Created on: 25 dic. 2022
 *      Author: alejandro
 */

#include "Examples/examples.hpp"

int main(void) {
	STLIB::start(Nucleo);

	BMSH bmsh = BMSH(SPI::spi3);
	bmsh.wake_up();

	Time::register_high_precision_alarm(100, [&](){
		bmsh.send_command(BMS::COMMAND::READ_CONFIGURATION_REGISTER_GROUP);
	});
}

void Error_Handler(void) {
	ErrorHandler("HAL error handler triggered");
}

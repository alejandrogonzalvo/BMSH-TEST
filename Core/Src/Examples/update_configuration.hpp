#include "ST-LIB.hpp"
#include "../Runes/Runes.hpp"
#include "BMSH/BMSH.hpp"

void update_configuration(BMSH& bmsh) {

	  LTC6811::configuration& adc_config = bmsh.external_adcs[0].peripheral_configuration;
	  adc_config.set_references(true);

	  bmsh.update_configuration();

	  array<uint8_t, 8> rx = { 0 };

	  Time::register_high_precision_alarm(10000, [&](){
		  bmsh.wake_up();
		  bmsh.send_receive_command(BMS::COMMAND::READ_CONFIGURATION_REGISTER_GROUP, rx);
		  bmsh.send_receive_command(BMS::COMMAND::READ_STATUS_REGISTER_GROUP_A, rx);
		  uint16_t temp = rx[2] + (((uint16_t)rx[3])<<8);
		  float ftemp = temp * (0.0001 / 0.0075) - 273;
		  printf("temperatura interna: %f\n", ftemp);
	  });

//	  Time::register_high_precision_alarm(5000000, [&](){
//
//		for (uint8_t i : iota(0, 12)) {
//			  adc_config.set_cell_discharging(i, not adc_config.is_cell_discharging(0));
//		}
//		  bmsh.update_configuration();
//
//	  });

	  while(1){};
}

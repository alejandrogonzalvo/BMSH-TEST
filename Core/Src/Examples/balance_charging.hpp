#include "ST-LIB.hpp"
#include "../Runes/Runes.hpp"
#include "BMSH/BMSH.hpp"

void update_configuration(BMSH& bmsh) {

	  LTC6811::configuration& adc_config = bmsh.external_adcs[0].peripheral_configuration;
	  adc_config.set_references(true);

	  bmsh.update_configuration();

	  array<uint8_t, 8> rx;

	  Time::register_high_precision_alarm(1000, [&](){
		  bmsh.send_receive_command(BMS::COMMAND::READ_CONFIGURATION_REGISTER_GROUP, rx);
	  });

	  Time::register_high_precision_alarm(5000000, [&](){
		  adc_config.set_cell_discharging(0, not adc_config.is_cell_discharging(0));

		  bmsh.update_configuration();

	  });

	  while(1){};
}

#include "ST-LIB.hpp"
#include "../Runes/Runes.hpp"
#include "BMSH/BMSH.hpp"
#include <stdlib.h>

void read_voltages(BMSH& bmsh) {
	LTC6811::configuration& adc_config = bmsh.get_config(0);
	for (uint8_t i : iota(0, 12)) {
		adc_config.set_cell_discharging(i, false);
	}

	Time::register_low_precision_alarm(20, [&](){
	  bmsh.start_adc_conversion_all_cells();
	});

	HAL_Delay(3);

	Time::register_low_precision_alarm(3, [&](){
		bmsh.read_cell_voltages();
	});

	Time::register_low_precision_alarm(100, [&]() {

		for (uint8_t j : iota(0, (int)BMS::EXTERNAL_ADCS*2)) {
			for (uint8_t i : iota(0, Battery::CELLS)) {
				printf("bat %d | cell %d: %.4fV\t", j+1, i+1, bmsh.get_cell(i+(j*Battery::CELLS)));
			}
			printf("\n\r");
		}
		printf("end\n\r");
	});

	while (1) {}
}


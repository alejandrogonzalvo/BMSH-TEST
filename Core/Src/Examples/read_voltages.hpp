#include "ST-LIB.hpp"
#include "../Runes/Runes.hpp"
#include "BMSH/BMSH.hpp"

void read_voltages(BMSH& bmsh) {
	LTC6811::configuration& adc_config = bmsh.get_config(0);
	adc_config.set_references(true);
	adc_config.set_adc_optimal_mode(true);
	for (uint8_t i : iota(0, 12)) {
		adc_config.set_cell_discharging(i, false);
	}


	bmsh.start_adc_conversion_all_cells();
	HAL_Delay(5);


	Time::register_low_precision_alarm(20, [&](){
	  bmsh.start_adc_conversion_all_cells();
	});

	HAL_Delay(3);

	Time::register_low_precision_alarm(5, [&](){
	  bmsh.read_cell_voltages();
	});

	Time::register_low_precision_alarm(100, [&]() {
		printf("\n\n\n\r");

		for (uint8_t i : iota(0, Battery::CELLS)) {
			printf("bat 1 | cell %d = %fV\t\t\tbat2 | cell %d = %f\n\r", i, bmsh.get_cell(i), i, bmsh.get_cell(i+Battery::CELLS));
		}

		for (uint8_t i : iota(0, Battery::CELLS)) {
			printf("bat 3 | cell %d = %fV\t\t\tbat4 | cell %d = %f\n\r", i, bmsh.get_cell(i+Battery::CELLS*2), i, bmsh.get_cell(i+Battery::CELLS*3));
		}
	});

	while (1) {}
}


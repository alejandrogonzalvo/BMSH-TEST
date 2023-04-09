#include "ST-LIB.hpp"
#include "../Runes/Runes.hpp"
#include "BMSH/BMSH.hpp"

void read_gpio(BMSH& bmsh) {
	LTC6811::configuration& adc_config = bmsh.get_config(0);
	for (uint8_t i : iota(0, 12)) {
		adc_config.set_cell_discharging(i, false);
	}

	array<uint8_t, 16> rx = { 0 };
	uint16_t temp;


	Time::register_low_precision_alarm(20, [&](){
		bmsh.start_adc_conversion_gpio();
	});

	HAL_Delay(3);

	Time::register_low_precision_alarm(3, [&](){
		bmsh.read_temperatures();
	});

	Time::register_low_precision_alarm(100, [&]() {
		printf("\n\n\n");
		for (uint8_t i : iota(0, 2)) {
			printf("bat 1 | gpio %d = %fV\t\t\tbat2 | gpio %d = %f\n\r", i, bmsh.get_gpio(i), i, bmsh.get_gpio(i+2));
		}

		for (uint8_t i : iota(0, 2)) {
			printf("bat 3 | gpio %d = %fV\t\t\tbat4 | gpio %d = %f\n\r", i, bmsh.get_gpio(i+2*2), i, bmsh.get_gpio(i+2*3));
		}
	});

	while (1) {}
}


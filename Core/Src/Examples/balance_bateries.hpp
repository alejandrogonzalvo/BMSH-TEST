#include "ST-LIB.hpp"
#include "../Runes/Runes.hpp"
#include "BMSH/BMSH.hpp"
#include <stdlib.h>

#define add_action_ms Time::register_low_precision_alarm
#define fori(x) for (int i=0; i<=x; i++)
#define forj(x) for (int j=0; j<=x; j++)
void balance_batteries(BMSH& bmsh) {

	forj(BMS::EXTERNAL_ADCS) {
		LTC6811::configuration& adc_config = bmsh.get_config(j);
		for (uint8_t i : iota(0, 12)) {
			adc_config.set_cell_discharging(i, false);
		}
	}

	add_action_ms(20, [&](){
	  bmsh.wake_up();
	  bmsh.start_adc_conversion_all_cells();
	});

	HAL_Delay(5);

	add_action_ms(20, [&](){
		bmsh.wake_up();
		bmsh.measure_internal_device_parameters();
	});

	HAL_Delay(5);

	array<uint8_t, BMS::EXTERNAL_ADCS*8> rx = { 0 };
	uint16_t temp;
	float ftemp;
	add_action_ms(20, [&](){
		bmsh.wake_up();
		bmsh.read_cell_voltages();
		bmsh.read_internal_temperature();

		temp = rx[2] + (((uint16_t)rx[3])<<8);
		ftemp = temp * (0.0001 / 0.0075) - 273;
	});

	add_action_ms(1000, [&]() {


		bmsh.start_balancing();
		if (ftemp > 70) {
			forj(BMS::EXTERNAL_ADCS) {
				LTC6811::configuration& adc_config = bmsh.get_config(j);
				fori(12){
					adc_config.set_cell_discharging(i, false);
				}
			}
			bmsh.wake_up();
			bmsh.update_configuration();
			printf("-1");
//			exit(0);
		}

		for (uint8_t j : iota(0, (int)BMS::EXTERNAL_ADCS*2)) {
			for (uint8_t i : iota(0, Battery::CELLS)) {
				printf(",%.4f", bmsh.get_cell(i+(j*Battery::CELLS)));
			}
		}

		printf("@");

		fori(BMS::EXTERNAL_ADCS) {
			printf(",%.4f", bmsh.external_adcs[i].internal_temperature);
		}

		printf("@");

		forj(BMS::EXTERNAL_ADCS) {
			LTC6811::configuration& adc_config = bmsh.get_config(j);
			fori(12) {
				if (adc_config.is_cell_discharging(i)) {
					printf(",B");
				} else {
					printf(",NB");
				}
			}
		}

		printf("@");

		for (uint8_t j : iota(0, (int)BMS::EXTERNAL_ADCS*2)) {
			for (uint8_t i : iota(0, Battery::CELLS)) {
				printf(",%.4f", bmsh.get_cell(i+(j*Battery::CELLS)));
			}
		}

		printf("\n");

	});

	while (1) {}
}


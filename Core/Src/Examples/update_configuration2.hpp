#include "ST-LIB.hpp"
#include "../Runes/Runes.hpp"
#include "BMSH/BMSH.hpp"

void update_configuration2(BMSH& bmsh) {
	bool balancing = false;

	LTC6811::configuration& adc_config = bmsh.external_adcs[0].peripheral_configuration;
	adc_config.set_references(true);

		for (uint8_t i : iota(0, 12)) {
			  adc_config.set_cell_discharging(i, false);
		}
	balancing = false;

	bmsh.wake_up();
	bmsh.update_configuration();

	array<uint8_t, 8> rx = { 0 };
	Time::register_low_precision_alarm(20, [&](){
	  bmsh.wake_up();
	  bmsh.send_command(BMS::COMMAND::MEASURE_INTERNAL_DEVICE_PARAMETERS);
	});

	HAL_Delay(3);

	Time::register_low_precision_alarm(20, [&](){
	  bmsh.wake_up();
	  bmsh.start_adc_conversion_all_cells();
	});



	HAL_Delay(3);

	Time::register_low_precision_alarm(10, [&](){
		bmsh.wake_up();
		bmsh.read_cell_voltages();
		bmsh.send_receive_command(BMS::COMMAND::READ_STATUS_REGISTER_GROUP_A, rx);
	});

	 HAL_Delay(2);

	 Time::register_low_precision_alarm(100, [&]() {

		bmsh.wake_up();
		bmsh.send_receive_command(BMS::COMMAND::READ_STATUS_REGISTER_GROUP_A, rx);
		bmsh.read_cell_voltages();

		uint16_t temp = rx[2] + (((uint16_t)rx[3])<<8);
		float ftemp = temp * (0.0001 / 0.0075) - 273;

		printf("\n\n\n\n\r");
		printf("\ttemperatura interna: %f", ftemp);
		if (adc_config.is_cell_discharging(0)) {
			printf("\tBALANCEANDO\n\n");
		} else {
			printf("\tNO BALANCEANDO\n\n");
		}

		for (uint8_t i : iota(0, Battery::CELLS)) {
			printf("bat 1 | cell %d = %.4f V\t\t\tbat2 | cell %d = %.4f V\n\r", i, bmsh.get_cell(i), i, bmsh.get_cell(i+Battery::CELLS));
		}
		for (uint8_t i : iota(0, Battery::CELLS)) {
			printf("bat 3 | cell %d = %fV\t\t\tbat4 | cell %d = %f\n\r", i, bmsh.get_cell(i+Battery::CELLS*2), i, bmsh.get_cell(i+Battery::CELLS*3));
		}

		if (ftemp > 50 and balancing) {
			printf("saliendo, sobrecalientamiento");
			for (uint8_t i : iota(0, 12)) {
				  adc_config.set_cell_discharging(i, false);
			}
			balancing = false;
			bmsh.wake_up();
			bmsh.update_configuration();
			printf("Sobrecalentamiento, deteniendo balanceo");
		}

		if (ftemp < 30 and not balancing) {
			for (uint8_t i : iota(0, 12)) {
				  adc_config.set_cell_discharging(i, true);
			}
			balancing = true;

			bmsh.wake_up();
			bmsh.update_configuration();
			printf("iniciando balanceo");
		}


	  });

	  while(1){};
}

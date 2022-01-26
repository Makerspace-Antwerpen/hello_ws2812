/* Copyright (c) 2017 pcbreflux. All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>. *
 */
#include <string.h>
#include <stdlib.h>

#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_system.h"

#include "ws2812.h"

#define TAG "MAIN"

#define GPIO GPIO_NUM_22
#define NLEDS 16

void ws2812_task(void *pvParameters) {
	WS2812 strip(GPIO, NLEDS, 0);

	while(1) {
		for( int i = 0; i < NLEDS; i++ ) {
			strip.setPixel( i, 255, 0, 0 );
		}
		strip.show();
	}
	ESP_LOGI(TAG, "All done!");

	vTaskDelete(NULL);
}

extern "C" {
	void app_main() {
	    xTaskCreate(ws2812_task, "ws2812 task", 12288, NULL, 5, NULL);
	}
}
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

char ssid[] = "ssid";
char pass[] = "pass";

const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;

int connect_to_wifi(void) {
  if (cyw43_arch_init_with_country(CYW43_COUNTRY_FRANCE)) {
    cyw43_arch_gpio_put(LED_PIN, 1);

    while(1) {
      printf("Failed to init WiFi\n");
      sleep_ms(1000);
    }
  }

  cyw43_arch_enable_sta_mode();

  int wifi_connection_status = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000);

  if (wifi_connection_status != 0) {
    cyw43_arch_gpio_put(LED_PIN, 1);

    while(1) {
      printf("Failed to connect to Wifi: %d\n", wifi_connection_status);
      sleep_ms(1000);
    }
  }

  return 0;
}

int main() {
  stdio_init_all();
  connect_to_wifi();

  while(1) {
    printf("Connected !\n");

    cyw43_arch_gpio_put(LED_PIN, 1);
    sleep_ms(250);
    cyw43_arch_gpio_put(LED_PIN, 0);
    sleep_ms(250);
  }
}

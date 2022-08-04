#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;

int main() {
  printf("Init\n");
  stdio_init_all();

  if (cyw43_arch_init()) {
    printf("WiFi init failed\n");
    return -1;
  }
  else {
    printf("WiFi init succeed!");
  }

  while (true) {
    printf("On");
    cyw43_arch_gpio_put(LED_PIN, 1);

    sleep_ms(250);

    printf("Off");
    cyw43_arch_gpio_put(LED_PIN, 0);

    sleep_ms(250);
  }
}

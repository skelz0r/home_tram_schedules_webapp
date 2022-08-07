#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"

char ssid[] = "ssid";
char pass[] = "pass";

const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;

/* WIFI CONNECTION */
int connect_to_wifi(void) {
  printf("WiFi: Init\n");

  if (cyw43_arch_init_with_country(CYW43_COUNTRY_FRANCE)) {
    while(1) {
      printf("WiFi: Failed to init\n");
      sleep_ms(1000);
    }
  }

  cyw43_arch_enable_sta_mode();

  cyw43_arch_gpio_put(LED_PIN, 1);

  int wifi_connection_status = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000);

  if (wifi_connection_status != 0) {
    cyw43_arch_gpio_put(LED_PIN, 0);

    while(1) {
      printf("WiFi: Failed to connect: %d\n", wifi_connection_status);
      sleep_ms(1000);
    }
  }

  printf("WiFi: Connected !\n");

  return 0;
}

/* FETCH DATA */
struct tcp_pcb* testpcb;

static void tcp_client_err(void *arg, err_t err) {
  printf("tcp_client_err: begin\n");

  if (err != ERR_ABRT) {
    printf("tcp_client_err: erreur %d\n", err);
  }
}

err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
  printf("tcp_client_recv: begin\n");

  if (!p) {
    printf("tcp_client_recv: no buffer\n");
  }

  return ERR_OK;
}

static err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len) {
  printf("tcp_client_sent %u\n", len);

  return ERR_OK;
}

uint32_t tcp_send_packet(void) {
  printf("TCP send: begin.\n");

  char *string = "GET / HTTP/1.0\r\nHost: tram.skelz0r.fr\r\n\r\n ";
  uint32_t len = strlen(string);

  /* push to buffer */
  err_t error = tcp_write(testpcb, string, strlen(string), TCP_WRITE_FLAG_COPY);

  if (error) {
    printf("ERROR: Code: %d (tcp_send_packet :: tcp_write)\n", error);
    return 1;
  }

  /* now send */
  error = tcp_output(testpcb);
  if (error) {
    printf("ERROR: Code: %d (tcp_send_packet :: tcp_output)\n", error);
    return 1;
  }

  return 0;

  printf("TCP send: end.\n");
}

err_t connectCallback(void *arg, struct tcp_pcb *tpcb, err_t err) {
  printf("TCP Connect: Connection established.\n");

  tcp_send_packet();

  return 0;
}

void tcp_setup(void) {
  printf("TCP Setup: Begin.\n");

  uint32_t data = 0xdeadbeef;

  ip_addr_t remote_ip;
  IP4_ADDR(&remote_ip, 91,166,46,209);

  /* create the control block */
  testpcb = tcp_new();    //testpcb is a global struct tcp_pcb
                          // as defined by lwIP

  /* dummy data to pass to callbacks*/
  tcp_arg(testpcb, &data);

  /* register callbacks with the pcb */
  tcp_err(testpcb, tcp_client_err);
  tcp_recv(testpcb, tcp_client_recv);
  tcp_sent(testpcb, tcp_client_sent);

  /* now connect */
  printf("TCP Setup: Connecting to %s port %u\n", ip4addr_ntoa(&remote_ip), 16900);
  tcp_connect(testpcb, &remote_ip, 16900, connectCallback);
  printf("TCP Setup: End.\n");
}

int fetch_tram_data(void) {
  tcp_setup();

  return 0;
}

/*  */

int main() {
  stdio_init_all();
  connect_to_wifi();
  fetch_tram_data();

  /* while(1) { */
  /*   printf("Connected !\n"); */
  /*  */
  /*   cyw43_arch_gpio_put(LED_PIN, 1); */
  /*   sleep_ms(250); */
  /*   cyw43_arch_gpio_put(LED_PIN, 0); */
  /*   sleep_ms(250); */
  /* } */
}

#include <bcm2835.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include "string.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <regex>
#include <RH_RF95.h>

#define BOARD_LORASPI

#include "RasPiBoards.h"

#include <assert.h>
#include <string>
#include "easywsclient/easywsclient.hpp"

// RF_95 configuration
#define RF_FREQUENCY  868.00
#define RF_NODE_ID    80

RH_RF95 rf95(RF_CS_PIN, RF_IRQ_PIN);

using easywsclient::WebSocket;
static WebSocket::pointer ws = NULL;
static const std::string SERVER_WS_URL = "ws://192.168.1.226:8888/ws";
volatile sig_atomic_t force_exit = false;

void sig_handler(int sig)
{
  printf("\n%s Break received, exiting!\n", __BASEFILE__);
  force_exit=true;
}

int main (int argc, const char* argv[] )
{
  unsigned long led_blink = 0;

  signal(SIGINT, sig_handler);
  printf( "%s\n", __BASEFILE__);

  if (!bcm2835_init()) {
    fprintf( stderr, "%s bcm2835_init() Failed\n", __BASEFILE__ );
    return 1;
  }

#ifdef RF_LED_PIN
  pinMode(RF_LED_PIN, OUTPUT);
  digitalWrite(RF_LED_PIN, HIGH );
#endif

#ifdef RF_IRQ_PIN
  pinMode(RF_IRQ_PIN, INPUT);
  bcm2835_gpio_set_pud(RF_IRQ_PIN, BCM2835_GPIO_PUD_DOWN);
  bcm2835_gpio_ren(RF_IRQ_PIN);
#endif

#ifdef RF_RST_PIN
  pinMode(RF_RST_PIN, OUTPUT);
  digitalWrite(RF_RST_PIN, LOW );
  bcm2835_delay(150);
  digitalWrite(RF_RST_PIN, HIGH );
  bcm2835_delay(100);
#endif

#ifdef RF_LED_PIN
  digitalWrite(RF_LED_PIN, LOW );
#endif

  if (!rf95.init()) {
    fprintf( stderr, "\nRF95 module init failed, Please verify wiring/module\n" );
  } else {

    rf95.setTxPower(14, false);
    rf95.setFrequency(RF_FREQUENCY);
    rf95.setThisAddress(RF_NODE_ID);
    rf95.setHeaderFrom(RF_NODE_ID);
    rf95.setPromiscuous(true);
    rf95.setModeRx();

    ws = WebSocket::from_url(SERVER_WS_URL);
    int packet_num = 0;
    std::regex packet_pattern("([0-9]+);([+-]?([0-9]*[.])?[0-9]+);([+-]?([0-9]*[.])?[0-9]+);([+-]?([0-9]*[.])?[0-9]+);([0-1])");
    
    printf( "Node ID: %d; Freq: %3.2fMHz\n", RF_NODE_ID, RF_FREQUENCY );
    printf( "Configurating LoRa successed\n" );

    while (!force_exit) {

#ifdef RF_IRQ_PIN
      if (bcm2835_gpio_eds(RF_IRQ_PIN)) {
        bcm2835_gpio_set_eds(RF_IRQ_PIN);
#endif

        if (rf95.available()) {
#ifdef RF_LED_PIN
          led_blink = millis();
          digitalWrite(RF_LED_PIN, HIGH);
#endif
          uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
          uint8_t len  = sizeof(buf);
          uint8_t from = rf95.headerFrom();
          uint8_t to   = rf95.headerTo();
          uint8_t id   = rf95.headerId();
          uint8_t flags= rf95.headerFlags();;
          int8_t rssi  = rf95.lastRssi();
	
	  char buf_char[len];

//std::cout <<std::endl;


	 // std::cout << buf_str;

          if (rf95.recv(buf, &len)) {
            printf("Packet received | Len: %02d; From node id %d; RSSI: %ddB; Packet: ", len, from, to, rssi);
            printbuffer(buf, len);
            
	    for (int i = 0; i < 32; i++) { 
	    	buf_char[i] = (char)buf[i];
            }
            
            std::string buf_str = std::string(buf_char);
//std::cout  << buf_str << std::endl;
	    if (std::regex_match(buf_str, packet_pattern) == 1) {
		            
  ws->send(buf_str);
                if (ws->getReadyState() != WebSocket::CLOSED) {
                  ws->poll();
              }
            }
          } else {
            printf("Error while receiving\n");
          }
          printf("\n");
        }

	packet_num++;
#ifdef RF_IRQ_PIN
      }
#endif

//    delete ws;

#ifdef RF_LED_PIN
      if (led_blink && millis()-led_blink>200) {
        led_blink = 0;
        digitalWrite(RF_LED_PIN, LOW);
      }
#endif
      // Switch context for allowing OS take other threads
      bcm2835_delay(5);
    }
  }

#ifdef RF_LED_PIN
  digitalWrite(RF_LED_PIN, LOW );
#endif
  printf( "\n%s Ending\n", __BASEFILE__ );
  delete ws;
  bcm2835_close();
  return 0;
}

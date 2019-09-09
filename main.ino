
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"
#include <SoftwareSerial.h>

#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);
String content = "";

void setup() {
  Serial.begin(115200);
  if (!ble.begin(VERBOSE_MODE)) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  ble.echo(false);
  Serial.println("Requesting Bluefruit info:");
  ble.info();
  ble.verbose(false);
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop() {
  while (ble.available()) {
    char c = (char)ble.read();
    if (c == '/') {
      Serial.println(content);
      colorToggle(content);
      content = "";
    } else {
      content.concat(c);
    }
  }

#include <esp_now.h>
#include <WiFi.h>
#include "esp_now_midi.h"
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// USB MIDI object
Adafruit_USBD_MIDI usb_midi;

// Attach usb_midi as the transport.
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

uint8_t macAddressMoth[]  =  {0x12, 0x34, 0x56, 0x78, 0x9A, 0x00};
uint8_t macAddressMoon[]  =  {0x12, 0x34, 0x56, 0x78, 0x9A, 0x01};

// on the dongle: run the print_mac firmware and paste it here
uint8_t peerMacAddress[6] = { 0x84, 0xF7, 0x03, 0xF5, 0x29, 0x24 };
esp_now_midi ESP_NOW_MIDI;

// there has been a change in the callback signature with esp32 board version 3.3.0, hence this is here for backwards compatibility
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 3, 0)
void customOnDataSent(const wifi_tx_info_t* info, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failure");
}
#else
void customOnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failure");
}
#endif

// ❌ REMOVE this second definition – it duplicates customOnDataSent and will cause an error
// void customOnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   // Serial.print("Custom Callback - Status: ");
//   // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failure");
// }

void onNoteOn(byte channel, byte note, byte velocity) {
  MIDI.sendNoteOn(note, velocity, channel);
}

void onNoteOff(byte channel, byte note, byte velocity) {
  MIDI.sendNoteOff(note, velocity, channel);
}

void onPolyAfterTouch(byte channel, byte note, byte value) {
  MIDI.sendAfterTouch(note, value, channel);
}

void MIDIsetup() {
  // Manual begin() is required on core without built-in support e.g. mbed rp2040
  if (!TinyUSBDevice.isInitialized()) {
    TinyUSBDevice.begin(0);
  }

  Serial.begin(115200);
  usb_midi.setStringDescriptor("TinyUSB MIDI");

  // Initialize MIDI, and listen to all MIDI channels
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // If already enumerated, re-enumerate
  if (TinyUSBDevice.mounted()) {
    TinyUSBDevice.detach();
    delay(10);
    TinyUSBDevice.attach();
  }

  // ❌ These referenced *undefined* functions:
  // MIDI.setHandleNoteOn(handleNoteOn);
  // MIDI.setHandleNoteOff(handleNoteOff);
}  // <<< CLOSE MIDIsetup properly

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_wifi_set_mac(WIFI_IF_STA, macAddressMoth);

  ESP_NOW_MIDI.setup(macAddressMoon, customOnDataSent);
  // ESP_NOW_MIDI.setup(destinationMacAddress);

  ESP_NOW_MIDI.setHandleNoteOn(onNoteOn);
  ESP_NOW_MIDI.setHandleNoteOff(onNoteOff);
  ESP_NOW_MIDI.setHandleAfterTouchPoly(onPolyAfterTouch);

  MIDIsetup();

  // register as a client by sending any message
  ESP_NOW_MIDI.sendControlChange(127, 127, 16);
}

void loop() {
}
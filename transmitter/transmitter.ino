#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xE9E8F0F0E1LL;   // IMPORTANT: The same as in the receiver
RF24 radio(9, 10); // select CE, CSN pin

struct Signal {
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
  byte aux1;
  byte aux2;
  byte led1;
  byte led2;
};

Signal data;

void ResetData() {
  data.throttle = 12;  // Motor stop (Signal lost position)
  data.pitch = 127;    // Center (Signal lost position)
  data.roll = 127;     // Center (Signal lost position)
  data.yaw = 127;      // Center (Signal lost position)
  data.aux1 = 127;     // Center (Signal lost position)
  data.aux2 = 127;     // Center (Signal lost position)
  data.led1 = 0;       // Switch off position
  data.led2 = 0;       // Switch off position
}

void setup() {
  radio.begin();
  radio.openWritingPipe(pipeOut);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening(); // start the radio communication for Transmitter
  ResetData();
}

void loop() {
  int val1 = analogRead(A0);
  int val2 = analogRead(A1);
  int val3 = analogRead(A2);
  int val4 = analogRead(A3);
  int val5 = analogRead(A4);
  int val6 = analogRead(A5);
  int val7 = digitalRead(2);
  int val8 = digitalRead(3);

  val1 = map(val1, 0, 1023, 0, 255);
  val2 = map(val2, 0, 1023, 0, 255);
  val3 = map(val3, 0, 1023, 0, 255);
  val4 = map(val4, 0, 1023, 0, 255);
  val5 = map(val5, 0, 1023, 0, 255);
  val6 = map(val6, 0, 1023, 0, 255);

  data.throttle = val1;
  data.yaw = val2;
  data.pitch = val3;
  data.roll = val4;
  data.aux1 = val5;
  data.aux2 = val6;
  data.led1 = val7;
  data.led2 = val8;

  radio.write(&data, sizeof(Signal));
}
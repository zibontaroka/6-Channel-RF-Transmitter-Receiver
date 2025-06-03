#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;
int ch_width_5 = 0;
int ch_width_6 = 0;
int ch_width_7 = 0;
int ch_width_8 = 0;
int led11;
int led22;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;

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

const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(7, 8);

void ResetData() {
  data.roll = 127;        // Center
  data.pitch = 127;       // Center
  data.throttle = 12;     // Motor Stop
  data.yaw = 127;         // Center
  data.aux1 = 127;        // Center
  data.aux2 = 127;        // Center
}

void setup() {
  ch1.attach(2);
  ch2.attach(3);
  ch3.attach(4);
  ch4.attach(5);
  ch5.attach(6);
  led11 = A0;
  led22 = A1;

  pinMode(led11, OUTPUT);
  pinMode(led22, OUTPUT);

  ResetData();
  radio.begin();
  radio.openReadingPipe(1, pipeIn);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening(); // start the radio communication for receiver
}

unsigned long lastRecvTime = 0;

void recvData() {
  while (radio.available()) {
    radio.read(&data, sizeof(Signal));
    lastRecvTime = millis(); // receive the data
  }
}

void loop() {
  recvData();
  unsigned long now = millis();
  if (now - lastRecvTime > 1000) {
    ResetData(); // Signal lost, reset data
  }

  ch_width_1 = map(data.throttle, 0, 255, 1000, 2000); // pin D2 (PWM signal)
  ch_width_2 = map(data.yaw, 0, 255, 1000, 2000);      // pin D3 (PWM signal)
  ch_width_3 = map(data.pitch, 0, 255, 1000, 2000);    // pin D4 (PWM signal)
  ch_width_4 = map(data.roll, 0, 255, 1000, 2000);     // pin D5 (PWM signal)
  ch_width_5 = map(data.aux1, 0, 255, 1000, 2000);     // pin D6 (PWM signal)
  ch_width_6 = map(data.aux2, 0, 255, 1000, 2000);     // pin D7 (PWM signal)
  ch_width_7 = data.led1;                              // pin A0 (Digital signal)
  ch_width_8 = data.led2;                              // pin A1 (Digital signal)

  ch1.writeMicroseconds(ch_width_1);
  ch2.writeMicroseconds(ch_width_2);
  ch3.writeMicroseconds(ch_width_3);
  ch4.writeMicroseconds(ch_width_4);
  ch5.writeMicroseconds(ch_width_5);
  ch6.writeMicroseconds(ch_width_6);

  digitalWrite(led11, ch_width_7 == HIGH ? HIGH : LOW);
  digitalWrite(led22, ch_width_8 == HIGH ? HIGH : LOW);
}
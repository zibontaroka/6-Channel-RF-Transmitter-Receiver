# 6 Channel Transmitter and Receiver

This project implements a 6-channel transmitter and receiver system using Arduino and the nRF24L01 RF module. The transmitter reads analog and digital inputs to control throttle, pitch, roll, yaw, and two auxiliary channels, along with two LED switches. The receiver outputs PWM signals to control servos and digital signals for LEDs.

## Table of Contents
- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Wiring](#wiring)
- [Usage](#usage)
- [File Structure](#file-structure)
- [License](#license)

## Project Overview
The system consists of two Arduino sketches:
- **Transmitter**: Reads input from six analog pins (A0-A5) for throttle, yaw, pitch, roll, and two auxiliary channels, and two digital pins (D2, D3) for LED switches. Data is transmitted via the nRF24L01 module.
- **Receiver**: Receives data from the transmitter and outputs PWM signals to six servo channels (D2-D7) and digital signals to two LEDs (A0, A1).

## Hardware Requirements
- 2x Arduino boards (e.g., Uno, Nano)
- 2x nRF24L01 RF modules
- 6x Servos (for receiver)
- 2x LEDs (for receiver)
- Potentiometers or joysticks (for transmitter inputs)
- Push buttons or switches (for transmitter LED controls)
- Jumper wires and breadboard

## Software Requirements
- Arduino IDE
- Libraries:
  - [RF24](https://github.com/nRF24/RF24)
  - [SPI](https://www.arduino.cc/en/Reference/SPI) (included with Arduino IDE)
  - [Servo](https://www.arduino.cc/en/Reference/Servo) (included with Arduino IDE)

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/6-channel-transmitter-receiver.git
   ```
2. Install the required libraries in the Arduino IDE:
   - Go to `Sketch > Include Library > Manage Libraries`.
   - Search for and install `RF24`.
3. Open the `.ino` files in the Arduino IDE.
4. Upload `transmitter.ino` to the transmitter Arduino and `receiver.ino` to the receiver Arduino.

## Wiring
### Transmitter
- **nRF24L01**:
  - CE: Pin 9
  - CSN: Pin 10
  - Connect MOSI, MISO, SCK to Arduino's SPI pins
  - VCC: 3.3V
  - GND: GND
- **Inputs**:
  - A0-A5: Analog inputs (e.g., potentiometers)
  - D2, D3: Digital inputs (e.g., push buttons for LEDs)

### Receiver
- **nRF24L01**:
  - CE: Pin 7
  - CSN: Pin 8
  - Connect MOSI, MISO, SCK to Arduino's SPI pins
  - VCC: 3.3V
  - GND: GND
- **Outputs**:
  - D2-D7: Servo PWM outputs
  - A0, A1: LED digital outputs

## Usage
1. Power on both the transmitter and receiver.
2. The transmitter reads analog inputs (A0-A5) and digital inputs (D2, D3), mapping them to control signals.
3. The receiver converts received signals to PWM outputs for servos (1000-2000 microseconds) and digital outputs for LEDs.
4. If the receiver loses the signal for more than 1 second, it resets to safe default values.

## File Structure
```
6-channel-transmitter-receiver/
├── transmitter.ino       # Transmitter Arduino sketch
├── receiver.ino          # Receiver Arduino sketch
├── README.md             # Project documentation
└── .gitignore            # Git ignore file
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details."# 6-Channel-RF-Transmitter-Receiver" 

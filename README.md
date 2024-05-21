# Bluetooth-Control-Car-with-Automatic-Braking-System
Follow This link for BlueTooth Control Part:<br>
```
https://www.youtube.com/watch?v=Q36NbjPMV5k
```
# Bluetooth Documentation 
    https://howtomechatronics.com/tutorials/arduino/arduino-and-hc-05-bluetooth-module-tutorial/


# For #include <AFMotor.h>
    https://github.com/adafruit/Adafruit-Motor-Shield-library

# Language Reference
    https://www.arduino.cc/reference/en/

# Programming 
    https://docs.arduino.cc/programming/
# Install Arduino
    sudo apt update
    sudo snap install arduino
# Ultrasonic sensor not working with Bluetooth Hc05 module
#### Electromagnetic Interference (EMI):
 Bluetooth operates in the 2.4 GHz frequency range, which can cause electromagnetic interference with other electronic components. Although ultrasonic sensors typically operate at frequencies around 40 kHz, the electronics controlling them might still be susceptible to EMI, potentially leading to erroneous readings or reduced performance.

#### Processor Load:
Using both Bluetooth and sonar simultaneously can place a significant load on the microcontroller, especially if it is handling other tasks as well. This can lead to timing issues or data loss. Microcontrollers have limited processing power, and managing both Bluetooth communication and sonar measurement can exceed their capacity, leading to performance degradation.

#### Power Consumption:
Both Bluetooth modules and ultrasonic sensors consume power. Running both devices simultaneously might lead to power supply issues, especially if the power source is not adequate, resulting in unstable operation.

# EventBoard - RTC Message Display System

## Description

EventBoard is an embedded system project using LPC2148 that displays scheduled messages on a 16x2 LCD based on real-time clock (RTC). The system allows secure admin access to configure time and select messages using a keypad with password protection. It also shows temperature using an LM35 sensor and indicates system status using LEDs

## Objective

To design a real-time automated message display system that shows predefined messages at specific times and allows user interaction through admin mode

## Features

* RTC-based automatic message display
* Admin mode with password protection
* Keypad interface for user input
* Temperature display using LM35 sensor
* LED indication for active and idle modes
* Scrolling messages on 16x2 LCD
* Displays current time when no message is scheduled

## Hardware Components

* LPC2148 Microcontroller
* 16x2 LCD Display
* Keypad
* LM35 Temperature Sensor
* LEDs
  
## Software Requirements

* Embedded C
* Keil uVision
* Flash Magic
## System Working

The system continuously checks the RTC time.

* If the current time matches a scheduled message, it displays the message on the LCD and turns ON the green LED.
* If no message is scheduled, it displays the current time and temperature, and turns ON the red LED.
* The user can enter Admin Mode using a password through the keypad to modify time and enable/disable messages.
    
## Conclusion

This project demonstrates the use of RTC, embedded C programming, and hardware interfacing to build a real-time automated display system with user interaction and environmental monitoring.

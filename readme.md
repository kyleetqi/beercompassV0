# Beer Compass

A compass that always points you to the nearest beer store using the Arduino framework, developed on Platform IO. This code is written for the debug/development version of the project, which uses breadboarding and breakout boards. A second generation version of this project is also under development that harmonizes the electronics on a custom PCB.

# A Note About Code Organization

This version of the project is being developed using the Arduino framework on an ESP32 chip. In order to provide ease of portability to other chips, code has been organized between hardware interfacing and abstracted code.

This decision was motivated by the fact that the ESP32 consumes over 100 mA, and provides features not necessary for this project such as Bluetooth and Wifi. This version of the project uses the ESP32 because it's super quick and simple to use the Arduino framework to get a prototype going, but the next version requires a more optimized microcontroller. The second version of this project will likely use a low power STM32 chip to provide better battery life since I plan to make this a handheld device.

<ul>
    <li> Hardware interfacing functions are located in HardwareWrapper.h/cpp </li>
    <li> Hardware interfacing code required for the sensors are located in their respective library files. </li>
    <li> utils.h/cpp is used purely for math, logic, and other helper functions and contains no hardware interfacing code. </li>
    <li> main.cpp is completely abstracted and does not contain any hardware interfacing code. </li>
</ul>

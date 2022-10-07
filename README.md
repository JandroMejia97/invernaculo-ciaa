# Hothouse

Hothouse is a project to build a system for monitoring and controlling a greenhouse. It is a work in progress.

In a first stage, with Hothouse, you can:
- Monitor the temperature and humidity inside your greenhouse
- Monitor the light level inside your greenhouse.
- Monitor the humidity of the soil in your greenhouse.
- Send data to a server, and view it in a web interface.

Future stages will include:
- Control the temperature inside your greenhouse.
- Control the humidity inside your greenhouse.
- Control the light level inside your greenhouse.
- Control the humidity of the soil in your greenhouse.

> This firmware uses the [Firmware v3](https://github.com/epernia/firmware_v3) available in the [epernia](https://github.com/epernia/firmware_v3) repository and the sAPI library.

## Hardware
- EDU-CIAA-NXP
- DHT11
- ESP32
- Capacitive Soil Moisture Sensor
- LDR
- 3 RGB LEDs

## Prerequisites
- Dowload the [Embedded IDE](https://github.com/epernia/software)

## Getting Started
To get started with the app, you have to follow these steps:
1. Clone the [repo from github](https://github.com/JandroMejia97/invernaculo-ciaa) with the command
    ```bash
    git clone https://github.com/JandroMejia97/invernaculo-ciaa.git
    ```
2. Go the Embedded IDE.
3. Go to the `Open Project` option.
4. Go to the path where you cloned the repo.
5. Select the `invernaculo-ciaa` folder.
6. Select the Makefile inside the folder
7. Click on the `Open` button.

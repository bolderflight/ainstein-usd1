[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![Bolder Flight Systems Logo](img/logo-words_75.png) &nbsp; &nbsp; ![Arduino Logo](img/arduino_logo_75.png)

# AinsteinUsD1
This library communicates with the [Ainstein US-D1](https://ainstein.ai/drone-makers-drone-service-providers/us-d1/) RADAR altimeter using UART. This library is compatible with Arduino and CMake build systems.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Description
The [Ainstein US-D1](https://ainstein.ai/drone-makers-drone-service-providers/us-d1/) is a low Size, Weight, Power, and Cost (SWaP-C) RADAR altimeter, primarily developed for the UAS or drone market. It can measure altitude above the ground within a range of 0.5m to 50 m with an accuracy of 6cm for altitudes less than 1m or 4cm for altitudes above 1m. The Ainstein US-D1 has an update rate of approximately 100 Hz.

# Installation

## Arduino
Use the Arduino Library Manager to install this library or clone to your Arduino/libraries folder. This library is added as:

```C++
#include "ainstein_usd1.h"
```

Example Arduino executables are located in: *examples/arduino/*. Teensy 3.x, 4.x, and LC devices are used for testing under Arduino and this library should be compatible with other Arduino devices.

## CMake
CMake is used to build this library, which is exported as a library target called *ainstein_usd1*. The header is added as:

```C++
#include "ainstein_usd1.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake .. -DMCU=MK66FX1M0
make
```

This will build the library and an example executable called *usd1_example*. The example executable source file is located at *examples/cmake/usd1_example.cc*. Notice that the *cmake* command includes a define specifying the microcontroller the code is being compiled for. This is required to correctly configure the code, CPU frequency, and compile/linker options. The available MCUs are:
   * MK20DX128
   * MK20DX256
   * MK64FX512
   * MK66FX1M0
   * MKL26Z64
   * IMXRT1062_T40
   * IMXRT1062_T41

These are known to work with the same packages used in Teensy products. Also switching packages is known to work well, as long as it's only a package change.

The example target creates an executable for communicating with the sensor using UART and demonstrates how to initialize communication and read data. Each target also has a *_hex*, for creating the hex file to upload to the microcontroller, and an *_upload* for using the [Teensy CLI Uploader](https://www.pjrc.com/teensy/loader_cli.html) to flash the Teensy. Please note that the CMake build tooling is expected to be run under Linux or WSL, instructions for setting up your build environment can be found in our [build-tools repo](https://github.com/bolderflight/build-tools).

# Namespace
This library is within the namespace *bfs*.

# AinsteinUsD1

## Methods

**AinsteinUsD1()** Default constructor, requires calling the *Config* method to setup the UART bus.

**AinsteinUsD1(HardwareSerial &ast;bus)** Creates the *AinsteinUsD1* object and specifies the UART bus the sensor is on.

```C++
/* Ainstein US-D1 object on UART1 */
bfs::AinsteinUsD1 radalt(&Serial1);
```

**void Config(HardwareSerial &ast;bus)** Used with the default constructor to configure the UART bus the sensor is on.

**bool Begin()** Initializes communication with the Ainstein US-D1 sensor and returns true if communication can be established, otherwise returns false.

```C++
/* Initialize communication */
if (!radalt.Begin()) {
  Serial.println("Unable to communicate with Ainstein US-D1");
  while (1) {}
}
```

**bool Read()** Reads data from the Ainstein US-D1 sensor and stores the data in the *AinsteinUsD1* object. Returns true if new data is available, otherwise returns false.

```C++
/* Check for new data */
if (radalt.Read()) {
  Serial.print(radalt.alt_m());
  Serial.print("\t");
  Serial.print(radalt.snr());
  Serial.print("\n");
}
```

**float alt_m()** Returns the altitude measurement from the last successful *Read*.

**uint8_t snr()** Returns the signal to noise ratio measurement from the last successful *Read*.

# OAEbud Wireless Earbuds Firmware
This README file will guide you through the process of running the firmware for a pair of wireless [OAEbud](https://github.com/uw-x/WirelessHardware) earbuds. The following sections outline the hardware and software dependencies, as well as the steps required to flash the firmware onto the earbuds' circuit board.

# Hardware Dependencies/Requirements
Programming the wireless OAEbud circuit board requires a hardware programmer. The one used for this project was the J-link EDU from Segger.

# Software Dependencies/Requirements

Segger Embedded Studio can be used to write software that is then flashed to the board using the hardware programmer.

# Instructions for Flashing Firmware

#### 1. Install Segger Embedded Studio:
Download and install Segger Embedded Studio from the official website. Make sure to select the appropriate version for your operating system.

#### 2. Clone the OAEbud Firmware Repository:
Clone the OAEbud firmware repository to your local machine using the following command:

```bash
git clone https://github.com/antoniog11/OAEbud-firmware
```

#### 3. Open the Firmware Project:
Launch Segger Embedded Studio and open the OAEbud firmware project. Navigate to File > Open Solution, and then select the .emProject file located in the cloned repository's root directory.

#### 4. Connect the Hardware Programmer:
Connect the J-link EDU (or any compatible programmer) to your computer and the OAEbud circuit board via micro USB.

#### 5. Configure Segger Embedded Studio:
In Segger Embedded Studio, go to Tools > Options > Debug > J-Link. Select the appropriate programmer from the "Adapter" dropdown menu and click "OK" to save the settings.

#### 6. Build the Firmware:
In Segger Embedded Studio, press F7 or click Build > Build Solution to compile the firmware.

#### 7. Flash the Firmware:
After successfully building the firmware, press F5 or click Debug > Start Debugging to flash the firmware onto the OAEbud circuit board. The IDE will automatically connect to the programmer, erase the target device's memory, and program the compiled firmware.

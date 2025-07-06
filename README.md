# Access Control for Turnstile with Arduino and RFID

## 📖 About the Project

This repository documents the development and implementation of a parallel activation system for a turnstile access control mechanism. The project uses the Arduino platform to manage both hardware and embedded software, creating a complete solution for automating the lock and release mechanism of the equipment.

## 🛠️ System Components

**User Identification (RFID Reader):**  
Authentication is performed by an RFID reader that communicates with the microcontroller via the SPI protocol. It validates the access credentials stored on tags or cards to authorize or deny entry.

**Mechanism Activation:**  
Once a valid authorization is granted, the Arduino sends a signal to relay modules. These modules switch the 12VDC power supply to the turnstile's solenoids, which mechanically unlock the rotation mechanism.
![image](https://github.com/user-attachments/assets/9e9fe487-2d3d-4c25-b3e3-9e5f08d3dce2)

**Passage Monitoring (Inductive Sensors and Optocoupler):**  
The NPN inductive sensors (12VDC) are part of the turnstile and detect the rotation of the mechanism. To safely interface with the Arduino's 5VDC digital inputs, an optocoupler module is used to convert and electrically isolate the sensor signals. These sensors are used in the project so that after detecting a rotation following a valid release, the turnstile is automatically locked again.

**Control Logic and Synchronization:**  
The firmware uses the [timer-library](https://github.com/contrem/arduino-timer/tree/master). This approach allows the controller to continuously monitor the sensors in real-time, even during the unlock period, ensuring the turnstile is immediately locked after the user passes through without compromising system responsiveness.

**Visual Interface (LEDs):**  
LEDs in different colors provide instant visual feedback to the user, indicating the system’s operational state:  
- 🔵 Blue: Powered/Ready  
- 🟢 Green: Access Granted  
- 🔴 Red: Access Denied

![image](https://github.com/user-attachments/assets/fc080a35-ba9a-498c-91a7-49fa5ba3347e)


## ⚙️ Hardware Used

- **Arduino Uno:** Development board acting as the project's central processing unit.  
- **RFID Reader Module MFRC522:** RFID module for reading and writing data to cards and tags.
- **5V Relay Module:** Electronic device with two electromechanical switches (relays) that enable the activation of higher-power loads from low-voltage microcontroller signals.
- **PC817 Optocoupler Module:** Component that transfers electrical signals between two electrically isolated circuits.

## 📁 Repository Structure

The project is organized into the following directories:

- **`files/firmware/`**  

- **`files/pictures/`**  

- **`files/schematics/`**  


## 👨‍💻 Author

**Alexandre Rocha de Freitas**  
[alexrfhh](mailto:alexrfhh)

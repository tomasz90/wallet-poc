
## Hardware Ethereum Wallet

This project serves as a proof of concept for a hardware Ethereum wallet, designed to provide secure cryptocurrency transactions. The wallet utilizes an ESP32 microcontroller with a 128x64 OLED screen and communicates with a web interface via Bluetooth. Similar to the Ledger wallet, it enables users to securely sign transactions initiated through a web interface and broadcast them to the Ethereum network.

Project also uses my own library *EthereumHDKeysGenerator* for derivation private keys, public keys and addresses of ethereum accounts based on mnemonic and hd path.

### Directory Structure

- hardware:
  Contains the firmware and code for the ESP32 microcontroller, responsible for handling the cryptographic operations and interfacing with the OLED screen and Bluetooth module.
  It includes all the necessary files to set up the ESP32-based hardware wallet. This includes the firmware code, libraries for the OLED screen and Bluetooth communication, and any additional hardware configuration instructions.
- web: Houses the web interface used by the user to initiate Ethereum transactions. This directory contains the frontend code necessary for transaction initiation and broadcasting signed transaction.

### Features

- Bluetooth Communication: The hardware wallet communicates with the web interface via Bluetooth, ensuring secure and seamless interaction between the user and the device.
- 128x64 OLED Screen: The OLED screen provides a user-friendly display for transaction details, ensuring clarity and transparency in transaction confirmation.
- Secure Transaction Signing: Transactions initiated through the web interface are securely signed by the hardware wallet, safeguarding user funds against unauthorized access.
- Ethereum Network Integration: Signed transactions are broadcasted to the Ethereum network, facilitating the execution of cryptocurrency transfers.

Here is a little demo of sending transaction:

https://github.com/tomasz90/wallet-poc/assets/49351206/078449d4-4c30-4aa3-a859-fa1ef411e6ad


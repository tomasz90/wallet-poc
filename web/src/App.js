import logo from "./logo.svg";
import "./App.css";
import {
  Button,
  Dialog,
  DialogActions,
  DialogContent,
  DialogContentText,
  DialogTitle,
  LinearProgress,
  Link,
  MenuItem,
  Select,
  TextField
} from "@mui/material";
import React, { useState } from "react";
import {
  DECODER,
  encode,
  OPTIONS,
  RECEIVER_UUID,
  SENDER_ADDRESS_UUID,
  SENDER_UUID,
  SERVICE_ADDRESS_UUID,
  SERVICE_UUID,
  toWei,
  Tx
} from "./utils";
import { InfuraProvider, keccak256, toUtf8Bytes } from "ethers";

let device, receiveCharacteristic, sendCharacteristic, sendAddressCharacteristic;
let provider;
let tx = new Tx();

class Network {
  constructor(name, chainId, scanUrl) {
    this.name = name;
    this.chainId = chainId;
    this.scanUrl = scanUrl;
  }
}

const mainnet = new Network("Mainnet", "1", "https://etherscan.io");
const polygon = new Network("Polygon", "137", "https://polygonscan.com");
const goerli = new Network("Goerli", "5", "https://goerli.etherscan.io");
const sepolia = new Network("Sepolia", "11155111", "https://sepolia.etherscan.io");

const networks = [mainnet, polygon, goerli, sepolia];

function App() {
  const [buttonText, setButtonText] = useState("connect");
  const [buttonVariant, setButtonVariant] = useState("contained");
  const [buttonColor, setButtonColor] = useState("none");
  const [inputAddress, setInputAddress] = useState("");
  const [inputValue, setInputValue] = useState("");
  const [selectedOption, setSelectedOption] = useState("placeholder");
  const [openTxDialog, setOpenTxDialog] = React.useState(false);
  const [linkUrl, setLinkUrl] = useState("");
  const [openConfirmSeedDialog, setOpenConfirmSeedDialog] = React.useState(false);

  async function connect() {
    if (!device || !device.gatt.connected) await tryConnect(); else await device.gatt.disconnect();
  }

  async function tryConnect() {
    try {
      // CONNECT DEVICE
      device = await navigator.bluetooth.requestDevice(OPTIONS);
      device.addEventListener("gattserverdisconnected", handleDisconnect);
      console.log("Device: ", device);

      // CONNECT SERVER
      const server = await device.gatt.connect();
      const serviceAddress = await server.getPrimaryService(SERVICE_ADDRESS_UUID);
      const service = await server.getPrimaryService(SERVICE_UUID);

      // CONNECT SEND ADDRESS CHARACTERISTICS
      sendAddressCharacteristic = await serviceAddress.getCharacteristic(SENDER_ADDRESS_UUID);
      sendAddressCharacteristic.addEventListener("characteristicvaluechanged", handleReceiveAddress);
      await sendAddressCharacteristic.startNotifications();

      // CONNECT SEND CHARACTERISTICS
      sendCharacteristic = await service.getCharacteristic(SENDER_UUID);
      sendCharacteristic.addEventListener("characteristicvaluechanged", handleSignedTx);
      await sendCharacteristic.startNotifications();

      // CONNECT RECEIVE CHARACTERISTICS
      receiveCharacteristic = await service.getCharacteristic(RECEIVER_UUID);

      setButtonConnected(true);
    } catch (error) {
      console.log("CANCELED");
      console.log(error);
    }
  }

  const setButtonConnected = (bool) => {
    if (bool) {
      console.log("CONNECTED");
      setButtonText("disconnect");
      setButtonVariant("outlined");
      setButtonColor("white");
    } else {
      setButtonColor("#1976d2");
      setButtonText("connect");
      setButtonVariant("contained");
    }
  };

  const handleReceiveAddress = (event) => {
    const address = DECODER.decode(event.target.value);
    if (address !== "0x") {
      tx.address = address;
      const firstFour = address.substring(0, 4);
      const lastFour = address.substring(address.length - 4, address.length);
      setButtonText("disconnect\n" + firstFour + "..." + lastFour);
      setOpenConfirmSeedDialog(false);
    } else {
      setOpenConfirmSeedDialog(true);
    }
  };

  const handleAddressChanged = (event) => {
    const regex = /^[0-9a-fA-FxX]+$/;
    let text = event.target.value;
    if (text === "" || regex.test(text)) {
      setInputAddress(text);
      if (text.startsWith("0x") && text.length === 42 && !text.slice(2).includes("x")) {
        tx.destinationAddress = event.target.value;
      }
    }
  };

  const handleValueChanged = (event) => {
    [tx.value, tx.valueHex] = toWei(event.target.value);
    setInputValue(event.target.value);
  };

  const handleSendClicked = async () => {
    if (device) {
      if (device.gatt.connected) {
        tx.gasLimit = 21000;
        tx.data = "";
        tx.gasPrice = await getGasPrice();
        tx.nonce = await getNonce();
        if (tx.gasPrice && tx.nonce !== undefined) {
          receiveCharacteristic.writeValue(encode(tx));
          console.log(tx);
        } else {
          console.log("NO GAS PRICE OR NONCE");
        }
      } else {
        console.log("NOT CONNECTED YET");
      }
    } else {
      console.log("NO DEVICE YET");
    }
  };

  const handleSignedTx = async (event) => {
    const txData = DECODER.decode(event.target.value);
    const parsed = JSON.parse(txData);
    console.log(parsed);
    const txHash = await provider.broadcastTransaction(parsed.encoded);
    console.log(txHash);

    // // CLEAR DATA
    // tx = new Tx();
    // setInputAddress("");
    // setInputValue("");
    // setSelectedOption("placeholder");
    const url = networks.find(network => network.chainId === tx.chainId).scanUrl;
    setLinkUrl(`${url}/tx/${txHash.hash}`);
    setOpenTxDialog(true);
  };

  const handleClose = () => {
    setOpenTxDialog(false);
    setOpenConfirmSeedDialog(false);
  };

  const handleDisconnect = () => {
    setButtonConnected(false);
    setOpenConfirmSeedDialog(false);
    console.log("ON DISCONNECTED");
  };

  const MySelectMenu = () => {
    const handleNetworkChange = (event) => {
      setSelectedOption(event.target.value);
      tx.chainId = event.target.value;
      provider = new InfuraProvider(parseInt(tx.chainId));
      console.log(tx);
    };

    return (
      <div>
        <Select value={selectedOption} style={{ backgroundColor: "white", minWidth: "10rem" }}
                onChange={handleNetworkChange}>
          <MenuItem value="placeholder" disabled>Select network</MenuItem>
          <MenuItem value={mainnet.chainId}>{mainnet.name}</MenuItem>
          <MenuItem value={goerli.chainId}>{goerli.name}</MenuItem>
          <MenuItem value={polygon.chainId}>{polygon.name}</MenuItem>
          <MenuItem value={sepolia.chainId}>{sepolia.name}</MenuItem>
        </Select>
      </div>
    );
  };

  const ConfirmSeedDialog = () => {
    const [inputWord, setInputWord] = useState("");

    const handleWordChanged = (event) => {
      setInputWord(event.target.value);
    };

    const handleSendWord = () => {
      const preHashed = toUtf8Bytes(inputWord + RECEIVER_UUID);
      const hashed = keccak256(preHashed);
      const cut = hashed.substring(hashed.length - 16, hashed.length);
      receiveCharacteristic.writeValue(encode(cut));
      setInputWord("");
    };

    const handleEnter = (event) => {
      if (event.keyCode === 13) {
        console.log("ENTER");
        handleSendWord(event);
      }
    };

    return (
      <Dialog
        className="seed-dialog"
        open={openConfirmSeedDialog}
        disableAutoFocus disableEnforceFocus
        aria-labelledby="confirm-seed-dialog"
      >
        <DialogTitle id="confirm-seed-dialog">
          {"Please confirm seed phrase"}
        </DialogTitle>
        <DialogContent className="dialog-word">
          <DialogContentText>Follow the instructions on your device</DialogContentText>
          <div className="input-word-row" style={{ display: "flex", justifyContent: "center" }}>
            <TextField autoFocus className="field seedWord" label="word" variant="filled" value={inputWord}
                       onChange={handleWordChanged} onKeyDown={handleEnter} />
            <div className="spacer" />
            <Button className="send word button" variant="outlined" onClick={handleSendWord}>send</Button>
          </div>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Dismiss</Button>
        </DialogActions>
      </Dialog>
    );
  };

  const TxDialog = () => {
    return (
      <Dialog
        open={openTxDialog}
        aria-labelledby="sending-tx-dialog"
      >
        <DialogTitle id="sending-tx-dialog">
          {"Sending transaction..."}
        </DialogTitle>
        <DialogContent className="dialog-tx">
          <LinearProgress className="link" />
          <Button component={Link} href={linkUrl} target="_blank" variant="body2">
            {linkUrl}
          </Button>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Ok</Button>
        </DialogActions>
      </Dialog>
    );
  };

  return (
    <div className="App">
      <header className="App-header">
        <div className="connect-row">
          <Button style={{ backgroundColor: buttonColor }} className="connect-button"
                  variant={buttonVariant} onClick={connect}>{buttonText}</Button>
        </div>
        <img src={logo} className="App-logo" alt="logo" />
        <div className="input-row">
          <MySelectMenu />
          <div className="spacer" />
          <TextField className="field to" label="to" variant="filled" value={inputAddress}
                     onChange={handleAddressChanged} />
          <div className="spacer" />
          <TextField type="number" className="field value" label="value" variant="filled" value={inputValue}
                     onChange={handleValueChanged} />
          <div className="spacer" />
          <Button className="send button" variant="outlined" onClick={handleSendClicked}>send</Button>
        </div>
        <ConfirmSeedDialog />
        <TxDialog />
      </header>
    </div>
  );
}

export default App;

async function getGasPrice() {
  try {
    let originalGasPrice = (await provider.getFeeData()).gasPrice;
    console.log("Original gas price: " + originalGasPrice);
    let gasPrice = originalGasPrice * BigInt(10) / BigInt(8);
    gasPrice = gasPrice.toString();
    console.log("GasPrice is: " + gasPrice);
    return gasPrice;
  } catch (error) {
    console.error("Error retrieving gas price:", error);
  }
}

async function getNonce() {
  try {
    const nonce = await provider.getTransactionCount(tx.address);
    console.log("Nonce is: " + nonce);
    return nonce;
  } catch (error) {
    console.error("Error retrieving nonce:", error);
  }
}

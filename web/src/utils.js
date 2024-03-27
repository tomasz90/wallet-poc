import BigNumber from "bignumber.js";

export const SERVICE_ADDRESS_UUID = "`b39418c1-5b51-4828-a8a0-7ee0eef01dba`";
export const SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
export const SENDER_ADDRESS_UUID = "6a079629-af17-4a50-bda7-80d55196dd27";
export const SENDER_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
export const RECEIVER_UUID = "03d2fde6-1615-461d-897b-6b0220bdd335";
export const OPTIONS
  = { filters: [{ namePrefix: "ESP32" }], optionalServices: [SERVICE_ADDRESS_UUID, SERVICE_UUID] };
export const ENCODER = new TextEncoder();
export const DECODER = new TextDecoder();

export function encode(obj) {
  return ENCODER.encode(JSON.stringify(obj));
}

export function toWei(value) {
  const ether = BigNumber(10).pow(18);
  const wei = BigNumber(value).times(ether);
  return [wei.toString(), wei.toString(16)];
}

export function Tx(nonce, chainId, gasPrice, gasLimit, address, destinationAddress, value, valueHex, data) {
  this.nonce = nonce;
  this.chainId = chainId;
  this.gasPrice = gasPrice;
  this.gasLimit = gasLimit;
  this.address = address;
  this.destinationAddress = destinationAddress;
  this.value = value;
  this.valueHex = valueHex;
  this.data = data;
}

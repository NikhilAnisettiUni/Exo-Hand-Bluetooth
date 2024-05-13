/*********************************************************************
This is the code for the CLIENT

CLIENT is the code that reads/writes variables to be read by the SERVER

In this case the Client is the hub.

Variables Currently defined are:

L5,L4,L3,L2,L1

SERVICE
packet = ("e3d0f10f-80c8-4e4a-b7e7-68caf7d449c0");

CHARACTERISITCS
L1 = ("04fdb0b8-8cf3-4236-9394-bc0887fac118");
L2 = ("36abbae0-525e-4ae3-b4f5-2b9f35ba678f");
L3 = ("641df76a-4161-42e7-b0cc-9f08e9473b7a");
L4 = ("19b0b4ec-f682-4006-af73-c31b1e5f045d");
L5 = ("30e746e6-774d-4957-bc0e-ec09e8b9aced");


READ VALUE IN HEX. 

DO NOT ACCESS ANY OTHER DESCRPITORS!
*********************************************************************/

#include <ArduinoBLE.h>
String uuid = "e3d0f10f-80c8-4e4a-b7e7-68caf7d449c0";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }
  Serial.println("Bluetooth® Low Energy Central - Peripheral Explorer");
  BLE.scan();
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    if (peripheral.localName() == "XIAO ") {
      BLE.stopScan();
      explorerPeripheral(peripheral);
    }
  }
}

void explorerPeripheral(BLEDevice peripheral) {
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }

  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

  for (int i = 0; i < peripheral.serviceCount(); i++) {
    BLEService service = peripheral.service(i);
    
    if (uuid == service.uuid()){
      exploreService(service);
    }
    else{
      Serial.println(" Expected service cannot be found");
    }
  }

  Serial.println();
}

void exploreService(BLEService service) {
  while (true){
  for (int i = 0; i < service.characteristicCount(); i++) {
    BLECharacteristic characteristic = service.characteristic(i);

    exploreCharacteristic(characteristic);
    
  }
  delay(3000);
  Serial.println("******************");
  }
  

}
void printData(const unsigned char data[], int length) {
  for (int i = 0; i < length; i++) {
    unsigned char b = data[i];
    if (b < 16) {
      Serial.print("0");
    }
    Serial.print(b, HEX);
  }
}
void exploreCharacteristic(BLECharacteristic characteristic) {
  if (characteristic.canRead()) {
    characteristic.read();

    if (characteristic.valueLength() > 0) {
      Serial.print("value : 0x");
      printData(characteristic.value(), characteristic.valueLength()); 
      Serial.println();
      Serial.println(characteristic.uuid());
    }
  }
  Serial.println();
  }




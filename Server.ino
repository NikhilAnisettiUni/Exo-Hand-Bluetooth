/*********************************************************************
This is the code for the SERVER

SERVER is the code that exposes variables to be read by the CLIENT

In this case the server is on the ExoHand.

Variables Currently defined are:

L5,L4,L3,L2,L1

When more is added used UUID 128bit generator.
*********************************************************************/
#include <bluefruit.h>

BLEService packet = BLEService("e3d0f10f-80c8-4e4a-b7e7-68caf7d449c0");
BLECharacteristic L1 = BLECharacteristic("04fdb0b8-8cf3-4236-9394-bc0887fac118");
BLECharacteristic L2 = BLECharacteristic("36abbae0-525e-4ae3-b4f5-2b9f35ba678f");
BLECharacteristic L3 = BLECharacteristic("641df76a-4161-42e7-b0cc-9f08e9473b7a");
BLECharacteristic L4 = BLECharacteristic("19b0b4ec-f682-4006-af73-c31b1e5f045d");
BLECharacteristic L5 = BLECharacteristic("30e746e6-774d-4957-bc0e-ec09e8b9aced");

BLEDis bledis;    // DIS (Device Information Service) helper class instance
BLEBas blebas;    // BAS (Battery Service) helper class instance
int test_data = 1;

uint8_t  bps = 0;

void setup()
{
  Serial.begin(115200);

  Serial.println("Initialise the Bluefruit nRF52 module");
  Bluefruit.begin();

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  Serial.println("Configuring the Device Information Service");
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather52");
  bledis.begin();

  //***TURN ON WHEN BATTERY IS BEING USED ON HAND***
  // Serial.println("Configuring the Battery Service");
  // blebas.begin();
  // blebas.write(100);

  Serial.println("Setting up packet...");
  setupPacket();

  Serial.println("Setting up the advertising payload(s)");
  startAdvertising();

  Serial.println("Finished");
}

void startAdvertising(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  Bluefruit.Advertising.addService(packet);
  Bluefruit.Advertising.addName();
  
  //Start Advertising 
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);  
  Bluefruit.Advertising.setFastTimeout(30);    
  Bluefruit.Advertising.start(0);              
}

void setupPacket(void)
{
  packet.begin();


  L1.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  L1.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  L1.begin();
  L1.write8(0X64);

  L2.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  L2.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  L2.begin();
  L2.write8(0X64);

  L3.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  L3.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  L3.begin();
  L3.write8(0X64);

  L4.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  L4.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  L4.begin();
  L4.write8(0X64);

  L5.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  L5.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  L5.begin();
  L5.write8(0X64);
}

void connect_callback(uint16_t conn_handle)
{
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char central_name[32] = { 0 };
  connection->getPeerName(central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
  Serial.println("Advertising!");
}


void loop()
{
  digitalToggle(LED_RED);
  if ( Bluefruit.connected() ) {
    //Put promise here to retrieve data from websocket.
    if (test_data){
      test_data = 0;
    }
    else{
      test_data=1;
    }
    L1.begin();
    L1.write8(test_data);

    L2.begin();
    L2.write8(test_data);

    L3.begin();
    L3.write8(test_data);

    L4.begin();
    L4.write8(test_data);

    L5.begin();
    L5.write8(test_data);
  delay(1000);
}
}

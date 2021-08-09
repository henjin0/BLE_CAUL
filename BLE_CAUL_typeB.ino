#include <M5StickCPlus.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define TYPE_B_ARRAYSIZE 11

const uint16_t kIrLed = 9; 
IRsend irsend(kIrLed);
uint16_t rawUpData[TYPE_B_ARRAYSIZE] = {5302, 722,  1282, 720,  616, 720,  612, 724,  612, 718,  1284};
uint16_t rawDOWNData[TYPE_B_ARRAYSIZE] = {5324, 704,  1302, 704,  628, 706,  630, 704,  1300, 704,  628};
uint16_t rawLEFTData[TYPE_B_ARRAYSIZE] = {5306, 720,  1306, 700,  612, 724,  1280, 722,  612, 724,  630};
uint16_t rawRIGHTData[TYPE_B_ARRAYSIZE] = {5324, 700,  1302, 702,  1302, 702,  630, 700,  634, 702,  630};
uint16_t rawUPLEFTData[TYPE_B_ARRAYSIZE] = {5320, 706,  1298, 704,  630, 704,  1300, 702,  632, 706,  1298};
uint16_t rawUPRIGHTData[TYPE_B_ARRAYSIZE] = {5324, 702,  1302, 702,  1302, 700,  632, 704,  630, 702,  1302};
uint16_t rawDOWNLEFTData[TYPE_B_ARRAYSIZE] = {5320, 704,  1298, 704,  632, 706,  1298, 706,  1298, 704,  628};
uint16_t rawDOWNRIGHTData[TYPE_B_ARRAYSIZE] = {5322, 706,  1298, 704,  1300, 704,  632, 706,  1298, 704,  630};

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

std::string command="none";

class MyCallbacks: public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic *pCharacteristic) {
    pCharacteristic->setValue("Hello World!");
    Serial.println("onRead");
  }

  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if(!value.empty()){
      command=value;
    }
    Serial.println(value.c_str());
    Serial.println("onWrite");
  }
};

void setup() {
  M5.begin();
  Serial.println("Starting BLE work!");

  irsend.begin();

  BLEDevice::init("m5stickcplus");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
   M5.update();
    if(command=="UP"){
      irsend.sendRaw(rawUpData, TYPE_B_ARRAYSIZE, 38);
    }if(command=="DOWN"){
      irsend.sendRaw(rawDOWNData, TYPE_B_ARRAYSIZE, 38);
    }else if(command=="RIGHT"){
       irsend.sendRaw(rawRIGHTData, TYPE_B_ARRAYSIZE, 38);
    }else if(command=="LEFT"){
       irsend.sendRaw(rawLEFTData, TYPE_B_ARRAYSIZE, 38);
    }else if(command=="UPLEFT"){
       irsend.sendRaw(rawUPLEFTData, TYPE_B_ARRAYSIZE, 38);
    }else if(command=="DOWNLEFT"){
       irsend.sendRaw(rawDOWNLEFTData, TYPE_B_ARRAYSIZE, 38);
    }else if(command=="UPRIGHT"){
       irsend.sendRaw(rawUPRIGHTData, TYPE_B_ARRAYSIZE, 38);
    }else if(command=="DOWNRIGHT"){
       irsend.sendRaw(rawDOWNRIGHTData, TYPE_B_ARRAYSIZE, 38);
    }else{
      Serial.println(command.c_str());
    }
    delay(1);
}

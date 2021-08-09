/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/
#include <M5StickCPlus.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

const uint16_t kIrLed = 9; 
IRsend irsend(kIrLed);
uint16_t rawUpData[23] = {5134, 688,  614, 664,  614, 666,  590, 688,  614, 666,  1230, 17436,  5086, 688,  612, 666,  590, 688,  590, 688,  590, 688,  1234};
uint16_t rawDOWNData[23] = {5074, 692,  582, 696,  582, 692,  586, 690,  1224, 694,  582, 17420,  5076, 696,  582, 692,  586, 694,  580, 694,  1226, 692,  582};
uint16_t rawLEFTData[23] = {5078, 690,  582, 694,  582, 692,  1226, 692,  584, 692,  584, 17416,  5074, 690,  586, 692,  584, 692,  1224, 692,  584, 694,  584};
uint16_t rawRIGHTData[23] = {5076, 690,  582, 694,  1226, 690,  584, 694,  582, 694,  584, 17418,  5072, 692,  582, 692,  1226, 692,  584, 694,  582, 692,  586};
uint16_t rawUPLEFTData[23] = {5116, 666,  590, 690,  590, 692,  1232, 688,  614, 668,  1232, 17454,  5094, 688,  590, 688,  592, 690,  1234, 688,  590, 688,  1236};  // UNKNOWN 7F07A6DB
uint16_t rawUPRIGHTData[23] = {5092, 690,  588, 690,  1232, 690,  588, 686,  594, 690,  1232, 17442,  5094, 690,  588, 688,  1234, 688,  590, 690,  590, 688,  1234};  // UNKNOWN 8D0808C3
uint16_t rawDOWNLEFTData[23] = {5094, 686,  594, 686,  594, 686,  1236, 686,  1236, 686,  592, 17450,  5094, 686,  592, 686,  594, 688,  1236, 688,  1236, 686,  594};  // UNKNOWN A6B43767
uint16_t rawDOWNRIGHTData[23] = {5114, 670,  606, 672,  1252, 672,  608, 672,  1252, 674,  606, 17440,  5106, 670,  608, 672,  1252, 672,  608, 672,  1250, 670,  612};  // UNKNOWN E6560397






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
      irsend.sendRaw(rawUpData, 23, 38);
    }if(command=="DOWN"){
      irsend.sendRaw(rawDOWNData, 23, 38);
    }else if(command=="RIGHT"){
       irsend.sendRaw(rawRIGHTData, 23, 38);
    }else if(command=="LEFT"){
       irsend.sendRaw(rawLEFTData, 23, 38);
    }else if(command=="UPLEFT"){
       irsend.sendRaw(rawUPLEFTData, 23, 38);
    }else if(command=="DOWNLEFT"){
       irsend.sendRaw(rawDOWNLEFTData, 23, 38);
    }else if(command=="UPRIGHT"){
       irsend.sendRaw(rawUPRIGHTData, 23, 38);
    }else if(command=="DOWNRIGHT"){
       irsend.sendRaw(rawDOWNRIGHTData, 23, 38);
    }else{
      Serial.println(command.c_str());
    }
    delay(1);
}
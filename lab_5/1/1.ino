#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "bbb5483e-36e1-4688-b7f5-ea07361b26a8"


BLEService 		  *SERVICE;
BLECharacteristic *LUMINOSITY_CHARACTERISTIC;


void SetupBLE();
void SetLuminosityCharacteristicOnBleDevice(const int luminosity);

void setup()
{
	Serial.begin(115200);
	while(not Serial)
	{
		delay(100);
	}

	SetupBLE();
	Serial.println("Characteristic defined!");
}

void loop()
{
	int luminosity = analogRead(36);
	SetLuminosityCharacteristicOnBleDevice(luminosity);
	delay(500);
}

void SetupBLE()
{
	BLEDevice::init("Esp32 test BLE");
	BLEServer *pServer = BLEDevice::createServer();
	SERVICE = pServer->createService(SERVICE_UUID);
	LUMINOSITY_CHARACTERISTIC = SERVICE->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
	LUMINOSITY_CHARACTERISTIC->setValue("0");
	SERVICE->start();
	BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
	pAdvertising->start();
}

void SetLuminosityCharacteristicOnBleDevice(const int luminosity)
{
	LUMINOSITY_CHARACTERISTIC->setValue(std::to_string(luminosity));
}

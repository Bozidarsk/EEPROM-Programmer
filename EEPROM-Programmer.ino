#include <stdint.h>

#define ADDRESS_START 11
#define ADDRESS_END 19
#define IO_START 3
#define IO_END 10
#define WE 2

uint8_t DATA[] = { 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 };

uint16_t GetMaxAddress() 
{
	uint16_t output = 1;
	for (uint16_t i = 0; i <= ADDRESS_END - ADDRESS_START; i++) { output *= 2; }
	return output;
}

void SetPins(const uint16_t data, const uint8_t start, const uint8_t end) 
{
	for (uint8_t i = start; i <= end; i++) 
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, ((data >> (i - start)) & 0x1 == 0x1) ? HIGH : LOW);
	}
}

uint16_t GetPins(const uint8_t start, const uint8_t end) 
{
	uint16_t data = 0x0000;
	for (uint8_t i = start; i <= end; i++) 
	{
		pinMode(i, INPUT);
		data += ((digitalRead(i) == HIGH) ? 1 : 0) << (i - start);
	}

	return data;
}

void Write(const uint8_t* data, const uint32_t length, const uint16_t offset) 
{
	for (uint32_t i = 0; i < length; i++) 
	{
		SetPins(i + offset, ADDRESS_START, ADDRESS_END);
		SetPins(data[i], IO_START, IO_END);

		digitalWrite(WE, LOW);
		delayMicroseconds(1);
		digitalWrite(WE, HIGH);
		delay(5);
	}
}

void Read() { Read(GetMaxAddress()); }
void Read(uint16_t maxAddress) 
{
	for (uint16_t address = 0x0000; address < maxAddress; address++) 
	{
		SetPins(address, ADDRESS_START, ADDRESS_END);
		Serial.println(GetPins(IO_START, IO_END));
	}
}

void setup() 
{
	digitalWrite(WE, HIGH);
	pinMode(WE, OUTPUT);
	Serial.begin(57600);

	// Write(DATA, sizeof(DATA), 0x0000);
	delay(10000);
	Read(6);
}

void loop() {}
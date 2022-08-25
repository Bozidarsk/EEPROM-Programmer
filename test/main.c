#include <stdio.h>
#include <stdint.h>

#define HIGH "HIGH\x00"
#define LOW "LOW\x00"
#define ADDRESS_START 11
#define ADDRESS_END 19
#define IO_START 3
#define IO_END 10
#define WE 2

void SetPins(const uint16_t data, const uint8_t start, const uint8_t end) 
{
	for (uint8_t i = start; i <= end; i++) 
	{
		printf("%i: %s\n", i, ((data >> (i - start)) & 0x1 == 0x1) ? HIGH : LOW);
	}
}

void Write(const uint8_t* data, const uint32_t length, const uint16_t offset) 
{
	for (uint32_t i = 0; i < length; i++) 
	{
		SetPins(i + offset, ADDRESS_START, ADDRESS_END);
		SetPins(data[i], IO_START, IO_END);

		// digitalWrite(WE, HIGH);
		// delayMicroSeconds(1);
		// digitalWrite(WE, LOW);
	}
}
int main() 
{
	uint8_t test[] = { 0xaa, 0x55, 0xaa, 0x55 };

	Write(test, sizeof(test) / sizeof(test[0]), 0x0000);
}
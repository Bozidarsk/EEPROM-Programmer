#define pinsAddress 0 // ports 0 to 12
#define pinsIO 13 // ports 13 to 20
#define pinWE 21 // EEPROM write enable pin
#define pinOE 22 // EEPROM output enable pin

#define emptyByte 0b11111111

/*
IO 0 to 7 = 0b00000000, the rightmost bit is IO0 and the leftmost bit is IO7, same for the address
*/

void SetPinsFromByte(int pinsStart, int pinsCount, byte value) 
{
	int i = 0;
        byte result = 0b0;
	
        for (int p = pinsStart; p <= pinsStart + pinsCount; p++)
        {
                result = (value & (1 << i)) >> i;
                digitalWrite(p, (result == 0b1) ? HIGH : LOW);
                i++;
        }
}

void Write(byte bytes[]) 
{
	for (int i = pinsIO; i <= pinsIO + 7; i++)
        {
                pinMode(i, OUTPUT);
        }

	for (int address = 0; address < sizeof(bytes); address++) 
	{
		digitalWrite(pinOE, HIGH);

        	SetPinsFromByte(pinsAddress, 12, byte(address));
        	SetPinsFromByte(pinsIO, 7, bytes[address]);

        	digitalWrite(pinWE, LOW);
        	delayMicroseconds(1);
        	digitalWrite(pinWE, HIGH);

        	digitalWrite(pinOE, LOW);
	}
}

void setup() 
{
	delay(15000);

	for (int i = pinsAddress; i <= pinsAddress + 12; i++) 
	{
		pinMode(i, OUTPUT);
	}

	pinMode(pinWE, OUTPUT);
	digitalWrite(pinWE, HIGH);
	pinMode(pinOE, OUTPUT);
	digitalWrite(pinOE, LOW);

	byte bytes[5] = { 0b11111101, 0b00000001, 0b00001001, 0b10100101, 0b11001100 };
	Write(bytes);
}

void loop() 
{
}

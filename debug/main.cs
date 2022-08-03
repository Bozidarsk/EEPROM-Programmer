using System;
using System.Collections;
using System.Collections.Generic;

class Pin 
{
    private int PIN;
    private bool STATE;

    public int pin 
    {
        set { PIN = value; }
        get { return PIN; }
    }

    public bool state 
    {
        set { STATE = value; }
        get { return STATE; }
    }

    public Pin(int _PIN, bool _STATE) 
    {
        PIN = _PIN;
        STATE = _STATE;
    }
}

class main 
{
    static bool HIGH = true;
    static bool LOW = false;

    static void digitalWrite(int pin, bool state) { Console.WriteLine(System.Convert.ToString(pin) + " is " + ((state) ? "HIGH" : "LOW")); }

    static void SetPinsFromByte(int pinsStart, int pinsCount, byte value)
    {
        int i = 0;
        int result = 0; // 'int' for .cs, 'byte' for .ino

        for (int p = pinsStart; p <= pinsStart + pinsCount; p++)
        {
            result = (value & (1 << i)) >> i;
            digitalWrite(p, (result == 1) ? HIGH : LOW);
            i++;
        }
    }

    static void Main() 
    {
        SetPinsFromByte(13, 7, 35);
    }
}
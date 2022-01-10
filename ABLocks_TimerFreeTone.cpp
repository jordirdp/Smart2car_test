// ---------------------------------------------------------------------------
// Created by Tim Eckel - teckel@leethost.com
// Copyright 2016 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
//
// See "TimerFreeTone.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "ABLocks_TimerFreeTone.h"

uint8_t _tft_volume[] = { 255, 200, 150, 125, 100, 87, 50, 33, 22, 2 }; // Duty for linear volume control.

#define OCTAVE_OFFSET 0

int RTTTL_NOTES_FREQ[] = { 
	0,262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
  523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
  1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
  2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
};

void TimerFreeTone(uint8_t pin, unsigned long frequency, unsigned int duration, uint8_t volume) {
	if (frequency == 0 || volume == 0) { // If frequency or volume are zero, just wait duration and exit.
		delay(duration);
		return;
	} 

	frequency = 1000000 / frequency;                        // Calculate the square wave length (in microseconds).
	uint32_t duty = frequency / _tft_volume[volume - 1];    // Calculate the duty cycle (volume).
#ifdef __AVR__
	uint8_t pinBit = digitalPinToBitMask(pin);                                  // Get the bitmask for the pin.
	volatile uint8_t *pinOutput = (uint8_t *) portOutputRegister(digitalPinToPort(pin)); // Get the port register for the pin.
	volatile uint8_t *portMode = (uint8_t *) portModeRegister(digitalPinToPort(pin));    // Get the port mode register for the pin.
	*portMode |= pinBit;                                                        // Set pin to output mode.
#else
	pinMode(pin, OUTPUT);                                                       // Set pin to output mode.
#endif
  
	uint32_t startTime = millis();           // Starting time of note.
	while(millis() - startTime < duration) { // Loop for the duration.

    yield();

	#ifdef __AVR__
		*pinOutput |= pinBit;    // Set pin high.
		delayMicroseconds(duty); // Square wave duration (how long to leave pin high).
		*pinOutput &= ~pinBit;   // Set pin low.
	#else
		digitalWrite(pin,HIGH);  // Set pin high.
		delayMicroseconds(duty); // Square wave duration (how long to leave pin high).
		digitalWrite(pin,LOW);   // Set pin low.
	#endif

		delayMicroseconds(frequency - duty); // Square wave duration (how long to leave pin low).
	}
}

void TimerFreeToneRtttl(uint8_t _pin, const char* p, uint8_t volume)
{
  // Absolutely no error checking in here
  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

  // get default octave
  if(*p == 'o')
  {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  // get BPM
  if(*p == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  // now begin note loop
  while(*p)
  {
    yield();
    
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.')
    {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note
    if(note)
    {
	    TimerFreeTone(_pin,(unsigned long)RTTTL_NOTES_FREQ[(scale - 4) * 12 + note],(unsigned int)duration, volume);
    }
    else
    {
      delay(duration);
    }
  }
}
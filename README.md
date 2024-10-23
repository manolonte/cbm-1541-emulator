# cbm-1541-emulator
Work in progress.

The idea is using an Arduino board to translate IEC bus communications to RS-232 serial data for a Raspberry PI to serve files to a CBM64.
Just for fun.

## Documentation
https://en.wikipedia.org/wiki/Commodore_bus
https://es.wikipedia.org/wiki/Bus_IEC_(Commodore)
https://www.c64-wiki.com/wiki/Serial_Port
https://handwiki.org/wiki/Commodore_bus

Books: 
- The anatomy of the 1541 Disk Drive - Abacus Software
- 64 Interno - Angerhausen/Brückmann/Englisch/Gerits - https://www.c64-wiki.de/wiki/64_intern

## Similar projects
https://www.gotek-retro.eu/c64-pi1541-zero/
https://github.com/Larswad/uno2iec

## Why another project for emulating a 1541
Mainly for fun and learning, but also I want to solve a potential problem in some of the existing projects. 
![image](https://github.com/user-attachments/assets/f7809e8d-5d22-4d3e-ad4d-c84580bcdee0)

Some of the pins of the IEC bus are in/out. But you cannot set up pins in Arduino board or Raspberry to be in and out simultaneously. Your code can change the sense of transfer according to the protocol, but that can be dangerous, because if something gets out of sync between the sender of data and the receiver and they set two connected pins as OUT with high level on one side and low level on the other, some mosfet in some chip can get burned.

So I want to protect pins in Arduino with the following strategy (still to be tested with a real CBM64):
```
		              +------------- IN     
CBM64		i/o --^v^v^v--|			    Arduino
		      R=20Ohm +-----|<|----- OUT
		                  Shottky
```
For every in/out pin in CBM64 (only CLK and DATA should be treated this way), we need one in pin and one out pin at Arduino side. The resistor protects from excesive current if something goes wrong, and the Shottky diode prevents current to go to the OUT pin of Arduino.

## Pinout
|     |     |     |     |     |
| --- | --- | --- | --- | --- |
| IEC port | meaning | RPi Port | Arduino in | Arduino out |
| 1   | SRQIN | 3   | \--- | \--- |
| 2   | GND | 9   | GND |     |
| 3   | ATN | 5   | PD6 |     |
| 4   | CLK | 7   | PD4 | PD5 |
| 5   | DATA | 11  | PD2 | PD3 |
| 6   | RESET | \--- | \--- | \--- |


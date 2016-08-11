# keithley-617-arduino
An Arduino program for communicating with the Keithley 617 Programmable Electrometer over IEEE-488 / GPIB

DISCLAIMER: This tutorial is provided AS-IS. I am not responsible if you destroy your electrometer. I am not an expert with the IEEE-488 protocol and do not guarantee that my implementation is 100% correct. This tutorial assumes that you know what you’re doing and does not go into the details. That being said, this worked fine for me (after I realized that I originally misidentified a pin) and would be surprised if it didn’t work for you.

## Put the electrometer in mode 41
1) Press the `Program Select` button so the following message is displayed: `IEEE 27`.

2) Press the up arrow `V-SOURCE ADJUST` repeatedly until parameter 41 is shown.

3) To exit the program, press `SHIFT` then `SELECT EXIT`. The unit is now programmed in talk-only mode and will remain in this mode until turned off.

## Choose output rate
1) Press and hold the `DATA STORE ON/OFF` button until the desired rate is displayed, as indicated below:
```
r=0 Conversion rate (every 360ms)
r=1 Every second
r=2 Every 10 seconds
r=3 Every 1 minute
r=4 Every 10 minutes
r=5 Every hour
r=6 Every time TRIG is pressed
```

2) Press the `PROGRAM SELECT` button until the IEEE program message is displayed. Release the button.

3) Press `SELECT EXIT` to resume to normal operation.
 
## Wire the arduino
1) Wire up the arduino by stripping an IEEE-488 cable and hooking up the wires to the arduino according to the following. You can find the cable pinout on Wikipedia.
```
#define EOI  A5    // 05  End-or-Identify
#define DAV  A4    // 06  Data Valid
#define NRFD A3    // 07  Not ready for data
#define NDAC 12    // 08  Not data accepted
#define IFC  11    // 09  Interface clear
#define SRQ  A2    // 10  Service request
#define ATN  A1     // 11  Attention
#define REN  10     // 17  Remote enable

#define DIO1 2     // 01  Data IO 1 LSB
#define DIO2 3     // 02  Data IO 2
#define DIO3 4     // 03  Data IO 3
#define DIO4 5     // 04  Data IO 4
#define DIO5 6     // 13  Data IO 5
#define DIO6 7     // 14  Data IO 6
#define DIO7 8     // 15  Data IO 7
#define DIO8 9     // 16  Data IO 8 MSB
```
2) Run the program on the arduino and hook it up to a computer with a serial terminal at 9600 baud. 

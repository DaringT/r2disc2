# Serial Driver for Amtren / Discmakers CD/DVD autoloading Robots

Tested OS's: Windows 7, Windows 10, Debian, Ubuntu

There is a [Python-Linux](https://github.com/DaringT/r2disc2/blob/master/src/serial_drive.py), [C-Linux](https://github.com/DaringT/r2disc2/blob/master/src/serial_drive.c) and [C-Win](https://github.com/DaringT/r2disc2/blob/master/src/win_serial.c) version 


```
Basics:
  DB-9 M to DB9 F straight through (no null-modem cable)
  Com port setup - 9600 (38400 for some) baud, 8N1, No flow control.
 
Response Codes:
  Success - X
  Failure - E
 
Core Commands:
  V - Signup or version (sometimes required as first command)
  C - Reset or Calibrate unit
  I - Input disc from bin to drive
  A - Accept disc from drive to output bin
  G - Get disc from drive and hold in picker (required before R and sometimes A)
  R - Move disc from picker to Reject bin
  S - Status of mechanism
Trial and Error:
  B - 'G'rab from Printer
  H - If 'G'rabbing, put in CD Tray
  P - Same as G
  K - Input stack -> Printer, 
      If currently 'G'rabbing, 
      it will move that to the input queue, 
      drop it, and then move it to the printer.
  D - Down
  U - Up
  L - Load Printer
  M - Drop 
  N - Get from Printer
  Q - Accept from Printer
  T - Test (input->cd_tray, cd_tray->accept_bin)
  W - some type of 3 number status

Status Codes:
  00 - OK
  14 - Top Sensor Error 
  15 - Float Sensor Error
  16 - CD Sensor Error 
  18 - Up Encoder Timeout
  19 - Down Encoder Timeout
  21 - Drive Tray Empty
  22 - Could not get disc from input bin (empty?)
  23 - Printer Empty
  65 -- ?? From running 'T' on the flexwriter

Examples of non-standard Commands:
On the Kodak unit, when you have five or less discs, command "I" for Input/Insert always returns E for failure (presumably to alert the kiosk operator that the device is running low) - you'll need to code around that if you want to be able to use the entire input capacity.
 
  ctrl-C - Cancel operation
  j - Shake-based Insert
  F - Reset flags (aka set input bin #1 as the staring bin)
  P - Pick (before I/? in multiple drive bank systems)
  H - Get from bank 2 in multiple drive bank systems
  B - Accept from bank 2 in multiple drive bank systems
```

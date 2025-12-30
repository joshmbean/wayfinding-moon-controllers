# Summary
This specification describes the command set used for communication between the Main Controller and the Sub-controllers 
via the I2C comms bus.

# Command Direction
Commands are always sent from the Main Controller to a Sub-controller.

# Command Format
Commands are made up of one or more I2C frames dependent on the command.
The first frame always contains the command ID

## Command List by ID
This section lists available Sub-controller commands by hexidecimal command ID
0x00 - Status
0x01 - Reset
0x02 - Blink
0x0F - Update Firmware
0x10 - Set Mode Base
0x11 - Set Mode Music
0x12 - Set Mode Simon
0x13 - Set Mode Calibration
0x14 - Set Mode Moth
0x15 - Set Mode Colour
0x16 - Set Mode Standby
0x17 - Set Mode Flash
0x20 - Configure Long Term Average Samples
0x21 - Configure Short Term Average Samples
0x22 - Configure Brightness
0x23 - Configure Retrigger Time
0x24 - Configure Sample Time
0x25 - Configure Press Threshold
0x26 - Configure Release Threshold
0x27 - Configure Max Threshold
0x28 - Configure Colour Hue Start
0x29 - Configure Colour Hue End
// todo add command range for picking what type of data is returned when a request is sent

# Mode Descriptions

## Base

## Music

## Simon

## Start Calibration
SubController begins recording min and max pressure values per sensor. LED colour in this mode is determined by the pressure reading of the sensor the LED is mounted too. A transition to Test Mode saves this data to flash. A transition to any other mode discards this data. Colours in this mode use colour to represent raw pressure values.

## Test Mode
If a threshold is out of range it will flash red. If it is within a threshold then leds will remain in independent control but will use their new calibrated map

## Moth

## Colour

## Standby

## Flash

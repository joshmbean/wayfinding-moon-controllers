# Summary
The MoonController is the primary brain of the Wayfinding installation. It is responsible for sending commands 
to sub-controllers and receive data from them.

# Mode Control
The MoonController handles to seperate methods of controlling the Moon Mode. User Mode, in which the mode is set by special mode controller pentagon cell, and Override Mode, in which the Moon mode is controller by the Website Override buttons.

## User Mode

## Override Mode
Enabling the Override Mode switch on the Moon Website enables this function. Once enabled the MoonController will send an SET_MODE command to the SubControllers according to which mode button is selected. 
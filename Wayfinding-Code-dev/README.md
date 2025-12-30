This is the code for the Wayfinding Project!

Software Required to Program for Wayfinding
- VS Code
- PlatformIO (VS Code Extension)
- Git

Development Enviroment:
There are three projects in Wayfinding
1. MainController (ESP32)
2. SubController  (STM32)
3. MothController (ESP32)

All three projects use the Arduino Core + their respective compatbility layers (e.g. STM32Duino, ESP32). The projects are
cofigured to use the PlatformIO extension which (barring some setup issues) "should" auto-magically install all depdencies
require to compile and upload to the Controllers.


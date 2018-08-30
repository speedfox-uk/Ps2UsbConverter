# Ps2UsbConverter

This is an Arduino sketch that can take an Arduino Leonardo, Arduino Pro Micro, or any other USB HID capable Arduino and turn it into an adapter that will allow you to convert a PS/2 keyboard to a USB keyboard. The sketch supports the use of two mappings internally, which can be toggled by the use of two separate switches. The idea of having two switches, both of which toggle which mapping is used, is to allow the mapping to be switched either by a switch on the adapter, or by a remote switch on a wire connected to the adapter. The sketch depends on two libraries, one for reading the keypress events from the PS/2 port and the other for passing them on to the USB HID interface.

This sketch was built around getting one particular PS/2 keyboard to work in one particular set of circumstances on one particular Arduino board. It is presented here as the basis for someone else to build their own custom PS/2 to USB keyboard adapter. Pin numbers in the sketch will likely need to be changed for different boards and the mappings can be changed to suit different tastes. Note that the mappings are indexed by Ps/2 scan codes and the values are USB HID keyboard scan codes. 
 
## Dependancies

PS2Events: https://github.com/speedfox-uk/PS2Events

KeyPress: https://github.com/speedfox-uk/KeyPress

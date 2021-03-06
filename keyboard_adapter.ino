#define byte uint8_t
#include <PS2Events.h>
#include "KeyPress.h"

//Pint 2 and pin 3 work for arduino mega
#define DATA_PIN 10
#define IRQ_PIN 3 //seems to have to be pin 3. no idea why
#define MAPPED_PIN A1
#define UNMAPPED_PIN 4
#define SW1_PIN 2
#define SW2_PIN A2

/*
 * These are the maps used to turn PS/2 scan codes into USB scan codes. 
 */

char ps2_to_usb_reampped_modded_codes[] = {
0x00,
0x00, //F9
0x00,
0x00, //F5
0x00, //F3
0x00, //F1
0x00, //F2
0x00, //F12
0x00, 
0x00, //F10
0x00, //F8
0x00, //F6
0x00, //F4
0x00, //TAB
0x00, //'`'
0x00,
0x00,
0xE6, //Left ALT --added
0x00, //LEFT shift --added
0x00,
0xE7, //Left ctrl --added
0x00, //'q'
0x00, //'1'
0x00,
0x00,
0x00,
0x00, //z
0x00, //s
0x00, //a
0x00, //w
0x00, //z
0x00,
0x00,
0x00, //c
0x00, //x
0x00, //d
0x00, //e
0x00, //4
0x00, //3
0x00,
0x00,
0x00, //SPACE ' '
0x00, //v
0x00, //f
0x00, //t
0x00, //r
0x00, //5
0x00,
0x00,
0x00, //n
0x00, //b
0x00, //h
0x00, //g
0x00, //y
0x00, //6
0x00,
0x00,
0x00,
0x00, //m
0x00, //j
0x00, //u
0x00, //7
0x00, //8
0x00,
0x00,
0x00, //',' 
0x00, //k
0x00, //i
0x00, //o
0x00, //0
0x00, //9
0x00,
0x00,
0x00, //'.'
0x00, //'/'
0x00, //l
0x00, //';'
0x00, //p
0x00, //'-'
0x00, 
0x00,
0x00,
0x00, //'\'
0x00, 
0x00, //'['
0x00, //'='
0x00, 
0x00,
0x00, //Caps lock --added
0x00, //Rshift --added
0x00, //Enter - added
0x00, //']'
0x00,
0x00, //'\\'
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00, //Backspace - added
0x00,
0x00,
0x00, //'1'
0x00,
0x00, //'4' & up
0x00, //'7'
0x00,
0x00,
0x00,
0x00, //'0'
0x00, //'.'
0x00, //'2' And down
0x00, //'5'
0x00, //'6' and right
0x00, //8 and up
0x00, //ESCAPE --added
0x00, //Num lock -added
0x00, //F11
0x00, //'+'
0x00, //'3'
0x00, //'-' Again aapparently
0x00, //'*'
0x00, //'9'
0x00, //Scroll
0x00,
0x00,
0x00,
0x00,
0x00 //F7
};



//Try these if there is a modified marker
char ps2_to_usb_remapped_codes[] = {
0x00,
0x00, //F9
0x00,
0x00, //F5
0x00, //F3
0x00, //F1
0x00, //F2
0x80, //F12 - reampped to vol down
0x00, 
0x7F, //F10 - remapped to mute
0x00, //F8
0x00, //F6
0x00, //F4
0x00, //TAB
0x00, //'`'
0x00,
0x00,
0x00, //Left ALT --added
0x00, //LEFT shift --added
0x00,
0x00, //Left ctrl --added
0x00, //'q'
0x00, //'1'
0x00,
0x00,
0x00,
0x00, //z
0x00, //s
0x00, //a
0x00, //w
0x00, //z
0x00,
0x00,
0x00, //c
0x00, //x
0x00, //d
0x00, //e
0x00, //4
0x00, //3
0x00,
0x00,
0x00, //SPACE ' '
0x00, //v
0x00, //f
0x00, //t
0x00, //r
0x00, //5
0x00,
0x00,
0x00, //n
0x00, //b
0x00, //h
0x00, //g
0x00, //y
0x00, //6
0x00,
0x00,
0x00,
0x00, //m
0x00, //j
0x00, //u
0x00, //7
0x00, //8
0x00,
0x00,
0x00, //',' 
0x00, //k
0x00, //i
0x00, //o
0x00, //0
0x00, //9
0x00,
0x00,
0x00, //'.'
0x00, //'/'
0x00, //l
0x00, //';'
0x00, //p
0x00, //'-'
0x00, 
0x00,
0x00,
0x00, //'\'
0x00, 
0x00, //'['
0x00, //'='
0x00, 
0x00,
0x00, //Caps lock --added
0x00, //Rshift --added
0x00, //Enter - added
0x00, //']'
0x00,
0x00, //'\\'
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00, //Backspace - added
0x00,
0x00,
0x00, //'1'
0x00,
0x00, //'4' & up
0x00, //'7'
0x00,
0x00,
0x00,
0x00, //'0'
0x00, //'.'
0x00, //'2' And down
0x00, //'5'
0x00, //'6' and right
0x00, //8 and up
0x00, //ESCAPE --added
0x00, //Num lock -added
0x81, //F11 - remapped to vol down
0x00, //'+'
0x00, //'3'
0x00, //'-' Again aapparently
0x00, //'*'
0x00, //'9'
0x00, //Scroll
0x00,
0x00,
0x00,
0x00,
0x00 //F7
};

//Try these if there is a modified marker
char ps2_to_usb_modded_codes[] = {
0x00,
0x00, //F9
0x00,
0x00, //F5
0x00, //F3
0x00, //F1
0x00, //F2
0x00, //F12
0x00, 
0x00, //F10
0x00, //F8
0x00, //F6
0x00, //F4
0x00, //TAB
0x00, //'`'
0x00,
0x00,
0x00, //Left ALT --added
0x00, //LEFT shift --added
0x00,
0x00, //Left ctrl --added
0x00, //'q'
0x00, //'1'
0x00,
0x00,
0x00,
0x00, //z
0x00, //s
0x00, //a
0x00, //w
0x00, //z
0x00,
0x00,
0x00, //c
0x00, //x
0x00, //d
0x00, //e
0x00, //4
0x00, //3
0x00,
0x00,
0x00, //SPACE ' '
0x00, //v
0x00, //f
0x00, //t
0x00, //r
0x00, //5
0x00,
0x00,
0x00, //n
0x00, //b
0x00, //h
0x00, //g
0x00, //y
0x00, //6
0x00,
0x00,
0x00,
0x00, //m
0x00, //j
0x00, //u
0x00, //7
0x00, //8
0x00,
0x00,
0x00, //',' 
0x00, //k
0x00, //i
0x00, //o
0x00, //0
0x00, //9
0x00,
0x00,
0x00, //'.'
0x00, //'/'
0x00, //l
0x00, //';'
0x00, //p
0x00, //'-'
0x00, 
0x00,
0x00,
0x00, //'\'
0x00, 
0x00, //'['
0x00, //'='
0x00, 
0x00,
0x00, //Caps lock --added
0x00, //Rshift --added
0x00, //Enter - added
0x00, //']'
0x00,
0x00, //'\\'
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00, //Backspace - added
0x00,
0x00,
0x4D, //'1' & end
0x00,
0x50, //'4' & left
0x4A, //'7' & home
0x00,
0x00,
0x00,
0x00, //'0'
0x00, //'.'
0x51, //'2' And down
0x00, //'5'
0x4F, //'6' and right
0x52, //8 and up
0x00, //ESCAPE --added
0x00, //Num lock -added
0x00, //F11
0x00, //'+'
0x4E, //'3' & page down
0x00, //'-' Again aapparently
0x00, //'*'
0x4B, //'9' & pageup
0x00, //Scroll
0x00,
0x00,
0x00,
0x00,
0x00 //F7
};


//The defautl scan code mapping. Use these if there is nothing lese to be used
char ps2_to_usb_codes[] = {
0x00,
0x42, //F9
0x00,
0x3E, //F5
0x3C, //F3
0x3A, //F1
0x3B, //F2
0x45, //F12
0x00, 
0x43, //F10
0x41, //F8
0x3F, //F6
0x3D, //F4
0x2B, //TAB
0x35, //'`'
0x00,
0x00,
0xE2, //Left ALT --added
0xE1, //LEFT shift --added
0x00,
0xE0, //Left ctrl --added
0x14, //'q'
0x1e, //'1'
0x00,
0x00,
0x00,
0x1d, //z
0x16, //s
0x04, //a
0x1a, //w
0x1f, //z
0x00,
0x00,
0x06, //c
0x1b, //x
0x07, //d
0x08, //e
0x21, //4
0x20, //3
0x00,
0x00,
0x2c, //SPACE ' '
0x19, //v
0x09, //f
0x17, //t
0x15, //r
0x22, //5
0x00,
0x00,
0x11, //n
0x05, //b
0x0b, //h
0x0a, //g
0x1c, //y
0x23, //6
0x00,
0x00,
0x00,
0x10, //m
0x0d, //j
0x18, //u
0x24, //7
0x25, //8
0x00,
0x00,
0x36, //',' 
0x0e, //k
0x0c, //i
0x12, //o
0x27, //0
0x26, //9
0x00,
0x00,
0x37, //'.'
0x38, //'/'
0x0f, //l
0x33, //';'
0x13, //p
0x2d, //'-'
0x00, 
0x00,
0x00,
0x34, //'\'
0x00, 
0x2f, //'['
0x2e, //'='
0x00, 
0x00,
0x39, //Caps lock --added
0xE5, //Rshift --added
0x28, //Enter - added
0x30, //']'
0x00,
0x31, //'\\'
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x2A, //Backspace - added
0x00,
0x00,
0x1e, //'1'
0x00,
0x21, //'4'
0x24, //'7'
0x00,
0x00,
0x00,
0x27, //'0'
0x37, //'.'
0x1f, //'2'
0x22, //'5'
0x23, //'6'
0x25, //8
0x29, //ESCAPE --added
0x53, //Num lock -added
0x44, //F11
0x2e, //'+'
0x20, //'3'
0x2d, //'-' Again aapparently
0x25, //'*'
0x26, //'9'
0x00, //Scroll
0x00,
0x00,
0x00,
0x00,
0x40 //F7
};


PS2Events input; //PS/2 input
boolean doRemap = true;

void setup() {
  pinMode(MAPPED_PIN, OUTPUT);
  pinMode(UNMAPPED_PIN, OUTPUT);
  pinMode(SW1_PIN, INPUT);
  pinMode(SW2_PIN, INPUT);  
  digitalWrite(MAPPED_PIN, doRemap ? LOW:HIGH);
  digitalWrite(UNMAPPED_PIN, !doRemap ? LOW:HIGH);
  input.begin(DATA_PIN, IRQ_PIN);  
  Serial.begin(9600);
  
  Serial.println("hi\n");
  delay(1000);

}

/**
 * The main loop. Has two distincly separate sections
 * 1.) Check remap state: checks the switches and see if remapping is reuired. If this has changed from the last itteration of the loop update the LEDS and release all of the keys. 
 * 2.) Check the PS2Events to see if there are any events that need to be passed to the USB library. If remapping is reuired check those mappings first.
 */
void loop() {  
 KeyEvent evt;
 boolean sw1 = digitalRead(SW1_PIN);
 boolean sw2 = digitalRead(SW2_PIN);
 //If both switches are in the same state we want to remap, otherwise not
 boolean swNow = sw1 == sw2;

 //remapping has been switched change the states of the LEDs
 if(swNow != doRemap){   
   doRemap = swNow;
   digitalWrite(MAPPED_PIN, doRemap ? LOW:HIGH);
   digitalWrite(UNMAPPED_PIN, !doRemap ? LOW:HIGH);
   if(doRemap)
       Serial.println("Map on\n");
   else
       Serial.println("Map off\n");
   KeyPress.allUp();//Get rid of everything after the switch to be safe.
 }
 
 if(input.eventAvailable()) {
   input.readEvent(&evt);
   Serial.print(evt.code, DEC);
   char code = 0;

   //remapping is on. Lets try those tables first
   if(doRemap){
     if(evt.mod && 0 == code)
       code = ps2_to_usb_reampped_modded_codes[evt.code];
       if(0==code)
         code = ps2_to_usb_remapped_codes[evt.code];
   }

    
   if(evt.mod && 0 == code)
     code = ps2_to_usb_modded_codes[evt.code];

   if(0==code)
     code = ps2_to_usb_codes[evt.code];
    
   if(evt.state){
     Serial.print(" DOWN");
     if(0!= code)
       KeyPress.keyDown(code);
   }
   else{
     Serial.print(" UP");
     if(0!=code)
       KeyPress.keyUp(code);
    }
        
    if(evt.mod)
        Serial.print(" Mod");
    else
        Serial.print(" nomod");
    Serial.print('\n');
  }  
  
}



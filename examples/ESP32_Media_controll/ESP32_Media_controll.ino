/* Media control with rotary encoder */

#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

#define outputA 13 //CLK Pin of Rotary encoder
#define outputB 34 //DT Pin of Rotary encoder
#define PinSW 25 //Switch pin of Rotary encoder
//Gnd --> Gnd 

int aState;
int aLastState;  

void setup()
{ 
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleKeyboard.begin();
    pinMode (outputA,INPUT_PULLUP);
    pinMode (outputB,INPUT_PULLUP);
    pinMode(PinSW, INPUT_PULLUP);
    
    aLastState = digitalRead(outputA);   
} 

void loop()
{
    if(bleKeyboard.isConnected()) {

        int btn = digitalRead(PinSW);
        
        if (!(digitalRead(PinSW))) {
            bleKeyboard.write(KEY_MEDIA_MUTE);
            delay(250);    
        }
        
        aState = digitalRead(outputA); // Reads the "current" state of the outputA
        if (aState != aLastState){     
            if (digitalRead(outputB) != aState) { 
            bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
            bleKeyboard.releaseAll();
            } else {
            bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
            }
        } 
        aLastState = aState; // Updates the previous state of the outputA with the current state
    }
}

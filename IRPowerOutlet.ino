#include <IRLib.h>

int RECV_PIN = 11;
int RELAY_PIN = 12;
int RELAY_STATE = LOW;

IRrecv My_Receiver(RECV_PIN);

IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];

void setup()
{
  Serial.begin(9600);
  pinMode(RELAY_PIN,OUTPUT);
  My_Receiver.enableIRIn(); // Start the receiver
  My_Decoder.UseExtnBuf(Buffer);
  
}

void loop() {
  if (My_Receiver.GetResults(&My_Decoder)) {
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
    My_Receiver.resume(); 
    My_Decoder.decode();
    if(My_Decoder.decode_type == NEC){
      switch(My_Decoder.value) {
        case 0xE17ACC33:
        if(RELAY_STATE == LOW) {
          digitalWrite(RELAY_PIN,HIGH);
          RELAY_STATE = HIGH;
        } else {
          digitalWrite(RELAY_PIN,LOW);
          RELAY_STATE = LOW;
        }
        break;
      }
    }
  }
}


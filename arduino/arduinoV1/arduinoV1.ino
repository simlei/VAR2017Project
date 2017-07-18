/*
 *
 */

int timeout = 35;

int nrFrets = 8;
int fretSignals[8];
boolean measurements[6][8];

int nrActiveStrings = 5;
int activeStrings[5] = {0, 1, 2, 3, 4};

int frets[8] = {3, 2, 4, 5, 6, 7, 9, 8};
int strings[6] = {14, 15, 16, 17, 18, 19}; // lower strings first. brown, red, orange, green, yellow, blue

int extraWhite = 10;
int extraBlue = 11;
int extraYellow = 12;
int extraRed = 13;

int m;

int ledActive = 0;
int ledPin1 = strings[5];

#define SET(Byte,Bit) (Byte |= (1<<Bit)) // this takes a byte and turns the identified bit HIGH
#define CLR(Byte,Bit) (Byte &= (~(1<<Bit)))

void setup() {
  Serial.begin(9600);

  for(int i=0; i<19; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  if(ledActive == 1) {
    pinMode(ledPin1, OUTPUT);
    digitalWrite(ledPin1, HIGH);
  }

  for(int i=0; i<nrFrets; i++) {
    pinMode(frets[i], INPUT_PULLUP);
  }

  for(int i=0; i<nrActiveStrings; i++) {
    int pin = strings[activeStrings[i]];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }

}

void loop()
{

  
  setAllFalse();

  delay(timeout);
  sendOutput();

}

void readF(int idx)
{
  digitalWrite(strings[idx], LOW);

  for(int i=0; i<nrFrets; i++) {
    m = digitalRead(frets[i]);
    if(m == HIGH) {
      measurements[idx][i] = false;
    } else {
      measurements[idx][i] = true;
    }
  }

  digitalWrite(strings[idx], HIGH);
}

void sendOutput()
{

//  if(Serial.available() > 0 && Serial.read() == 'r')
//  {

    for(int i=0; i<nrActiveStrings; i++) {
      int idx = activeStrings[i];
      readF(idx);
    }
    
    for(int s = 0; s < 6; s++) {
      Serial.print("string,");
      Serial.print(s);
      Serial.print(",");
      for(int fret = 0; fret < nrFrets; fret++) {
        if(measurements[s][fret]) {
          Serial.print("o");
        } else {
          Serial.print("-");
        }
      }
      
      Serial.print("\n ");
    }
//  }
  
  

  //Serial.println(dataPacket[5], HEX);


}


void setAllFalse()
{
  for(int i=0; i<6; i++) {
    for(int k=0; k<nrFrets; k++) {
      measurements[i][k] = false;
    }
  }
}


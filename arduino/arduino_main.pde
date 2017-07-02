/*
 *
 */

int ledPin = 13;                // choose the pin for the LED


int greenPin = 6;
int redPin = 7;
int yellowPin = 8;
int bluePin = 9;
int orangePin = 10;

//int pinBlackF1 = 6;
//int pinYellowF2 = 7;
//int pinWhiteF3 = 8;
//int pinRedF4 = 9;
//int pinBlueF5 = 10;

int firstString = 19;
int secondString = 18;
int thirdString = 17;
int fourthString = 16;
int fifthString = 15;
int sixthString = 14;

int green = 0;                    // variable for reading the pin status
int red = 0;
int yellow = 0;
int blue = 0;
int orange = 0;

int greenOn = 0;
int redOn = 0;
int yellowOn = 0;
int blueOn = 0;
int orangeOn = 0;

int greenTimerWait = 20;
int greenTimers[6] = {0,0,0,0,0,0}; //These give timing to properly read green buttons on each string.
int greenTimers2[6] = {0,0,0,0,0,0};
boolean triedGreen[6] = {false, false, false, false, false, false};

#define SET(Byte,Bit) (Byte |= (1<<Bit)) // this takes a byte and turns the identified bit HIGH
#define CLR(Byte,Bit) (Byte &= (~(1<<Bit)))

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, INPUT_PULLUP);      // declare LED as output

  pinMode(greenPin, INPUT_PULLUP);     // declare the fret inputs
  pinMode(redPin, INPUT_PULLUP);
  pinMode(yellowPin, INPUT_PULLUP);
  pinMode(bluePin, INPUT_PULLUP);
  pinMode(orangePin, INPUT_PULLUP);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  pinMode(firstString, OUTPUT);   // The string pins provide current to
  pinMode(secondString, OUTPUT);  // the fret pins
  pinMode(thirdString, OUTPUT);
  pinMode(fourthString, OUTPUT);
  pinMode(fifthString, OUTPUT);
  pinMode(sixthString, OUTPUT);

  digitalWrite(firstString, HIGH);  // set the strings to HIGH to start with
  digitalWrite(secondString, HIGH);
  digitalWrite(thirdString, HIGH);
  digitalWrite(fourthString, HIGH);
  digitalWrite(fifthString, HIGH);
  digitalWrite(sixthString, HIGH);
}

void loop()
{
  readF(firstString);
  readF(secondString);
  readF(thirdString);
  //readF(fourthString);
  //readF(fifthString);
  //readF(sixthString);
  sendOutput();
  setAllFalse();
}

void readF(int guitarString)
{
  digitalWrite(guitarString, LOW);

  green = digitalRead(greenPin);
  red = digitalRead(redPin);
  yellow = digitalRead(yellowPin);
  blue = digitalRead(bluePin);
  orange = digitalRead(orangePin);// read input value

  if (orange == LOW && blue == LOW  && orangeOn == 0)
  {
    orangeOn = guitarString;
    triedGreen[guitarString] = false;
  }
  else if (blue == LOW && yellow == LOW && blueOn == 0)
  {
    blueOn = guitarString;
    triedGreen[guitarString] = false;
  }
  else if (yellow == LOW && red == LOW && yellowOn == 0)
  {
    yellowOn = guitarString;
    triedGreen[guitarString] = false;
  }
  else if (red == LOW && green == LOW && redOn == 0)
  {
    redOn = guitarString;
    triedGreen[guitarString] = false;
  }
  else if (green == LOW)
  {
    if (triedGreen[guitarString] == false)
    {
      greenTimers[guitarString] = millis();
      triedGreen[guitarString] = true;
    }
    else //triedGreen == true
    {
      if (millis() - greenTimers[guitarString] > greenTimerWait
          && greenOn == 0)
      {
        greenOn = guitarString;
      }
    }
  }

  else  //no buttons pressed
  {
    triedGreen[guitarString] = false;
  }

  digitalWrite(guitarString, HIGH);
}

void sendOutput()
{
  boolean lightswitch = false;


  Serial.print("F5 ");
  Serial.print(orangeOn);
  Serial.print(", F4 ");
  Serial.print(blueOn);
  Serial.print(", F3 ");
  Serial.print(yellowOn);
  Serial.print(", F2 ");
  Serial.print(redOn);
  Serial.print(", F1 ");
  Serial.print(greenOn);
  //Serial.println(dataPacket[5], HEX);


}


void setAllFalse()
{
  greenOn = 0;
  redOn = 0;
  yellowOn = 0;
  blueOn = 0;
  orangeOn = 0;
}

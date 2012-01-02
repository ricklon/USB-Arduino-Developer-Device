/*
Git Controls using custom buttons as Keyboard output
 
 Press one of several buttons configured for the Arduino Leonardo, or ATMEga32u4 boards.
 
 Define the git repository you want to interact with.
 
 Created Jan 2, 2012
 by Rick Anderson
 
 button code, and keboard code insired from Tom Igoes KeyBoard Message exmaple
 KeyboardMessage.ino
 
 Pin Mapping without custom variant, using leonardo variant
x0 PD2 - digital 0 / serial RX
x1 PD3 - digital 1 / serial TX

1=11 PB7 - digital 11
0=10 PB6 - digital 10
2=2 PD1 - digital 2
3=3 PD0 - digital 3
4 PD4 - digital 4 / A6
5 PC6 - digital 5
6 PD7 - digital 6
8 PB4 - digital 8
9 PB5 - digital 9


Status LED
13 PC7 - digital 13
 
 */



#define NUMBUTTONS 9

char gitrepo[] = " https://github.com/ricklon/USB-Arduino-Developer-Device";
char absdirectory[] =  "/Users/rianders/projects/USB-Arduino-Developer-Device";

long previousMillis = 0;        // will store last time millis was updated
long interval = 65;           // interval at which to debounce (milliseconds)

const int buttonPins[] = { 
  10,11,2,3,4,5,6,8,9};

int previousButtonState[NUMBUTTONS] ={
  1,1,1,1,1,1,1,1,1};

const int statLedPin = 13;

void setup() 
{
  Serial.begin(9600);
  //Configure buttons
  for(int ii = 0; ii < NUMBUTTONS; ii++) //Init digital pins for INPUT
  {
    pinMode(buttonPins[ii], INPUT);     
  }
  //configure status LED
  pinMode(statLedPin, OUTPUT);
  //diagnostic blink
  digitalWrite(statLedPin, HIGH);
  delay(250);
  digitalWrite(statLedPin, LOW);
}

void loop() 
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) 
  {
    for(int ii = 0; ii < NUMBUTTONS; ii++) //Read button state
    {
      int buttonState = digitalRead(buttonPins[ii]); 
      Serial.print("Buton[");
      Serial.print(ii);
      Serial.print("] ");
      Serial.println(buttonState);
       //Light stat LED while button pressed   
       digitalWrite(statLedPin, buttonState);
      if ((buttonState != previousButtonState[ii])  && (buttonState == HIGH))   // and it's currently pressed:
      {
        doAction(ii);
      }
      previousButtonState[ii] = buttonState;
    }
  }
}

void doAction(int button)
{
  switch(button)
  {
  case 0: //Clone repository
    Keyboard.print("git clone ");
    Keyboard.println(gitrepo);
    break;
  case 1: //Change to projcet directory
    Keyboard.print("cd ");
    Keyboard.println(absdirectory);
    break;
  case 2: //Fetch changes
    Keyboard.println("git fetch");
    break;
  case 3: //Check status
    Keyboard.println("git diff --stat origin/master");
    break;
  case 4: //Get the changes
    Keyboard.println("git merge");
    break;
  case 5:  //List branches
    Keyboard.println("git branches");
    break;
  case 6: //Check differences
    Keyboard.println("git diff");
    break;
  case 7: //Commit changes
    Keyboard.print("git commit -a -m \"mychange\"");
    break;
  case 8: //Push changes
    Keyboard.println("git push");
    break;

  }
}






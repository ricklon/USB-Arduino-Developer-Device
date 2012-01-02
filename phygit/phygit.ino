/*
Git Controls using custom buttons as Keyboard output
 
 Press one of several buttons configured for the Arduino Leonardo, or ATMEga32u4 boards.
 
 Define the git repository you want to interact with.
 
 Created Jan 2, 2012
 by Rick Anderson
 
 button code, and keboard code insired from Tom Igoes KeyBoard Message exmaple
 KeyboardMessage.ino
 
 */

#define GITREPO  https://github.com/ricklon/USB-Arduino-Developer-Device
#define ABSDIRECTORY /Users/rianders/projects/USB-Arduino-Developer-Device
#define NUMBUTTONS 10

long previousMillis = 0;        // will store last time millis was updated
long interval = 15;           // interval at which to debounce (milliseconds)

const int buttonPins[] = { 
  26,27,28,29,30,31,32,33,34,35};

int previousButtonState[NUMBUTTONS] ={
  0,0,0,0,0,0,0,0,0,0};

void setup() 
{

  for(int ii = 0; ii < NUMBUTTONS; ii++) //Init digital pins for INPUT
  {
    pinMode(buttonPins[ii], INPUT);     
  }
}

void loop() 
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) 
  {
    for(int ii = 0; ii < NUMBUTTONS; ii++) //Read button state
    {
      int buttonState = digitalRead(buttonPins[ii]);    
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
    Keyboard.print("GITREPO");
    break;
  case 1: //Fetch changes
    Keyboard.println("git fetch");
    break;
  case 2: //Check status
    Keyboard.println("git diff --stat origin/master");
    break;
  case 3: //check differences summary
    Keyboard.println("git diff --name-only origin/master");
    break;
  case 4: //Get the changes
    Keyboard.println("");
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
  case 9: //Change to projcet directory
    Keyboard.print("cd");
    Keyboard.println("ABSDIRECTORY");
    break;


  }
}






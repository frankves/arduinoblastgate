/*  Servo Control for blast gates
    with a little help from Bob from ILikeToMakeStuff :)
    Frank van Es - 5 apr 2021
    13-5-2023 adaptation for Alex Fehlerstrom blast gate on pos1

    PINConfig:
                  ServoPin    ButtonPin
    Servo   1     3           2
    Servo   2     5           4
    Servo   3     6           7
    Servo   4     9           8
    Servo   5     10          12
    Servo   6 .   11 .        13
*/

#include <Servo.h>      // servo control
#include <ezButton.h> // debounce


// SERVO CONFIG
// twelve servo objects can be created on most boards
const byte servoCount = 5;

static Servo servoList[servoCount];

const int openPos = 180;  // open positions for servo . 135
const int closedPos = 90;  // close position for servo . 90


//BUTTON CONFIG

ezButton button1(2);  // define ez Buttons
ezButton button2(4);
ezButton button3(7);
ezButton button4(8);
ezButton button5(12);


void setup() {

  Serial.begin(9600);

  // SET DEBOUNCE TIME
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50);
  button3.setDebounceTime(50);
  button4.setDebounceTime(50);
  button5.setDebounceTime(50);

  //DEFINE BUTTONS
  pinMode (2, INPUT_PULLUP); // pullup for not needing an extra resistor
  pinMode (4, INPUT_PULLUP);
  pinMode (7, INPUT_PULLUP);
  pinMode (8, INPUT_PULLUP);
  pinMode (12, INPUT_PULLUP);

  //DEFINE SERVO ARRAY and open all
  servoList[0].attach(3);   //~ above workbench
  servoList[1].attach(5);   //~ table saw
  servoList[2].attach(6);   //~ defective
  servoList[3].attach(9);   //~ mitre saw
  servoList[4].attach(10);  //~ disc sander
  //servoList[0].write(openPos);   //~
  servoList[1].write(openPos);   //~
  //servoList[2].write(openPos);   //~
  //servoList[3].write(openPos);   //~
  //servoList[4].write(openPos);  //~
}

void loop() {

  button1.loop(); // MUST call the loop() function first
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();

  //Serial.println(button1.getState());

  delay(50); // generally an ok delay for pressing a button.
 
  if (button1.isPressed()) {
    Serial.println("Button1 is Pressed");
    servoAttach();  // attach and detach for each button to prevent constant chattering of servo
    setServoState(0);
    servoDetach();
  }

  if (button2.isPressed()) {
    Serial.println("Button2 is Pressed");
    servoAttach();
    setServoState(1);
    servoDetach();
  }

  if (button3.isPressed()) {
    Serial.println("Button3 is Pressed");
    servoAttach();
    setServoState(2);
    servoDetach();
  }

  if (button4.isPressed()) {
    Serial.println("Button4 is Pressed");
    servoAttach();
    setServoState(3);
    servoDetach();
  }

  if (button5.isPressed()) {
    Serial.println("Button5 is Pressed");
    servoAttach();
    setServoState(4);
    servoDetach();
  }
}

// Open servo corresponding to button and close all other gates,
void setServoState(char number) {
  int thisServ = 0;
  int val;
  boolean ignoreAll = false;
  switch (number) {
    case '1':
      val = 0;
      break;
    case '2':
      val = 1;
      break;
    case '3':
      val = 2;
      break;
    case '4':
      val = 3;
      break;
    case '5':
      val = 4;
      break;

      ignoreAll = true;
      break;
    default:
      val = number;
      break;
  }
  int newPos = 0;
  if (!ignoreAll) {
    
    //Serial.println("In the servo loop");
    servoList[val].write(openPos); // first open a gate to prevent vacuum Pull
    //openAll();
    for (thisServ = 0; thisServ < servoCount; thisServ += 1) {
      delay(500); // wait between to prevent overload of circuits
      if (thisServ == val) {
        newPos = openPos;
        //Serial.println("open the Gates!");
      }
      else {
        newPos = closedPos;
        //Serial.println("close the Gates!");
      }
      //}
      servoList[thisServ].write(newPos);

    }
  }

}

void servoAttach() {
  servoList[0].attach(3); //attach servos
  servoList[1].attach(5);
  servoList[2].attach(6);
  servoList[3].attach(9);
  servoList[4].attach(10);
  delay(500);
}

void servoDetach() {
  delay(500);
  servoList[0].detach(); //detach servos
  servoList[1].detach();
  servoList[2].detach();
  servoList[3].detach();
  servoList[4].detach();
}

void openAll(){
  servoList[0].write(openPos);
  servoList[1].write(openPos);
  servoList[2].write(openPos);
  servoList[3].write(openPos);
  servoList[4].write(openPos);
  
}

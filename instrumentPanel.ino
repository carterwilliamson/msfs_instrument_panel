#include <Joystick.h>
#define IGNITION 2
#define FLAPS_UP 3
#define FLAPS_DOWN 4
#define BEA 5
#define LND 6
#define TAXI 7
#define NAV 8
#define STR 9
#define THROTTLE A0
#define TRIM A2
#define MIX A1
#define LOWER_E_KEY 101
#define KEY_HOLD_DURATION 500

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 32, 0,
  true, true, false, false, false, false,
  true, true, false, false, false);


int digitalPins[] = {IGNITION, FLAPS_UP, FLAPS_DOWN, BEA, LND, TAXI, NAV, STR};
int analogPins[] = {THROTTLE, TRIM, MIX};

bool ignitionStatus = false;
bool beaStatus = false;
bool lndStatus = false;
bool taxiStatus = false;
bool navStatus = false;
bool strStatus = false;
int throttleValue = 0;
int trimValue = 0;
int mixValue = 0;

bool debugMode = true
;

void setup() {
  // put your setup cde here, to run once:
  pinMode(IGNITION, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(FLAPS_UP, INPUT_PULLUP);
  pinMode(FLAPS_DOWN, INPUT_PULLUP);
  pinMode(TRIM, INPUT_PULLUP);
  pinMode(THROTTLE, INPUT_PULLUP);
  pinMode(MIX, INPUT_PULLUP);
  Serial.begin(9600);

  Joystick.setThrottleRange(0, 100);
  Joystick.setXAxisRange(-100, 100);
  Joystick.setYAxisRange(0, 100);
  Joystick.begin();
}

void pressButton(unsigned int button){
    Joystick.pressButton(button);
    delay(KEY_HOLD_DURATION);
    Joystick.releaseButton(button);
}

void pressButtonQuick(unsigned int button){
    Joystick.pressButton(button);
    delay(100);
    Joystick.releaseButton(button);
}

void startIgnition(){
    pressButton(1);
    ignitionStatus = true;
}

void stopIgnition(){
    pressButton(2);
    ignitionStatus = false;
}

void handleIgnition(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("Ignition value is " + val);
  }
    
  if(pinValue==HIGH && ignitionStatus==false){
    startIgnition();
  }
  else if(pinValue==LOW && ignitionStatus==true){
    stopIgnition();
  }
}

void handleThrottle(float pinValue){
  
  int newThrottleValue = map(pinValue, 16, 1019, 100, 0);
  
  if (debugMode){
    Serial.println("Throttle value is " + String(newThrottleValue) + "(" + String(pinValue) + ")");
  }
  if(throttleValue != newThrottleValue){
    throttleValue = newThrottleValue;
    
    Joystick.setThrottle(throttleValue);
      
  }
}

void handleTrim(float pinValue){
  int axisValue = (pinValue < 558) ? map(pinValue, 24, 552, 28, 0) : map(pinValue, 562, 1019, 0, -13);

  
  if (debugMode){
    Serial.println("Trim value is " + String(axisValue) + " " + String(pinValue));
  }
  if(trimValue != axisValue){
    Serial.println("HERE");
    trimValue = axisValue;
    Joystick.setXAxis(axisValue);
  }
  
}

void handleMix(float pinValue){
  int axisValue = map(pinValue, 16, 1019, 100, 0);
  
  if (debugMode){
    Serial.println("mix value is " + String(axisValue) + " " + String(pinValue));
  }
  if (axisValue != mixValue){
    mixValue = axisValue;
    Joystick.setYAxis(axisValue);
  }
  
}

void handleFlapsUp(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("Flaps up value is " + String(pinValue));
  }
  if (pinValue == HIGH){
    pressButtonQuick(3);
  }
}

void handleFlapsDown(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("Flaps down value is " + String(pinValue));
  }
  if(pinValue == HIGH){
    pressButtonQuick(4);
  }
}

void handleBea(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("bea value is " + String(pinValue));
  }
  if(pinValue==HIGH && beaStatus==false) {
    pressButton(5);
    beaStatus = true;
  }else if (pinValue==LOW && beaStatus==true){
    pressButton(6);
    beaStatus = false;
  }
}

void handleLnd(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("lnd value is " + String(pinValue));
  }

  if(pinValue==HIGH && lndStatus==false) {
    pressButton(7);
    lndStatus = true;
  }else if (pinValue==LOW && lndStatus==true){
    pressButton(8);
    lndStatus = false;
  }
}

void handleTaxi(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("taxi value is " + String(pinValue));
  }

  if(pinValue==HIGH && taxiStatus==false) {
    pressButton(9);
    taxiStatus = true;
  }else if (pinValue==LOW && taxiStatus==true){
    pressButton(10);
    taxiStatus = false;
  }
}

void handleNav(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("nav value is " + String(pinValue));
  }

  if(pinValue==HIGH && navStatus==false) {
    pressButton(11);
    navStatus = true;
  }else if (pinValue==LOW && navStatus==true){
    pressButton(12);
    navStatus = false;
  }
}

void handleStr(int pinValue){
  if (debugMode){
    String val = pinValue==HIGH ? "On" : "Off";
    Serial.println("str value is " + String(pinValue));
  }

  if(pinValue==HIGH && strStatus==false) {
    pressButton(13);
    strStatus = true;
  }else if (pinValue==LOW && strStatus==true){
    pressButton(14);
    strStatus = false;
  }
}

void loop() {
  for(int i=0; i<8; i++){
    int digitalPin = digitalPins[i];
    int digitalPinValue = digitalRead(digitalPin);
    switch(digitalPin){
      case IGNITION:
        handleIgnition(digitalPinValue);
        break;
      case FLAPS_UP:
        handleFlapsUp(digitalPinValue);
        break;
      case FLAPS_DOWN:
        handleFlapsDown(digitalPinValue);
        break;
        
      case BEA:
        handleBea(digitalPinValue);
        break;
        
      case LND:
        handleLnd(digitalPinValue);
        break;
        
      case TAXI:
        handleTaxi(digitalPinValue);
        break;
        
      case NAV:
        handleNav(digitalPinValue);
        break;
        
      case STR:
        handleStr(digitalPinValue);
        break;
      default:
        Serial.println("Unexpected digital pin: " + String(digitalPin));
      break;
    }
  }
    
  for(int i=0; i<3; i++){
    int analogPin = analogPins[i];
    int analogPinValue = analogRead(analogPin);
    switch(analogPin){
      case THROTTLE:
        handleThrottle(analogPinValue);
      break;
      case TRIM:
        handleTrim(analogPinValue);
      break;
      case MIX:
        handleMix(analogPinValue);
      break;
      default:
        Serial.println("Unexpected analog pin: " + String(analogPin));
      break;
    }
  }
  delay(250);
}

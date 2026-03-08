

/*
 * This is a pick & place robot using relays and limit switchs 
 * operating by Blynk 
 * it have auto & manual mode 
 * 03.03.2026
 * Blynk id and pass
 * cottonpicplace@etics.us
 * xxxxxxxxxxxxx
 */  

#define BLYNK_TEMPLATE_ID "TMPL37RhGrljc"
#define BLYNK_TEMPLATE_NAME "Cotton Pic Place"
#define BLYNK_AUTH_TOKEN "LukuiANOll7_cMhMP21XBnycK_eIhKgB"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define relay1 15 
#define relay2 2
#define relay3 4
#define relay4 5 

#define R5 18    //up
#define R6 19    //down
#define R7 21   //left
#define R8 22   //right
#define R9 25   //open
#define R10 27   // close

#define L1 13
#define L2 14
#define L3 26
#define L4 32
#define L5 12
#define L6 33

#define IR_PIN 16

#define buzz 23
 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "admin"; 
char pass[] = "1234567890"; 

uint32_t ts,ts1,ts2; 
int ir;
bool objectD=false;

bool lastPB = HIGH;
bool pbState = HIGH;
bool pbStableState = HIGH;
bool pbLastReading = HIGH;
unsigned long pbLastChange = 0;
const unsigned long pbDebounceDelay = 50;

bool AutoMode=false;
bool manUp=false;
bool manDown=false;
bool manLeft=false;
bool manRight=false;
bool manOpen=false;
bool manClose=false;
bool Auto=false;

const unsigned long debounceDelay = 50;
unsigned long autoTimer = 0;
bool TimerStarted = false;
unsigned long buzTimer = 0;
bool buzActive = false;
unsigned long ls1_lastChange = 0;
bool ls1_stableState = HIGH;

unsigned long ls2_lastChange = 0;
bool ls2_stableState = HIGH;

unsigned long ls3_lastChange = 0;
bool ls3_stableState = HIGH;

unsigned long ls4_lastChange = 0;
bool ls4_stableState = HIGH;

unsigned long ls5_lastChange = 0;
bool ls5_stableState = HIGH;

unsigned long ls6_lastChange = 0;
bool ls6_stableState = HIGH;

enum HomeState {
  HOME_IDLE,
  HOME_Z,
  HOME_X,
  HOME_Y,
  HOME_DONE
};

HomeState homeState = HOME_IDLE;
enum AutoState {
  AUTO_IDLE,
  AUTO_HOME,
  AUTO_FORWARD,
  AUTO_DOWN,
  AUTO_CLOSE,
  AUTO_UP,
  AUTO_RIGHT,
  AUTO_OPEN,
  AUTO_LEFT
};

AutoState autoState = AUTO_IDLE;

bool HomeS = false;

void Home();
bool debounceLS(int pin, bool &stableState, unsigned long &lastChangeTime)
{
  bool reading = digitalRead(pin);

  if(reading != stableState)
  {
    if(millis() - lastChangeTime > debounceDelay)
    {
      stableState = reading;
      lastChangeTime = millis();
    }
  }
  else
  {
    lastChangeTime = millis();
  }

  return stableState;
}
void StopALL()
{
  digitalWrite(relay1,LOW);digitalWrite(relay2,LOW);digitalWrite(relay3, LOW);digitalWrite(relay4, LOW);
  digitalWrite(R5,LOW);digitalWrite(R6,LOW);digitalWrite(R7, LOW);digitalWrite(R8, LOW);
  digitalWrite(R9, LOW);digitalWrite(R10, LOW);digitalWrite(buzz, LOW);
  // Serial.println("All are stopped -Safe");
}

void setup() {
  Serial.begin(115200);
  
  pinMode(L1, INPUT_PULLUP);pinMode(L2, INPUT_PULLUP);pinMode(L3, INPUT_PULLUP);
  pinMode(L4, INPUT_PULLUP);pinMode(L5, INPUT_PULLUP);pinMode(L6, INPUT_PULLUP);
  
  pinMode(IR_PIN, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);
  pinMode(R10, OUTPUT);
  pinMode(buzz, OUTPUT);
  
  StopALL();

   WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Blynk Starts");

  HomeS = false;
  while(!HomeS)
  {
     Home();
     delay(5);
  }
  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);
  

}

void loop() {

  Blynk.run();
  
  ir=digitalRead(IR_PIN);
  ls1=digitalRead(L1);ls2=digitalRead(L2);ls3=digitalRead(L3);
  ls4=digitalRead(L4);ls5=digitalRead(L5);ls6=digitalRead(L6);
  
 /*Serial.print("LS1:");Serial.print(ls1);
  Serial.print("|LS2:");Serial.print(ls2);
  Serial.print("|LS3:");Serial.print(ls3);
  Serial.print("|LS4:");Serial.print(ls4);
  Serial.print("|LS5:");Serial.print(ls5);
  Serial.print("|LS6:");Serial.print(ls6);
   Serial.print("| IR:");Serial.println(ir);*/
  
    if(!Auto)
    {
        HomeS=false;
        if(AutoMode)
        {
          StopALL();
          AutoMode=false;
        }
      Serial.println("Auto mode off-Manual ON");
    
    }
    if(Auto)
    {
      Serial.println("Manual mode off-Auto ON");
      if(!AutoMode)   
      {
        AutoMode=true;
        StopALL();
        autoState = AUTO_HOME;
      }
    }
 
    if(AutoMode)
    {
      AUTO();
      
    }
      if(!AutoMode)
    {
      autoState = AUTO_IDLE;
    }
    if(!AutoMode)
    {
    
      if(manUp && ls1 == HIGH)
          digitalWrite(R5, HIGH);
      else
          digitalWrite(R5, LOW);
    
      if(manDown && ls2 == HIGH)
          digitalWrite(R6, HIGH);
      else
          digitalWrite(R6, LOW);
    
      if(manLeft && ls4 == HIGH)
          digitalWrite(R7, HIGH);
      else
          digitalWrite(R7, LOW);
    
      if(manRight && ls3 == HIGH)
          digitalWrite(R8, HIGH);
      else
          digitalWrite(R8, LOW);
    
      if(manOpen && ls5 == HIGH)
          digitalWrite(R9, HIGH);
      else
          digitalWrite(R9, LOW);
    
      if(manClose && ls6 == HIGH)
          digitalWrite(R10, HIGH);
      else
          digitalWrite(R10, LOW);
    }
   
  
}


BLYNK_WRITE(V0) {x = param.asInt(); if(x==1 && !AutoMode){Serial.println("Forward"); digitalWrite(relay1, HIGH);digitalWrite(relay3,HIGH); digitalWrite(relay2, LOW);digitalWrite(relay4, LOW); }else if(x==0){Stop();}}

BLYNK_WRITE(V1) {y = param.asInt();if(y==1 && !AutoMode){Serial.println("Reverse ");digitalWrite(relay2, HIGH);digitalWrite(relay4, HIGH); digitalWrite(relay1, LOW);digitalWrite(relay3, LOW); }else if(y==0){Stop();}}

BLYNK_WRITE(V2) {z = param.asInt();if(z==1 && !AutoMode){Serial.println("LEFT"); digitalWrite(relay3, HIGH);digitalWrite(relay4, LOW); digitalWrite(relay2,HIGH );digitalWrite(relay1, LOW);}else if(z==0){Stop();}}

BLYNK_WRITE(V3) {a = param.asInt(); if(a==1 && !AutoMode){Serial.println("RIGHT"); digitalWrite(relay4, HIGH);digitalWrite(relay3,LOW);digitalWrite(relay1,HIGH);digitalWrite(relay2, LOW); } else if(a==0){Stop();}}


BLYNK_WRITE(V4){ manUp = param.asInt(); }
BLYNK_WRITE(V5){ manDown = param.asInt(); }
BLYNK_WRITE(V6){ manLeft = param.asInt(); }
BLYNK_WRITE(V7){ manRight = param.asInt(); }
BLYNK_WRITE(V8){ manOpen = param.asInt(); }
BLYNK_WRITE(V9){ manClose = param.asInt(); }

BLYNK_WRITE(V10) {
  Auto= param.asInt();
  
  }
  
void Stop(){
  if(!AutoMode){
  digitalWrite(relay1,LOW);digitalWrite(relay2,LOW);digitalWrite(relay3, LOW);digitalWrite(relay4, LOW);
   Serial.println("Stopped!!");}
}

void AUTO()
{
  bool LS1 = debounceLS(L1, ls1_stableState, ls1_lastChange);
  bool LS2 = debounceLS(L2, ls2_stableState, ls2_lastChange);
  bool LS3 = debounceLS(L3, ls3_stableState, ls3_lastChange);
  bool LS4 = debounceLS(L4, ls4_stableState, ls4_lastChange);
  bool LS5 = debounceLS(L5, ls5_stableState, ls5_lastChange);
  bool LS6 = debounceLS(L6, ls6_stableState, ls6_lastChange);
  static AutoState lastState = AUTO_IDLE;

  if(autoState != lastState)
  {
    //Serial.print("AUTO STATE -> ");
    //Serial.println(autoState);
    lastState = autoState;
  }

  switch(autoState)
  {
    case AUTO_IDLE:
      if(AutoMode)
        autoState = AUTO_HOME;
    break;

    case AUTO_HOME:
      if(!HomeS)
      {
        Home();
      }
      else
      {
        autoState = AUTO_FORWARD;
      }
    break;

  
        case AUTO_FORWARD:
    
      digitalWrite(relay1, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay2, LOW);
      digitalWrite(relay4, LOW);
    
      if(ir == 0)
      {
        if(!TimerStarted)
        {
          autoTimer = millis();
          TimerStarted = true;
        }
    
        if(millis() - autoTimer >= 500)
        {
          StopALL();
          TimerStarted = false;
          autoState = AUTO_CLOSE;
        }
      }
    
    break;

   
   case AUTO_CLOSE:
     if(LS6 == HIGH)
      {
        digitalWrite(R10, HIGH);
      }
      else
      {
        digitalWrite(R10, LOW);
        autoState = AUTO_UP;
      }
   break;

    
    case AUTO_UP:
      if(LS1 == HIGH)
      {
        digitalWrite(R5, HIGH);
      }
      else
      {
        digitalWrite(R5, LOW);
        autoState = AUTO_RIGHT;
      }
    break;

    
    case AUTO_RIGHT:
      if(LS3 == HIGH)
      {
        digitalWrite(R8, HIGH);
      }
      else
      {
        digitalWrite(R8, LOW);
        autoState = AUTO_OPEN;
      }
    break;

    
    case AUTO_OPEN:
      if(LS5 == HIGH)
      {
        digitalWrite(R9, HIGH);
      }
      else
      {
        digitalWrite(R9, LOW);
        autoState = AUTO_LEFT;
      }
    break;

    
    case AUTO_LEFT:
      if(LS4 == HIGH)
      {
        digitalWrite(R7, HIGH);
      }
      else
      {
        digitalWrite(R7, LOW);
        autoState = AUTO_DOWN;
      }
    break;

    
    case AUTO_DOWN:
      if(LS2 == HIGH)
      {
        digitalWrite(R6, HIGH);
      }
      else
      {
        digitalWrite(R6, LOW);
        autoState = AUTO_FORWARD;
      }
    break;
  }
}


void Home()
{
  bool LS2 = debounceLS(L2, ls2_stableState, ls2_lastChange);
  bool LS4 = debounceLS(L4, ls4_stableState, ls4_lastChange);
  bool LS5 = debounceLS(L5, ls5_stableState, ls5_lastChange);

  switch(homeState)
  {
    case HOME_IDLE:
      Serial.println("Home Started...");
      homeState = HOME_X;
      break;

    case HOME_Z:
      if(LS2 == HIGH)
      {
        digitalWrite(R6, HIGH);   // Move Down
      }
      else
      {
        digitalWrite(R6, LOW);
        homeState = HOME_Y;
      }
      break;

    case HOME_X:
      if(LS4 == HIGH)
      {
        digitalWrite(R7, HIGH);   // Move Left
      }
      else
      {
        digitalWrite(R7, LOW);
        homeState = HOME_Z;
      }
      break;

    case HOME_Y:
      if(LS5 == HIGH)
      {
        digitalWrite(R9, HIGH);   // Grip Open
      }
      else
      {
        digitalWrite(R9, LOW);
        homeState = HOME_DONE;
      }
      break;

    case HOME_DONE:

  if(!buzActive)
  {
    digitalWrite(buzz, HIGH);
    buzTimer = millis();
    buzActive = true;
  }

  if(millis() - buzTimer > 500)
  {
    digitalWrite(buzz, LOW);
    buzActive = false;

    Serial.println("Home Completed");
    HomeS = true;
    homeState = HOME_IDLE;
  }

break;
  }
}

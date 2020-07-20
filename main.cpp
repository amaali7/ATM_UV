#include <Arduino.h>

/* 
  
  States :- 
  
  int State

  0 : Wating for motion to statr state  
  1 : Motion detected operation online
  2 : motion stoped wating for movment
  3 : UV online

*/

size_t State = 0; 
size_t UV_Pin= LED_BUILTIN; // UV Pin
size_t Sinsor= 10;  // Sinsor Pin
size_t UV_State = 1;
size_t TimeOfUV = 1000;
size_t DelayTime = 2000;

int SinsorState(){
  if (digitalRead(Sinsor) == HIGH)
  {
    return 1;
  }
  else if (digitalRead(Sinsor) == LOW)
  {
    return 0;
  }
  else
  {
    return 2;
  }
}

void Main(){
  if (State == 0)
    {
      if (UV_State == 1)
      {
        digitalWrite(UV_Pin,LOW);
        UV_State = 0;
      }
    }
  if (State == 0 && SinsorState() == 1)
  {
    State = 1;    
  }
  else if (State == 1)
  {
     int S1 = SinsorState();
     delay(DelayTime);
     int S2 = SinsorState();
     Serial.print("State 1   ");
     Serial.print("S1 = ");
     Serial.print(S1);
     Serial.print("    S2 = ");
     Serial.print(S2);
     Serial.print("\n");
     if (S1 == 1 || S2 == 1)
     {
     }
     else if(S1 == 0 && S2 == 0)
     {
       State = 2;
     }     
  }
  else if (State == 2)
  { 
    int S1 = SinsorState();
    delay(DelayTime);
    int S2 = SinsorState();
    
     Serial.print("State 2   ");
     Serial.print("S1 = ");
     Serial.print(S1);
     Serial.print("    S2 = ");
     Serial.print(S2);
     Serial.print("\n");
    if (S1 == 0 && S2 ==0)
    {
      State = 3;
    }
    else
    {
      State = 1;
    }
  }
  else if(State==3)
  {
    digitalWrite(UV_Pin,HIGH);
    for (size_t i = 0; i < TimeOfUV; i++)
    {
      delay(20);
      if (SinsorState() == 1)
      {
        digitalWrite(UV_Pin,LOW);
        State = 1;
        UV_State = 0;
        break;
      }
    }

      digitalWrite(UV_Pin,LOW);
      State = 0;
      UV_State = 0;    
  }    
}

void setup(){
  pinMode(UV_Pin, OUTPUT);
  pinMode(Sinsor, INPUT);
  Serial.begin(9600);
}

void loop(){
  Main();
}
int LED1 = 16;
int LED2 = 5;

unsigned long pev1 = 0;
unsigned long pev2 = 0;
int taskled1 = 500;
int taskled2 = 1000;
int led1State = HIGH;
int led2State = HIGH;


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}


void loop() {
  if(millis() - pev1 >= taskled1){
    pev1 = millis();
 if(led1State == HIGH){
  led1State = LOW;
  }
  else if (led1State == LOW){
    led1State = HIGH;
    }
 
  digitalWrite(LED1, led1State);    

  }
  if(millis() - pev2 >= taskled2){
      pev2 = millis();
  if(led2State == HIGH){
  led2State = LOW;
  }
  else if (led2State == LOW){
    led2State = HIGH;
    } 
  digitalWrite(LED2, led2State); 
  }
}

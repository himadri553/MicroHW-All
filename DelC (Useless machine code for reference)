#include <Servo.h>
Servo lidservo;
Servo armservo; 
Servo flag;

int switchpin = 3;

int action = 1;

int pos = 0;

void setup() {
pinMode(switchpin,INPUT);
lidservo.attach(1);
armservo.attach(2);
flag.attach(4);

// Servo Default Starting Position

armservo.write(50);
flag.write(50);
lidservo.write(90);
}

void loop() {

// Action Selection starting with 1

  if (digitalRead(switchpin) == HIGH)
  {
  if (action > 8) {
    action = 1;
  }  
    if (action == 1) {
    action1();
    }
    else if (action == 2) {
    action2();
    }
    else if (action == 3) {
    action3();
    }
    else if (action == 4) {
    action4();
    }
    else if (action == 5) {
    action5();
    }
    else if (action == 6) {
    action6();
    }
    else if (action == 7) {
    action7();
    }
    else if (action == 8) {
    action8();
    }

    action += 1;
    
  }
}

//The Following are actions that are chosen chronologically

void action1() {
  lidservo.write(20);
  delay(1000);
  armservo.write(177);
  delay(500); 
  armservo.write(50);
  delay(1000);
  lidservo.write(90);
  delay(1000);
}

void action2() {
  lidservo.write(50);
  delay(100);
  armservo.write(177);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
}

void action3() {
    for(pos = 90; pos > 20; pos -=1)
  {
    lidservo.write(pos);
    delay(50);
  }
  armservo.write(177);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
}

void action4() {
  delay(250);
  lidservo.write(50);
  delay(100);
  armservo.write(177);
  delay(2500);
for(pos = 177; pos > 90; pos -=1)
  {
    armservo.write(pos);
    delay(50);
  }
  lidservo.write(90);
  armservo.write(50);
}

void action5() {
  lidservo.write(50);
  delay(500);
  lidservo.write(90);
  delay(500);
  lidservo.write(50);
  delay(500);
  lidservo.write(90);
  delay(500);
  lidservo.write(50);
  delay(500);
  lidservo.write(90);
  delay(2500);
  lidservo.write(50);
  delay(100);
  armservo.write(177);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
}

void action6() {
  lidservo.write(50);
  delay(100);
  armservo.write(155);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
  delay(250);
  lidservo.write(50);
  delay(100);
  armservo.write(155);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
  delay(250);
  lidservo.write(50);
  delay(100);
  armservo.write(155);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
  delay(250);  
  lidservo.write(50);
  delay(100);
  armservo.write(177);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
}

void action7() {
    for(pos = 90; pos > 20; pos -=2)
  {
    lidservo.write(pos);
    delay(50);
  }
for(pos = 50; pos < 145; pos +=2)
  {
    armservo.write(pos);
    delay(100);
  }
  armservo.write(177);
for(pos = 177; pos > 50; pos -=2)
  {
    armservo.write(pos);
    delay(100);
  }
for(pos = 20; pos < 90; pos +=2)
  {
    lidservo.write(pos);
    delay(50);
  }
  lidservo.write(90);
}

void action8() {
  if (digitalRead(switchpin) == HIGH)
  {
    delay(1000);
      for(pos = 90; pos > 20; pos -=2)
  {
    lidservo.write(pos);
    delay(50);
  }
      for(pos = 50; pos < 175; pos +=10)
  {
    flag.write(pos);
    delay(50);
  }
  delay(250);
      for(pos = 175; pos > 125; pos -=10)
  {
    flag.write(pos);
    delay(50);
  }
        for(pos = 125; pos < 175; pos +=10)
  {
    flag.write(pos);
    delay(50);
  }
        for(pos = 175; pos > 125; pos -=10)
  {
    flag.write(pos);
    delay(50);
  }
        for(pos = 125; pos < 175; pos +=10)
  {
    flag.write(pos);
    delay(50);
  }
        for(pos = 175; pos > 125; pos -=10)
  {
    flag.write(pos);
    delay(50);
  }
        for(pos = 125; pos < 175; pos +=10)
  {
    flag.write(pos);
    delay(50);
  }
        for(pos = 175; pos > 125; pos -=10)
  {
    flag.write(pos);
    delay(50);
  }
        for(pos = 125; pos < 175; pos +=10)
  {
    flag.write(pos);
    delay(50);
  }
  delay(250);
        for(pos = 175; pos > 50; pos -=10)
  {
    flag.write(pos);
    delay(50);
  }
   for(pos = 20; pos < 90; pos +=2)
  {
    lidservo.write(pos);
    delay(50);
  }
  delay(2000);
      lidservo.write(50);
  delay(100);
  armservo.write(177);
  delay(250);
  armservo.write(50);
  delay(100);
  lidservo.write(90);
  }

}

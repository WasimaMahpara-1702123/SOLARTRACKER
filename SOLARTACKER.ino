
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);


Servo servohori;                                                                                                                                                                                                                                                                                               
int servoh = 0;
int servohLimitHigh = 90;
int servohLimitLow = 0;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 90;
int servovLimitLow = 0;
//Assigning LDRs
int ldrtopl = 1; //top left LDR green
int ldrtopr = 0; //top right LDR yellow
int ldrbotl = 3; // bottom left LDR blue
int ldrbotr = 2; // bottom right LDR orange
void write_angle_lcd(int pos)
{
  lcd.setCursor(0,1);
  lcd.print(pos);
  lcd.print(" ");
  
}
 

 void setup () 
 {

  servohori.attach(9);
  servohori.write(0);
  servoverti.attach(10);
  servoverti.write(0);
 lcd.begin(16,2);
 lcd.print("SERVO ANGLE");
 lcd.setCursor(0,1);
  
   
 }

void loop()
{
 
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
    }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(10);
  }
  else if (avgleft ==avgright)
  {
  
int pos;
for(pos= 0; pos <= 180; pos +=1){

  servohori.write(pos);
  write_angle_lcd(pos);
  delay(50);
}
}
}

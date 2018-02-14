#include "includes.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "math.h"
#include "Wire.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
float angX, angY;
int cTime, lTime, eTime, aTime;
int cTime2, lTime2, eTime2, aTime2;
int mpuStatus = 0;
int sL = 0;
int sR = 0;
int pg = 0;
int startTime = 0;
int endTime = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  accelgyro.initialize();
  mpuStatus = accelgyro.testConnection() ? 1 : 0;
  accelgyro.setSleepEnabled(false);
  lcd.begin(16, 2);
  lcd.clear();
  cTime = millis();
  startTime = millis();
}

void loop() {
  cTime = millis();
  aTime = (cTime - lTime);
  eTime += aTime;
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  angX = (atan2(ay, az) + PI) * RAD_TO_DEG;
  angY = (atan2(ax, az) + PI) * RAD_TO_DEG;
  if(eTime >= 50) {
    cTime2 = millis();
    aTime2 = (cTime2 - lTime2);
    if(sL < 16 && sR < 16) {
      PDL_update();
      PDL_render();
    } else {
      eTime2 += aTime2;
      if(eTime2 >= 1000) {
        lcd.clear();
        if(sL >= 16) {
          lcd.setCursor(0, 0);
          lcd.print("WINNER");
        } else if(sR >= 16) {
          lcd.setCursor(0, 0);
          lcd.print("LOSER");
        }
        if(pg == 0) {
          lcd.setCursor(2, 1);
          lcd.print("Play Again??");
          pg = 1;
        } else {
          pg = 0;
        }
        eTime2 -= 500;
      }
    }
    lTime2 = cTime2;
    eTime -= 50;
  }
  lTime = cTime;
}

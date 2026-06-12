#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu;

// Pins
int redLED = 2;
int greenLED = 4;
int buzzer = 5;

int gasSensor = 34;
int flameSensor = 35;

// Thresholds
int gasThreshold = 500;

// States
bool systemOn = true;
bool emergencyMode = false;

// Siren variables
int freq = 500;
bool increasing = true;

// MPU previous values
int16_t prevAx = 0, prevAy = 0, prevAz = 0;

// Emergency timer
unsigned long emergencyStart = 0;

void setup() {
  Serial.begin(115200);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(flameSensor, INPUT);

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  mpu.initialize();

  lcd.setCursor(0,0);
  lcd.print("SMART SAFETY");
  lcd.setCursor(0,1);
  lcd.print("SYSTEM");
  delay(2000);
  lcd.clear();

  mpu.getAcceleration(&prevAx, &prevAy, &prevAz);
}

void loop() {

  // ===== GESTURE =====
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  int dAx = abs(ax - prevAx);
  int dAy = abs(ay - prevAy);
  int dAz = abs(az - prevAz);

  // 🔄 SHAKE → Emergency (5 sec)
  if (dAx > 15000 || dAy > 15000 || dAz > 15000) {
    emergencyMode = true;
    emergencyStart = millis();
  }

  // 👈 Tilt LEFT → Emergency (5 sec)
  else if (ax < -8000) {
    emergencyMode = true;
    emergencyStart = millis();
  }

  // 👉 Tilt RIGHT → OFF
  else if (ax > 8000) {
    systemOn = false;
  }

  // 📏 FLAT → ON
  else if (abs(ax) < 3000 && abs(ay) < 3000) {
    systemOn = true;
  }

  // ⏱️ Emergency timeout (5 sec)
  if (emergencyMode && millis() - emergencyStart > 5000) {
    emergencyMode = false;
  }

  prevAx = ax;
  prevAy = ay;
  prevAz = az;

  // ===== SYSTEM OFF =====
  if (!systemOn) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    noTone(buzzer);

    lcd.setCursor(0,0);
    lcd.print("SYSTEM OFF     ");
    lcd.setCursor(0,1);
    lcd.print("Tilt Right OFF ");
    return;
  }

  // ===== READ SENSORS =====
  int gasValue = analogRead(gasSensor);
  int flame = digitalRead(flameSensor);

  Serial.print("Gas: ");
  Serial.print(gasValue);
  Serial.print(" | Flame: ");
  Serial.println(flame);

  // ===== EMERGENCY =====
  if (emergencyMode) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    // Fast beep
    tone(buzzer, 2500);

    lcd.setCursor(0,0);
    lcd.print("!!!EMERGENCY!!!");
    lcd.setCursor(0,1);
    lcd.print("5 Sec Active   ");
    return;
  }

  // ===== FIRE =====
  if (flame == LOW) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    tone(buzzer, 2000);

    lcd.setCursor(0,0);
    lcd.print("FIRE ALERT!!!  ");
    lcd.setCursor(0,1);
    lcd.print("Take Action    ");
    return;
  }

  // ===== GAS =====
  if (gasValue > gasThreshold) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    // Ambulance siren
    tone(buzzer, freq);

    if (increasing) {
      freq += 30;
      if (freq >= 2000) increasing = false;
    } else {
      freq -= 30;
      if (freq <= 500) increasing = true;
    }

    lcd.setCursor(0,0);
    lcd.print("GAS ALERT!!!   ");
    lcd.setCursor(0,1);
    lcd.print("Level:");
    lcd.print(gasValue);
    lcd.print("   ");
    return;
  }

  // ===== SAFE =====
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
  noTone(buzzer);

  lcd.setCursor(0,0);
  lcd.print("STATUS: SAFE   ");
  lcd.setCursor(0,1);
  lcd.print("Gas:");
  lcd.print(gasValue);
  lcd.print("   ");

  delay(200);
}
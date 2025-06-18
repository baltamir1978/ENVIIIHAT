#include <M5StickCPlus2.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include "M5UnitENV.h"

Adafruit_SHT31 sht30 = Adafruit_SHT31();
QMP6988 qmp6988;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.fillScreen(BLACK);

  // ⚠️ Muy importante: configurar correctamente el bus I2C (GPIO0 = SDA, GPIO26 = SCL)
  Wire.begin(0, 26, 100000UL);
  delay(100);

  if (!sht30.begin(0x44)) {
    M5.Lcd.println("Fallo SHT30");
  }

  if (!qmp6988.begin(&Wire, 0x70, 0, 26, 100000UL)) {
    M5.Lcd.println("Fallo QMP6988");
  }
}

void loop() {
  float temp = sht30.readTemperature();
  float hum = sht30.readHumidity();
  float pres = qmp6988.calcPressure();  // Pascales

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.printf("Temp: %.2f C\n", temp);
  M5.Lcd.printf("Hum:  %.2f %%\n", hum);
  M5.Lcd.printf("Pres: %.2f hPa\n", pres / 100.0);

  delay(2000);
}

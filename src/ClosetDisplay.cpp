#include "application.h"
#line 1 "/Users/kevinmcquown/Dropbox/WCL/wcltalkstech/TempSensorProject/ClosetDisplay/src/ClosetDisplay.ino"
void displayMessage(uint8_t textSize, uint8_t lineNumber, const char *data);
void showTemp(const char *event, const char *data);
void setup();
void loop();
#line 1 "/Users/kevinmcquown/Dropbox/WCL/wcltalkstech/TempSensorProject/ClosetDisplay/src/ClosetDisplay.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

unsigned long timeOfLastUpdate;
unsigned long delta;
char timeString[10];

void displayMessage(uint8_t textSize, uint8_t lineNumber, const char *data) {
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.setCursor(0,lineNumber*18);
  display.println(data);
  display.display();
}

void showTemp(const char *event, const char *data)
{
  delta = millis() - timeOfLastUpdate;
  timeOfLastUpdate = millis();
  display.clearDisplay();
  displayMessage(2, 0, data);
  snprintf(timeString, sizeof(timeString), "%d", delta);
  displayMessage(2, 1, timeString);
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  timeOfLastUpdate = millis();

  display.clearDisplay();
  displayMessage(2, 0, "MESH...");
  Mesh.on();
  Mesh.connect();
  waitUntil(Mesh.ready);

  display.clearDisplay();
  displayMessage(2, 0, "WAITING");

  Mesh.subscribe("newTemp", showTemp);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}
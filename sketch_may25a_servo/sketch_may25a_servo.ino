#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


int pos = 0;
int soilMoistureValue = 0;
int tick = 1;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo servo_9;

void setup()
{
   
  servo_9.attach(9);
  
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

}



void loop() 
{
  // bring it down if it needs water
  if (soilMoistureValue > 0 && soilMoistureValue < 550) {
      for (pos = 0; pos <= 180; pos += 5) {
      servo_9.write(pos);
      delay(15); // Wait for 15 millisecond(s)
    }
  }
s
  delay(5000);
 
  for (pos = 180; pos >= 0; pos -= 5) {
    servo_9.write(pos);
    delay(15); // Wait for 15 millisecond(s)
  }
    
  soilMoistureValue = analogRead(A0);
  ++tick;
  delay(300);
  writeMoistureLevel(soilMoistureValue);

}


void writeMoistureLevel(int val) {
  
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println(val);
  display.setTextSize(1);
  display.setCursor(10,0);
  display.println(F("Moisture level"));
  display.display();
  delay(3000);
  display.clearDisplay();
  display.display();
  delay(1000);
}

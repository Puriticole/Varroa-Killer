#include <Sipeed_ST7789.h>

SPIClass spi_(SPI0); // MUST be SPI0 for Maix series on board LCD
Sipeed_ST7789 lcd(320, 240, spi_);


void func()
{
    lcd.fillScreen(COLOR_RED);
    lcd.drawRect(20, 20, 50, 50, COLOR_WHITE);
    lcd.fillCircle(100, 100, 40, COLOR_WHITE);
    lcd.fillTriangle(10, 200, 300, 200, 300, 150, COLOR_WHITE);
    lcd.setTextSize(2);
    lcd.setTextColor(COLOR_WHITE);
    lcd.setCursor(100,30);
    lcd.println("hello Sipeed Maix");
}

void setup()
{
    lcd.begin(15000000, COLOR_RED);    
}

void loop()
{
    lcd.setRotation(0);
    func();
}

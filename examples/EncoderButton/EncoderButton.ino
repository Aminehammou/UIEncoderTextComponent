/*
  Exemple EncoderButton : Bouton avec callback
*/

#include <TFT_eSPI.h>
#include <U8g2_for_TFT_eSPI.h>
#include "EncoderButton.h"

// TFT & U8g2
TFT_eSPI tft = TFT_eSPI();
U8g2_for_TFT_eSPI u8f(tft);

// Bouton
EncoderButton* button;

void setup() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    
    UIRect rect{10, 50, 220, 40};
    button = new EncoderButton(u8f, rect, "Cliquez!");
    button->setOnClick([]() { Serial.println("Bouton cliqué!"); });
    
    Serial.begin(115200);
    Serial.println("Bouton prêt. (Mock: auto-clic toutes 3s)");
}

void loop() {
    // Mock focus/click
    static unsigned long lastClick = 0;
    if (millis() - lastClick > 3000) {
        button->setFocus(true);
        button->handleClick();
        button->setFocus(false);
        lastClick = millis();
    }
    
    // Draw
    static unsigned long lastDraw = 0;
    if (millis() - lastDraw > 100) {
        tft.fillScreen(TFT_BLACK);
        button->draw(tft, true);
        lastDraw = millis();
    }
    
    delay(50);
}

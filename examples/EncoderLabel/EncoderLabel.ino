/*
  Exemple simple : UIEncoderLabel
  Démo un label texte contrôlé par encodeur.
*/

#include <TFT_eSPI.h>
#include <U8g2_for_TFT_eSPI.h>
#include "UIEncoderComponent.h"  // Assumé parent lib installée
#include "UIEncoderTextComponent.h"

// Mock encoder (remplacer par vrai pins)
int encoderPos = 0;

// Instance TFT et U8g2
TFT_eSPI tft = TFT_eSPI();
U8g2_for_TFT_eSPI u8f(tft);

// Label exemple (besoin de class concrète comme UIEncoderLabel)
class SimpleLabel : public UIEncoderTextComponent {
public:
    SimpleLabel(U8g2_for_TFT_eSPI& u8f, const UIRect& rect) 
        : UIEncoderTextComponent(u8f, rect, "Label Demo") {}
    
    void drawInternal(TFT_eSPI& tft, bool force) override {
        u8f.setFont(u8g2_font_ncenB10_tr);
        u8f.setForegroundColor(TFT_WHITE);
        u8f.setCursor(rect.x + 5, rect.y + 20);
        u8f.print(getText());
    }
};

SimpleLabel* label;

void setup() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    
    UIRect rect{10, 10, 200, 30};
    label = new SimpleLabel(u8f, rect);
    
    Serial.begin(115200);
    Serial.println("Label Demo prête! Tournez l'encodeur.");
}

void loop() {
    // Mock encoder change
    static int lastPos = 0;
    encoderPos++;
    if (encoderPos != lastPos) {
        label->setTextf("Valeur: %d", encoderPos);
        lastPos = encoderPos;
    }
    
    // Mock draw chaque 100ms
    static unsigned long lastDraw = 0;
    if (millis() - lastDraw > 100) {
        tft.fillScreen(TFT_BLACK);
        label->draw(tft, true);  // Force draw
        lastDraw = millis();
    }
    
    delay(10);
}

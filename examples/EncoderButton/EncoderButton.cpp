#include "EncoderButton.h"
#include <TFT_eSPI.h>

EncoderButton::EncoderButton(U8g2_for_TFT_eSPI&amp; u8f, const UIRect&amp; rect, const String&amp; text)
    : UIEncoderTextComponent(u8f, rect, text), onClick(nullptr) {}

void EncoderButton::handleClick() {
    if (onClick) onClick();
    setTextf("Clic! (%d)", millis() / 1000);
    setDirty(true);
}

void EncoderButton::drawInternal(TFT_eSPI&amp; tft, bool force) {
    uint16_t bg = isFocused() ? TFT_DARKGREY : TFT_BLACK;
    uint16_t border = isFocused() ? TFT_WHITE : TFT_DARKGREY;
    
    tft.fillRect(rect.x, rect.y, rect.w, rect.h, bg);
    tft.drawRect(rect.x, rect.y, rect.w, rect.h, border);
    
    _u8f.setFont(u8g2_font_ncenB10_tr);
    _u8f.setForegroundColor(TFT_WHITE);
    _u8f.setCursor(rect.x + 5, rect.y + 20);
    _u8f.print(getText());
}

#ifndef ENCODERBUTTON_H
#define ENCODERBUTTON_H

#include "UIEncoderTextComponent.h"
#include <functional>

class EncoderButton : public UIEncoderTextComponent {
public:
    using Callback = std::function<void()>;
    
    EncoderButton(U8g2_for_TFT_eSPI&amp; u8f, const UIRect&amp; rect, const String&amp; text);
    void setOnClick(const Callback&amp; cb) { onClick = cb; }
    
    void handleClick() override;

protected:
    void drawInternal(TFT_eSPI&amp; tft, bool force) override;
    
private:
    Callback onClick;
};

#endif

# UIEncoderTextComponent v2.0.0 - Bibliothèque UI pour Arduino/ESP32

[![PlatformIO Registry](https://img.shields.io/badge/platformio-lib-✅-9966FF.svg)](https://registry.platformio.org/libraries/UIEncoderTextComponent)

## Installation

### Via PlatformIO Library Manager
```
pio lib install "UIEncoderTextComponent"
```

### Manuel
1. Clonez le repo : `git clone https://github.com/HAMMOU-UI/UIEncoderTextComponent.git`
2. Copiez dans `lib/` de votre projet.

**Dépendances requises** :
- TFT_eSPI (^2.5.41)
- u8g2 (^2.35.19)
- UIEncoderComponent (lib parent)

## Vue d'ensemble

`UIEncoderTextComponent` est une classe de base C++ abstraite qui fusionne les fonctionnalités de `UIEncoderComponent` et `UITextComponent`. Elle est conçue pour être la fondation de tout composant d'interface utilisateur qui **affiche du texte** et qui est **contrôlé par un encodeur rotatif**.

En héritant de cette classe, un composant concret (comme un bouton ou un label) dispose à la fois de la capacité à gérer et afficher du texte, et de la logique pour interagir via un système de focus et d'événements d'encodeur.

## Hiérarchie

`UIComponent` <|-- `UIEncoderComponent` <|-- `UIEncoderTextComponent`

## Dépendances

- **`UIEncoderComponent`**: La classe de base pour les composants contrôlés par encodeur.
- **`U8g2_for_TFT_eSPI.h`**: Pour le rendu de polices de haute qualité.
- **`Arduino.h`**: Pour la classe `String`.

---

## Définition de la Classe

```cpp
class UIEncoderTextComponent : public UIEncoderComponent {
public:
    // Constructeur
    UIEncoderTextComponent(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text);
    
    // Destructeur
    virtual ~UIEncoderTextComponent() = default;

    // Méthodes pour la manipulation du texte
    virtual void setText(const String& newText);
    virtual const String& getText() const;

protected:
    // Membres protégés
    U8g2_for_TFT_eSPI& _u8f; ///< Référence à l'objet U8g2 pour le rendu des polices.
    String _text;             ///< Le texte du composant.
};
```

---

## Méthodes Publiques

`UIEncoderTextComponent(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text);`
- **Description** : Constructeur de la classe.
- **Paramètres** :
    - `u8f` : Une référence à l'instance de `U8g2_for_TFT_eSPI`.
    - `rect` : Un objet `UIRect` définissant la géométrie du composant.
    - `text` : Le texte initial à afficher.

`virtual void setText(const String& newText);`
- **Description** : Met à jour le texte du composant. Marque le composant comme `dirty` si le texte change, afin de déclencher un redessin.
- **Paramètres** : `newText` - La nouvelle chaîne de caractères.

`virtual const String& getText() const;`
- **Description** : Récupère le texte actuel du composant.
- **Retourne** : Une référence constante (`const String&`) au texte.

*Note : Les méthodes de gestion de l'encodeur (`handleEncoder`, `handleClick`, etc.) et du focus (`setFocus`, `isFocused`) sont héritées de `UIEncoderComponent`.*

---

## Membres Protégés

`U8g2_for_TFT_eSPI& _u8f;`
- **Description** : Référence directe à l'objet de rendu de police, à utiliser dans la méthode `drawInternal` des classes dérivées.

`String _text;`
- **Description** : Le contenu textuel du composant.

---

## Exemple d'Héritage

Voici comment une classe `EncoderButton` pourrait hériter de `UIEncoderTextComponent`.

```cpp
// EncoderButton.h
#include "UIEncoderTextComponent.h"
#include <functional>

class EncoderButton : public UIEncoderTextComponent {
public:
    EncoderButton(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text);

    // Action à exécuter lors du clic
    std::function<void()> onClick;

    // Surcharger le gestionnaire de clic
    void handleClick() override;

protected:
    void drawInternal(TFT_eSPI& tft, bool force) override;
};

// EncoderButton.cpp
#include "EncoderButton.h"

EncoderButton::EncoderButton(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text)
    : UIEncoderTextComponent(u8f, rect, text) {}

void EncoderButton::handleClick() {
    // Si un callback est défini, on l'appelle
    if (onClick) {
        onClick();
    }
}

void EncoderButton::drawInternal(TFT_eSPI& tft, bool force) {
    // Si le bouton a le focus, dessiner un fond différent
    if (isFocused()) {
        tft.fillRect(rect.x, rect.y, rect.w, rect.h, TFT_DARKGREY);
        tft.drawRect(rect.x, rect.y, rect.w, rect.h, TFT_WHITE);
    } else {
        tft.fillRect(rect.x, rect.y, rect.w, rect.h, TFT_BLACK);
        tft.drawRect(rect.x, rect.y, rect.w, rect.h, TFT_DARKGREY);
    }

    // Dessiner le texte
    _u8f.setFont(u8g2_font_ncenB10_tr);
    _u8f.setForegroundColor(TFT_WHITE);
    _u8f.setCursor(rect.x + 5, rect.y + 15);
    _u8f.print(getText());
}
```

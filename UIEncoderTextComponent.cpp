/**
 * @file UIEncoderTextComponent.cpp
 * @brief Implémentation de la classe UIEncoderTextComponent.
 * @date 2024-07-15
 */

#include "UIEncoderTextComponent.h"
#include <cstdarg> // Pour va_list, va_start, va_end

/**
 * @brief Constructeur de UIEncoderTextComponent.
 * @details Initialise le composant de base `UIEncoderComponent` avec le rectangle fourni,
 *          et stocke les références vers le moteur de polices et le texte initial.
 *
 * @param u8f Référence à l'objet U8g2_for_TFT_eSPI pour le rendu des polices.
 * @param rect Le rectangle définissant la position et les dimensions du composant.
 * @param text Le texte initial du composant.
 */
UIEncoderTextComponent::UIEncoderTextComponent(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text)
    : UIEncoderComponent(rect), _u8f(u8f), _text(text) {
    // Le corps du constructeur est vide car tout est fait dans la liste d'initialisation.
}

/**
 * @brief Modifie le texte du composant.
 * @details C'est une implémentation cruciale pour l'efficacité de l'interface.
 *          Le texte n'est modifié et le composant n'est marqué comme "dirty" (à redessiner)
 *          que si le nouveau texte est réellement différent de l'ancien. Cela évite
 *          des redessins inutiles si on appelle `setText` plusieurs fois avec la même valeur.
 *
 * @param newText Le nouveau texte à afficher.
 */
void UIEncoderTextComponent::setText(const String& newText) {
    if (_text != newText) {
        _text = newText;
        setDirty(true); // Marquer le composant comme nécessitant un redessin
    }
}

/**
 * @brief Récupère le texte actuel du composant.
 * @details Retourne une référence constante pour éviter de copier la chaîne de caractères,
 *          ce qui est plus efficace en termes de mémoire et de vitesse.
 *
 * @return const String& Une référence constante vers le texte.
 */
const String& UIEncoderTextComponent::getText() const {
    return _text;
}

/**
 * @brief Modifie le texte du composant en utilisant un formatage de type printf.
 * @details Cette fonction utilise les macros `va_list`, `va_start`, et `va_end` pour gérer
 *          un nombre variable d'arguments, tout comme le ferait `printf`.
 *          Elle formate la chaîne dans un tampon temporaire, puis appelle `setText()`
 *          pour effectuer la mise à jour, ce qui garantit que la logique du "dirty flag"
 *          est également appliquée ici.
 * 
 * @param format La chaîne de format (ex: "Valeur: %d").
 * @param ... Les arguments variables correspondant au format.
 */
void UIEncoderTextComponent::setTextf(const char* format, ...) {
    char buffer[256]; // Tampon pour la chaîne formatée. Assez grand pour la plupart des usages.
    va_list args;
    va_start(args, format);
    // vsnprintf est une version sécurisée de vsprintf qui évite les débordements de tampon.
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    // Réutilise la méthode setText pour mettre à jour le texte et gérer le dirty flag.
    setText(String(buffer));
}
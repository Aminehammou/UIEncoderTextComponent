#ifndef UIENCODERTEXTCOMPONENT_H
#define UIENCODERTEXTCOMPONENT_H

#include "UIEncoderComponent.h"
#include "U8g2_for_TFT_eSPI.h"
#include <Arduino.h> // Pour la classe String

/**
 * @class UIEncoderTextComponent
 * @brief Classe de base abstraite pour les composants qui affichent du texte.
 * @version 2.0
 * @date 2024-07-15
 *
 * @details
 * ### Rôle et Philosophie
 * `UIEncoderTextComponent` est une sous-classe de `UIEncoderComponent`.
 * Elle sert de "modèle" pour tous les autres composants qui ont besoin d'afficher du texte
 * (labels, boutons, etc.).
 *
 * Elle ne peut pas être utilisée directement car elle est **abstraite**. Cela signifie qu'elle
 * fournit des fonctionnalités de base, mais qu'il manque encore des pièces.
 * Concrètement, elle ne dit pas **comment** dessiner le texte. C'est aux classes qui en héritent
 * (comme `UIEncoderLabel`) de le faire en implémentant la méthode `drawInternal()`.
 *
 * ### Concepts Clés pour les Débutants
 *
 * 1.  **Héritage à deux niveaux :** La hiérarchie est la suivante :
 *     `UIEncoderComponent` (gère la position, le focus, l'état "dirty")
 *       -> `UIEncoderTextComponent` (ajoute la gestion du texte et des polices)
 *         -> `UIEncoderLabel` (implémente `drawInternal` pour dessiner le texte)
 *
 * 2.  **Gestion du Texte :** Cette classe ajoute un membre `String _text` et des méthodes
 *     comme `setText()` et `getText()` pour le manipuler. L'avantage est que tous les composants
 *     à base de texte auront une interface cohérente.
 *
 * 3.  **Moteur de Polices U8g2 :** Elle intègre une référence à `U8g2_for_TFT_eSPI` (`_u8f`).
 *     Cela permet d'utiliser des polices de caractères avancées (différentes tailles, styles...)
 *     de manière unifiée dans tous les composants texte.
 */
class UIEncoderTextComponent : public UIEncoderComponent {
public:
    /**
     * @brief Constructeur de UIEncoderTextComponent.
     *
     * @param u8f Référence à l'objet U8g2_for_TFT_eSPI. Cet objet est partagé par tous les
     *            composants et gère le rendu des polices de caractères.
     * @param rect Le rectangle définissant la position et les dimensions du composant.
     * @param text Le texte initial à afficher.
     */
    UIEncoderTextComponent(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text);

    /**
     * @brief Destructeur virtuel par défaut.
     */
    virtual ~UIEncoderTextComponent() = default;

    // --- Méthodes pour la manipulation du texte ---

    /**
     * @brief Modifie le texte du composant.
     * @details Si le nouveau texte est différent de l'ancien, il met à jour le texte interne
     *          et appelle automatiquement `setDirty(true)` pour que le composant soit redessiné.
     * @param newText Le nouveau texte à afficher.
     */
    virtual void setText(const String& newText);

    /**
     * @brief Récupère le texte actuel du composant.
     * @return Une référence constante vers le texte (`const String&`).
     */
    virtual const String& getText() const;

    /**
     * @brief Modifie le texte en utilisant un formatage de type `printf`.
     * @details C'est une méthode pratique pour construire des chaînes de caractères complexes
     *          sans avoir à faire la concaténation manuellement.
     * @param format La chaîne de format (ex: "Temp: %.1f C").
     * @param ... Les arguments variables correspondant au format (ex: une variable `float`).
     * @note La taille finale de la chaîne est limitée à 255 caractères pour des raisons de performance.
     * @code
     *   // Exemple d'utilisation
     *   float temperature = 23.5;
     *   myLabel->setTextf("Temp: %.1f C", temperature);
     * @endcode
     */
    void setTextf(const char* format, ...);

protected:
    /// @brief Référence au moteur de rendu de polices U8g2, partagé par tous les composants.
    U8g2_for_TFT_eSPI& _u8f;
    
    /// @brief Le contenu textuel du composant.
    String _text;
};

#endif // UIENCODERTEXTCOMPONENT_H
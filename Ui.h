#ifndef UI
#define UI
#include <string>
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>
#include "UiStyle.h"
#include "UiEntry.h"

class Ui: public sf::Transformable, public sf::Drawable {
private:    
    bool horizontal;            // If true the menu entries will be horizontally, not vertically, adjacent
    const bool highlightable;         // if true entry changes color, when mouse is ove it
    UiStyle style;              // Style of UI element
    sf::Vector2f dimensions;    // Size of UI element
    int padding;                // distance between text and borders to prevent overlapping

public:
    std::vector<UiEntry> entries;

    bool visible;

    // Constructor: 
    // dimensions - size of UI element;
    // padding - distance between text and borders to prevent overlapping;
    // horizontal - true if UI elements are horizontally aligned;
    // style - UI style of elements;
    // entries - pair of strings, first is text displayed on UI entry, second - message, that entry returns
    Ui(sf::Vector2f dimensions, int padding, bool horizontal, bool highlightable, UiStyle& style, std::vector<std::pair<std::string, std::string>> entries);

    // Returns the total dimensions of the UI as sum of its elements
    sf::Vector2f getSize();

    // Return the entry that the mouse is hovering over. Returns
    // -1 if the mouse if outside of the GUI 
    int getEntry(const sf::Vector2f mousePos);

    // Change the text of an entry.
    void setEntryText(int entry, std::string text);

    // Change the entry dimensions.
    void setDimensions(sf::Vector2f dimensions);

    // Draw the UI.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void show();

    void hide();

    bool is_highlightable() const;

    // Highlights an entry of the menu.
    void highlight(const int entry);

    // Return the message bound to the entry.
    std::string activate(const int entry);
    std::string activate(const sf::Vector2f mousePos);
};

#endif
#ifndef DYN_UI
#define DYN_UI
#include <string>
#include <SFML/Graphics.hpp>
#include "UiEntry.h"
#include "UiStyle.h"

class DynamicUi {
    UiEntry entry;

    // style of the entry
    UiStyle style;
    // Size of UI element
    sf::Vector2f dimensions;
    // distance between text and borders to prevent overlapping
    int padding;                
    // position of top left corner of the entry
    sf::Vector2i position;

	bool visible;
public:
    // constructor
    DynamicUi(int padding, UiStyle& style, std::pair<std::string, std::string> entry);
    // default constructor
    DynamicUi() { }
    // sets position of entry to pos
    void set_position(sf::Vector2f pos);
    // show UI entry
    void show();
    // hide UI entry
    void hide();
    // Returns 1 if mouse is hovering over. Returns
    // -1 if the mouse if outside of the GUI
    bool isMouseOver(const sf::Vector2f mousePos);
    // highlights the entry
    void highlight(const bool mouseover);
    // returns message of an entry
    std::string activate(const sf::Vector2f mousePos);

    // draw entry
    void draw(sf::RenderWindow& w) const;
};

#endif
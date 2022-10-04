#pragma once
#include <string>
#include <utility>
#include <vector>
#include <SFML/Graphics.hpp>

class UiStyle
{
public:

    sf::Color bodyCol;              // body color of entry
    sf::Color bodyHighlightCol;     // body color of entry if highlited
    sf::Color borderCol;            // border color of entry
    sf::Color borderHighlightCol;   // border color of entry if highlighted
    sf::Color textCol;              // text color of text in entry
    sf::Color textHighlightCol;     // text color of text in entry if highlighted
    sf::Font* font;                 // pointer to font used

    float borderSize;               // border width

    //constructor
    UiStyle(sf::Font* font, float borderSize,
        sf::Color bodyCol, sf::Color borderCol, sf::Color textCol,
        sf::Color bodyHighlightCol, sf::Color borderHighlightCol, sf::Color textHighlightCol)
    {
        this->bodyCol = bodyCol;
        this->borderCol = borderCol;
        this->textCol = textCol;
        this->bodyHighlightCol = bodyHighlightCol;
        this->borderHighlightCol = borderHighlightCol;
        this->textHighlightCol = textHighlightCol;
        this->font = font;
        this->borderSize = borderSize;
    }
    UiStyle() { }
};

class UiEntry
{
public:

    // Handles appearance of the entry
    sf::RectangleShape shape;

    // String returned when the entry is activated
    std::string message;

    // Text displayed on the entry
    sf::Text text;

    UiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text)
    {
        this->message = message;
        this->shape = shape;
        this->text = text;
    }
    UiEntry() { }
};

class Ui: public sf::Transformable, public sf::Drawable {
private:    
    bool horizontal;            // If true the menu entries will be horizontally, not vertically, adjacent
    UiStyle style;              // Style of UI element
    sf::Vector2f dimensions;    // Size of UI element
    int padding;                // distance between text and borders to prevent overlapping

public:
    std::vector<UiEntry> entries;

    bool visible;

    // Constructor
    Ui(sf::Vector2f dimensions, int padding, bool horizontal, UiStyle& style, std::vector<std::pair<std::string, std::string>> entries);

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

    // Highlights an entry of the menu.
    void highlight(const int entry);

    // Return the message bound to the entry.
    std::string activate(const int entry);
    std::string activate(const sf::Vector2f mousePos);
};
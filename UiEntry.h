#ifndef UI_ENTRY
#define UI_ENTRY
#include <string>
#include "UiStyle.h"
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

#endif
#ifndef  UI_STYLE
#define UI_STYLE
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

#endif
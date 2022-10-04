#include "Ui.h"

Ui::Ui(sf::Vector2f dimensions, int padding, bool horizontal,
    UiStyle& style, std::vector<std::pair<std::string, std::string>> entries) {
    visible = false;
    this->horizontal = horizontal;
    this->style = style;
    this->dimensions = dimensions;
    this->padding = padding;

    // Construct the background shape
    sf::RectangleShape shape;
    shape.setSize(dimensions);
    shape.setFillColor(style.bodyCol);
    shape.setOutlineThickness(-style.borderSize);
    shape.setOutlineColor(style.borderCol);

    // Construct each gui entry
    for (auto entry : entries)
    {
        // Construct the text
        sf::Text text;
        text.setString(entry.first);
        text.setFont(*style.font);
        text.setFillColor(style.textCol);
        text.setCharacterSize(dimensions.y - style.borderSize - padding);

        this->entries.push_back(UiEntry(entry.second, shape, text));
    }
}

sf::Vector2f Ui::getSize() {
    if (horizontal)
        return sf::Vector2f(this->dimensions.x * this->entries.size(), this->dimensions.y ); // if menu is horizontally adjacent
    else
        return sf::Vector2f(this->dimensions.x, this->dimensions.y * this->entries.size());  // if menu is vetrically adjacent
}

int Ui::getEntry(const sf::Vector2f mousePos) {
    // If there are no entries then outside the menu.
    if (entries.size() == 0) 
        return -1;
    if (!this->visible) 
        return -1;

    for (int i = 0; i < this->entries.size(); ++i)
    {
        // Translate point to use the entry's local coordinates.
        sf::Vector2f point = mousePos;
        point += this->entries[i].shape.getOrigin();
        point -= this->entries[i].shape.getPosition();
        // if pointer is not in shape coordinates in one of the axis, going to the next shape, else returns its index
        if (point.x < 0 || point.x > this->entries[i].shape.getScale().x * this->dimensions.x) continue;
        if (point.y < 0 || point.y > this->entries[i].shape.getScale().y * this->dimensions.y) continue;
        return i;
    }
    return -1;
}

void Ui::setEntryText(int entry, std::string text) {
    if (entry >= entries.size() || entry < 0)
        return;
    entries[entry].text.setString(text);
}

void Ui::setDimensions(sf::Vector2f dimensions) {
    this->dimensions = dimensions;
    for (auto& entry : entries)             
    {
        entry.shape.setSize(dimensions);                                   // change dimensions of each entry in the UI
        entry.text.setCharacterSize(dimensions.y - style.borderSize - padding); // changing text size to prevent ovelapping with new dimensions
    }
}

void Ui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // if ui is not visible, draw nothing
    if (!visible)
        return;
    // Draw each entry of the menu.
    for (auto entry : this->entries)
    {
        // Draw the entry.
        target.draw(entry.shape);
        target.draw(entry.text);
    }
}

void Ui::show()
{
    sf::Vector2f offset(0.0f, 0.0f);    // offset of next UI entry from previous one

    this->visible = true;

    // For each entry of the menu.
    for (auto& entry : this->entries)
    {
        // Set the origin of the entry 
        sf::Vector2f origin = this->getOrigin();    // get currnet origin
        origin -= offset;                           // modify it by offset, so if UI is vertically aligned next entry will be lower than current
        entry.shape.setOrigin(origin);              // use modified origin as new one for current entry
        entry.text.setOrigin(origin);

        // Compute the position of the entry.
        entry.shape.setPosition(this->getPosition());
        entry.text.setPosition(this->getPosition());

        if (this->horizontal) 
            offset.x += this->dimensions.x;         // if UI is horizontal modify offset by x size of UI dimensions, so next entry will
        else                                        // be placed to the right of the current one
            offset.y += this->dimensions.y;         // if UI is vertical modify offset by y size of UI dimensions, so next entry will
    }                                               // be placed below of the current one
}

void Ui::hide()
{
    this->visible = false;
}

void Ui::highlight(const int entry)
{
    for (int i = 0; i < entries.size(); ++i)
    {
        if (i == entry)
        {
            entries[i].shape.setFillColor(style.bodyHighlightCol);
            entries[i].shape.setOutlineColor(style.borderHighlightCol);
            entries[i].text.setFillColor(style.textHighlightCol);
        }
        else
        {
            entries[i].shape.setFillColor(style.bodyCol);
            entries[i].shape.setOutlineColor(style.borderCol);
            entries[i].text.setFillColor(style.textCol);
        }
    }
}

// Return the message bound to the entry.
std::string Ui::activate(const int entry)
{
    if (entry == -1) return "null";
    return entries[entry].message;
}

std::string Ui::activate(sf::Vector2f mousePos)
{
    int entry = this->getEntry(mousePos);
    return this->activate(entry);
}
#ifndef ENGINE
#define ENGINE

#include <stack>
#include <SFML/Graphics.hpp>
#include "RandomNumberGenerator.h"
#include "GalacticFactory.h"
#include "State.h"
#include "Ui.h"
#include "utility.h"
#include "GraphicsHandler.h"

class State;
class GalacticFactory;
class RandomNumberGenerator;

class Engine
{
public:
    std::stack <State*> states;
    sf::RenderWindow window; //window, to which everything is rendered
    GraphicsHandler graphics_handler;
    std::map<std::string, UiStyle> styles;
    std::map<std::string, sf::Font> fonts;
    RandomNumberGenerator* rng;

    //constructor, creates necessary variables and simulatable objects
    Engine();
    //destructor
    ~Engine();
    // loads fonts from files
    void load_fonts();
    // loads UI styles
    void load_styles();
    //adds state on top of state stack
    void push_state(State* state);
    //removes top state from state stack
    void pop_state();
    //changes state on top of the state stack
    void change_state(State* state);
    //returns whatever state is on top of state stack
    State* peek_state();

    //starts engines's working cycle
    void run();
};
#endif
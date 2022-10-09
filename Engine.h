#ifndef ENGINE
#define ENGINE

#include <stack>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Ui.h"
#include "utility.h"
#include "GraphicsHandler.h"

class State;

class Engine
{
public:
    std::stack <State*> states;
    sf::RenderWindow window; //window, to which everything is rendered
    GraphicsHandler graphics_handler;
    std::map<std::string, UiStyle> styles;
    std::map<std::string, sf::Font> fonts;

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
    //creates shapes (T0D0: some way for shape creation that is connected to objects in simulation and not by hand, but automatically)
    void create_shapes();

    //starts engines's working cycle
    void run();
};
#endif
#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Camera.h"
#include "SolarSystem.h"
#include "PlanetSystem.h"
#include "planet.h"
class State;
class Engine
{
public:
    std::stack <State*> states;
    sf::RenderWindow window; //window, to which everything is rendered
    Camera cam;                // player camera
    sf::Font font;             //font used to print text to window
    sf::Text text;             //text printed to window
    bool cameraMoving = false; // variable that is true, when camera is moving by mouse
    bool following = false;    // variable that is true, when camera is following some object
    sf::Vector2f oldPos;       // variable, that stores old mouse pointer position
    sf::Vector2f pointerPos;   // current pointer position
    SolarSystem* focus_sol;    // focused on solar system
    PlanetSystem* focus_system;// focused on planet system
    Planet* focus_planet;      // focused on planet


    //constructor, creates necessary variables and simulatable objects
    Engine();
    //destructor
    ~Engine();
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


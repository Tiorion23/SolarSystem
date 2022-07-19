#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "SolarSystem.h"
#include "PlanetSystem.h"
#include "planet.h"
class Engine
{
    //переменные для графической части движка
    sf::RenderWindow m_Window; //window, to which everything is rendered
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

public:
    //constructor, creates necessary variables and simulatable objects
    Engine();
    //starts working cycle with simulation
    void run();
};


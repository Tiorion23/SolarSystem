#include <SFML/Graphics.hpp>
#include "utility.h"
#include "planet.h"
#include "PlanetSystem.h"
#include "SolarSystem.h"
#include "Vectorld2d.h"
#include "Camera.h"
#include <iostream>
#include <iomanip>
#include <math.h>


int main()
{
    unsigned long long int time = 0; // number of simulated seconds
    int sim;
    int step;
    while (true) {
        std::cout << "Define simulation time in days, enter 0 for endless simulation ";
        std::cin >> sim;
        if (sim < 0) {
            std::cout << "Error! Number must be positive!\n";
        }
        else
            break;
    }
    while (true) {
        std::cout << "Define simulation step in minutes, enter 0 for 1-second step ";
        std::cin >> step;
        if (step < 0) {
            std::cout << "Error! Number must be positive!\n";
        }
        else if (step == 0) {
            step = 1;
            break;
        }
        else {
            step = step * 60;
            break;
        }
            
    }
    sim = sim * 24 * 60 * 60;
    sf::Color orange(255, 165, 0, 255);
    //std::cout << std::setprecision(16); 
    PlanetSystem* sun = new PlanetSystem(std::vector<Planet*> {
        new Planet("Sun", 1.392e9, 1.989e30, 0, 0, Vectorld2d(0, 0), sf::Color::Yellow, 1.392e9/2)}, // creating planet for system 
        0, 0, Vectorld2d(0, 0)); // coordinates and speed of system
    PlanetSystem* smercury = new PlanetSystem(std::vector<Planet*> {
        new Planet("Mercury", 4.8794e6, 3.33022e23, 0, 0, Vectorld2d(0, 0), sf::Color::Magenta, 4.8794e6/2*100)},// creating planet for system
        -57909227000, 0, Vectorld2d(0, -47360)); // coordinates and speed of system
    PlanetSystem* svenus = new PlanetSystem(std::vector<Planet*> {
        new Planet("Venus", 1.21036e7, 4.8675e24, 0, 0, Vectorld2d(0, 0), sf::Color::Green, 1.21036e7/2*100)}, // creating planet for system
        -108942109000, 0, Vectorld2d(0, -35020)); // coordinates and speed of system
    PlanetSystem* earth_moon = new PlanetSystem(std::vector<Planet*> {
        new Planet("Earth", 1.2742e7, 5.972e24, 0, 0, Vectorld2d(0, 0), sf::Color::Blue, 1.2742e7/2*100), // creating planet for system
            new Planet("Moon", 3.47628e6, 7.3477e22, 406700000, 0, Vectorld2d(0, 1023), sf::Color::White, 3.47628e6/2*100)}, // creating planet for system
        149597870700, 0, Vectorld2d(0, 29999.99999999941)); // coordinates and speed of system
    PlanetSystem* mars = new PlanetSystem(std::vector <Planet*> {
        new Planet("Mars", 6.779e6, 6.4171e23, 0, 0, Vectorld2d(0, 0), sf::Color::Red, 6.779e6/2*100),
            new Planet("Phobos", 2.25e4, 1.072e16, 9.3772e6, 0, Vectorld2d(2138.45, 0), sf::Color::Cyan, 2.25e4/2*100),
            new Planet("Deimos", 1.24e4, 1.48e15, 2.3458e7, 0, Vectorld2d(1351.28, 0), sf::Color(100, 100, 100, 255), 1.24e4/2*100)},
        2.2794382e11, 0, Vectorld2d(0, 24130));
    PlanetSystem* jupiter = new PlanetSystem(std::vector<Planet*> {
        new Planet("Jupiter", 69.911e6, 1.8986e27, 0, 0, Vectorld2d(0, 0), orange, 69.911e6/2*10)},
        7.785472e11, 0, Vectorld2d(0, 13070));
    SolarSystem* sol = new SolarSystem(std::vector <PlanetSystem*> { sun, smercury, svenus, earth_moon, mars, jupiter }, 
        0, 0, Vectorld2d(0, 0));
    
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text info;
    info.setFont(font);
    info.setPosition(0, 0);
    info.setCharacterSize(12);
    info.setFillColor(sf::Color::White);

    bool cameraMoving = false;  // variable that is true, when camera is moving by mouse
    bool following = false;     // variable that is true, when camera is following some object
    sf::Vector2i oldPos;       // variable, that stores old mouse pointer position "in window" coords
    sf::Vector2i pointerPos;    // variable, that stores current mouse pointer position "in window" coords
    SolarSystem* focus_sol = nullptr; // followed solar system
    PlanetSystem* focus_system = nullptr; // followed planetary system
    Planet* focus_planet = nullptr; // followed planet
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Solar System");    // creating window 
    //window.setVerticalSyncEnabled(true);
    Camera* cam = new Camera({ float(sun->get_global_x()), float(sun->get_global_y())}, sf::Vector2f(window.getSize())); //camera focuses on Sun
    window.setView(cam->getView());    
    
    //simulation for planetary systems
    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // X button on window pressed, window closes
            case sf::Event::Closed:
                window.close();  break; 
            //window is resized
            case sf::Event::Resized:
                cam->resize(event.size.width, event.size.height);                
                break;
            case sf::Event::MouseWheelScrolled: // zoom in and out by mousewheel
                if (event.mouseWheelScroll.delta > 0) { //wheel up - zoom in
                    cam->rescale(0.8);
                }                    
                else if (event.mouseWheelScroll.delta < 0) { //wheel down - zoom out
                   cam->rescale(1.2);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    pointerPos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y); //taking pointer position "in window" coordinates
                    if (!cameraMoving) { //working camera moving code
                        cameraMoving = true;
                        std::cout << "cameraMoving = " << cameraMoving << " x0 = " << pointerPos.x << " y0 = " << pointerPos.y << "\n";
                        //std::cout << "current view center " << " x1 = " << cam->getView().getCenter().x << " y1 = " << cam->getView().getCenter().y << "\n";
                        oldPos = pointerPos;
                    }
                }
                break;                
            case sf::Event::MouseButtonReleased: // mouse button released, map cant be moved now
                if (event.mouseButton.button == 0)
                {
                    cameraMoving = false;
                    std::cout << "cameraMoving = " << cameraMoving << " x1 = " << oldPos.x << " y1 = " << oldPos.y << "\n";
                    std::cout << "new view center " << " x1 = " << cam->getView().getCenter().x << " y1 = " << cam->getView().getCenter().y << "\n";
                }
                break;
            case sf::Event::MouseMoved: //if mouse button pressed map cn be moved                
                if (!cameraMoving) { //if mouse button isnt pressed (camera isnt moving) do nothing
                   /* const sf::Vector2i newPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);  //debugging code
                    for (const auto& ps : sol->get_systems()) {
                        for (const auto& p: ps->get_planets())
                            std::cout << "x=" << window.mapPixelToCoords(newPos).x << " y=" << window.mapPixelToCoords(newPos).y << " mouseover=" << ps->is_clicked(window.mapPixelToCoords(newPos)) << '\n';
                    }*/
                    break;
                }                    
                //defining pointer position "in window" coordinates
                const sf::Vector2i newPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                cam->move(oldPos, newPos);
                //saving new position as old one
                oldPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // resets to default view and scale
            {
                cam->reset();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) // increasing size of shapes of all planets
            {
                sol->resize_shapes(2);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) // decreasing size of shapes of all planets
            {
                sol->resize_shapes(0.5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // closes window on Esc pressed
            {
                window.close();
            }
        }        
        if (sim == 0) {
            info.setString(utility::timer(time) + utility::info(sol->get_systems()));
            sol->simulate(step);
            window.setView(window.getDefaultView());
            window.draw(info);
            if (following) {
                cam->setView(sf::Vector2f(focus_system->get_global_x(), focus_system->get_global_y()), cam->getView().getSize());
                window.setView(cam->getView());
            }
            else
                window.setView(cam->getView());
            sol->draw_system(window);
            window.display();
            time += step;
        }
        else if (sim > 0) {
            info.setString(utility::timer(time) + utility::info(sol->get_systems()));
            sol->simulate(step);
            window.setView(window.getDefaultView());
            window.draw(info);
            if (following) {
                cam->setView(sf::Vector2f(focus_system->get_global_x(), focus_system->get_global_y()), cam->getView().getSize());
                window.setView(cam->getView());
            }
            else
                window.setView(cam->getView());
            sol->draw_system(window);
            window.display();
            time += step;
            if (time == sim)
                break;
        }
    }    
    return 0;
}
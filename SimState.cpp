#include "SimState.h"

SimState::SimState(Engine* engine) {
	this->engine = engine;
    this->engine->create_shapes();
	sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
	sim_view.setSize(pos);
	ui_view.setSize(pos);
	ui_view.setCenter(pos * 0.5f);    
    default_scale = 100000000.f;
    scale = 1.f;
    sol = initialize_solar_system();    
    sim_view.setCenter(this->sol->get_systems()[0]->get_global_coords().x, this->sol->get_systems()[0]->get_global_coords().y);
    sim_view.zoom(scale *= default_scale);
    action_state = ActionState::NONE;
    simulation_state = SimulationState::RUNNING;
    time = 0;
    simulation_speed.emplace(SimulationState::RUNNING, 1);
    simulation_speed.emplace(SimulationState::PAUSED, 0);
    initialize_ui();
}

SimState::~SimState() {
    for (auto a : sol->get_systems()) {
        for (auto b : a->get_planets())
            delete b;
        delete a;
    }
    delete sol;
}

SolarSystem* SimState::initialize_solar_system() {
    PlanetSystem* sun = new PlanetSystem(std::vector<CosmicBody*> {
        new CosmicBody(CosmicBodyType::STAR, "Sun", 1.392e9, 1.989e30, 0, 0, Vectorld2d(0, 0), this->engine->graphics_handler.get_shapes_manager().get_shape("Sun"))}, // creating planet for system 
        0, 0, Vectorld2d(0, 0)); // coordinates and speed of system
    PlanetSystem* smercury = new PlanetSystem(std::vector<CosmicBody*> {
        new CosmicBody(CosmicBodyType::PLANET, "Mercury", 4.8794e6, 3.33022e23, 0, 0, Vectorld2d(0, 0), this->engine->graphics_handler.get_shapes_manager().get_shape("Mercury"))},// creating planet for system
        -5.7909227e10, 0, Vectorld2d(0, -47360)); // coordinates and speed of system
    PlanetSystem* svenus = new PlanetSystem(std::vector<CosmicBody*> {
        new CosmicBody(CosmicBodyType::PLANET, "Venus", 1.21036e7, 4.8675e24, 0, 0, Vectorld2d(0, 0), this->engine->graphics_handler.get_shapes_manager().get_shape("Venus"))}, // creating planet for system
        -1.08942109e11, 0, Vectorld2d(0, -35020)); // coordinates and speed of system
    PlanetSystem* earth_moon = new PlanetSystem(std::vector<CosmicBody*> {
        new CosmicBody(CosmicBodyType::PLANET, "Earth", 1.2742e7, 5.972e24, 0, 0, Vectorld2d(0, 0), this->engine->graphics_handler.get_shapes_manager().get_shape("Earth")), // creating planet for system
            new CosmicBody(CosmicBodyType::SATELLITE, "Moon", 3.47628e6, 7.3477e22, 4.067e8, 0, Vectorld2d(0, 1023), this->engine->graphics_handler.get_shapes_manager().get_shape("Moon"))}, // creating planet for system
        1.495978707e11, 0, Vectorld2d(0, 29999.99999999941)); // coordinates and speed of system
    PlanetSystem* mars = new PlanetSystem(std::vector <CosmicBody*> {
        new CosmicBody(CosmicBodyType::PLANET, "Mars", 6.779e6, 6.4171e23, 0, 0, Vectorld2d(0, 0), this->engine->graphics_handler.get_shapes_manager().get_shape("Mars")),
            new CosmicBody(CosmicBodyType::SATELLITE, "Phobos", 2.25e4, 1.072e16, 9.3772e6, 0, Vectorld2d(0, 2138.45), this->engine->graphics_handler.get_shapes_manager().get_shape("Phobos")),
            new CosmicBody(CosmicBodyType::SATELLITE, "Deimos", 1.24e4, 1.48e15, 2.3458e7, 0, Vectorld2d(0, 1351.28), this->engine->graphics_handler.get_shapes_manager().get_shape("Deimos"))},
        2.2794382e11, 0, Vectorld2d(0, 24130));
    PlanetSystem* jupiter = new PlanetSystem(std::vector<CosmicBody*> {
        new CosmicBody(CosmicBodyType::PLANET, "Jupiter", 69.911e6, 1.8986e27, 0, 0, Vectorld2d(0, 0), this->engine->graphics_handler.get_shapes_manager().get_shape("Jupiter")),
            new CosmicBody(CosmicBodyType::SATELLITE, "Io", 3.6426e4, 8.9319e22, 4.217e8, 0, Vectorld2d(0, 17334), this->engine->graphics_handler.get_shapes_manager().get_shape("Io")),
            new CosmicBody(CosmicBodyType::SATELLITE, "Europa", 3.1216e4, 4.8017e22, -6.711e8, 0, Vectorld2d(0, 13740), this->engine->graphics_handler.get_shapes_manager().get_shape("Europa")),
            new CosmicBody(CosmicBodyType::SATELLITE, "Hanimedes", 5.2682e4, 1.4819e23, 1.0704e9, 0, Vectorld2d(0, 10880), this->engine->graphics_handler.get_shapes_manager().get_shape("Hanimedes")),
            new CosmicBody(CosmicBodyType::SATELLITE, "Kallisto", 4.8206e4, 1.075e23, -1.8827e9, 0, Vectorld2d(0, 8204), this->engine->graphics_handler.get_shapes_manager().get_shape("Kallisto"))},
        7.785472e11, 0, Vectorld2d(0, 13070));
    SolarSystem* sol = new SolarSystem(std::vector <PlanetSystem*> { sun, smercury, svenus, earth_moon, mars, jupiter },
        0, 0, Vectorld2d(0, 0));
    return sol;
}

void SimState::initialize_ui() {    // creating statically placed UI elements
    this->static_ui_system.emplace("speed_controls", Ui(sf::Vector2f(32, 32), 4, true, engine->styles.at("button"),
        { std::make_pair("+", "increase_sim_speed"),
        std::make_pair("II", "pause/resume"),
        std::make_pair("-", "decrease_sim_speed") }));
    this->static_ui_system.at("speed_controls").setPosition(this->engine->window.getSize().x - this->static_ui_system.at("speed_controls").getSize().x, this->engine->window.getSize().y - 32);
    this->static_ui_system.at("speed_controls").show();

    this->static_ui_system.emplace("timer", 
        Ui(sf::Vector2f(this->engine->window.getSize().x - this->static_ui_system.at("speed_controls").getSize().x, 32), 
            4, true, engine->styles.at("panel"),
        { std::make_pair(utility::timer(time), "timer") }));
    this->static_ui_system.at("timer").setPosition(sf::Vector2f(0.f, this->engine->window.getSize().y - 32));
    this->static_ui_system.at("timer").show();

    this->static_ui_system.emplace("menu_button", Ui(sf::Vector2f(96, 32), 4, true, engine->styles.at("button"),
        { std::make_pair("Menu", "menu_button") }));
    this->static_ui_system.at("menu_button").setPosition(0, 0);
    this->static_ui_system.at("menu_button").show();
    // cycling through all planets in solar system to create corresponding nameplates
    for (auto a : sol->get_systems())
        for (auto b : a->get_planets()) {
            this->dynamic_ui_system.emplace(b->get_name(), DynamicUi(2, engine->styles.at("nameplates"),
                std::make_pair(b->get_name(), b->get_name())));
            sf::Vector2i pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(b->get_global_coords().x + b->get_diameter() / 2,
                b->get_global_coords().y + b->get_diameter() / 2), sim_view);
            this->dynamic_ui_system.at(b->get_name()).set_position(this->engine->window.mapPixelToCoords(pos, ui_view));
            // hiding nameplates for satellites to lessen clutter
            if (b->get_type() == CosmicBodyType::STAR || b->get_type() == CosmicBodyType::PLANET) {
                this->dynamic_ui_system.at(b->get_name()).show();
            }
        }
}

void SimState::handle_input() {
    sf::Event event;
    pointerPos = sf::Mouse::getPosition(this->engine->window); //taking pointer position "in window" coordinates
    while (this->engine->window.pollEvent(event)) {        
        switch (event.type) {
            // X button on window pressed, window closes
        case sf::Event::Closed:
            this->engine->window.close();  break;
            //window is resized
        case sf::Event::Resized: {
            this->sim_view.setSize(event.size.width, event.size.height);        // changing simulation view size to fit new window size
            this->sim_view.zoom(scale);                                   // rescaling simulation view back to previous scale
            this->ui_view.setSize(event.size.width, event.size.height);         // changing UI view size to fit new window size
            sf::Vector2f pos = sf::Vector2f(0.f, event.size.height - 32);       // position of static UI elements in window coordinates
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->ui_view);  // translation to UI view coordinates
            // resizing and putting UI elements to new positions
            this->static_ui_system.at("timer").setDimensions(sf::Vector2f(event.size.width - this->static_ui_system.at("speed_controls").getSize().x, 32));
            this->static_ui_system.at("timer").setPosition(pos);
            this->static_ui_system.at("timer").show();
            pos = sf::Vector2f(this->static_ui_system.at("timer").getSize().x, event.size.height - 32);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->ui_view);
            this->static_ui_system.at("speed_controls").setPosition(pos);
            this->static_ui_system.at("speed_controls").show();
            pos = sf::Vector2f(0.f, 0.f);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->ui_view);
            this->static_ui_system.at("menu_button").setPosition(pos);
            this->static_ui_system.at("menu_button").show();
            break; 
        }
        case sf::Event::MouseWheelScrolled: // zoom in and out by mousewheel
            if (event.mouseWheelScroll.delta > 0) { //wheel up - zoom in
                this->sim_view.zoom(0.8);
                scale *= 0.8;
            }
            else if (event.mouseWheelScroll.delta < 0) { //wheel down - zoom out
                this->sim_view.zoom(1.2);
                scale *= 1.2;
            }
            break;
        case sf::Event::MouseButtonPressed:     // handler for LMB click, first go through all UI elements to check if they are clicked
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::string msg = this->static_ui_system.at("speed_controls").activate(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view));
                if (msg != "null") {
                    if (msg == "increase_sim_speed" && simulation_speed.at(SimulationState::RUNNING) != 24) {
                        simulation_speed.at(SimulationState::RUNNING) += 1;
                        std::cout << "simulation_speed = " << simulation_speed.at(SimulationState::RUNNING) << "\n";
                        break;
                    }
                    if (msg == "decrease_sim_speed" && simulation_speed.at(SimulationState::RUNNING) != 1) {
                        simulation_speed.at(SimulationState::RUNNING) -= 1;
                        std::cout << "simulation_speed = " << simulation_speed.at(SimulationState::RUNNING) << "\n";
                        break;
                    }
                    if (msg == "pause/resume" && simulation_state == SimulationState::RUNNING) {
                        simulation_state = SimulationState::PAUSED;
                        this->static_ui_system.at("speed_controls").
                            setEntryText(this->static_ui_system.at("speed_controls").
                                getEntry(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view)), "I>");
                        std::cout << "simulation paused\n";
                        break;
                    }
                    if (msg == "pause/resume" && simulation_state == SimulationState::PAUSED) {
                        simulation_state = SimulationState::RUNNING;
                        this->static_ui_system.at("speed_controls").
                            setEntryText(this->static_ui_system.at("speed_controls").
                                getEntry(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view)), "II");
                        std::cout << "simulation resumed\n";
                        break;
                    }
                }
                msg = this->static_ui_system.at("menu_button").activate(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view));
                if (msg != "null") {
                    if (msg == "menu_button") {
                        go_to_pause();
                        break;
                    }
                }
                for (auto a : sol->get_systems()) {
                    for (auto b : a->get_planets()) {
                        if (this->dynamic_ui_system.at(b->get_name()).isMouseOver(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view))) {
                            msg = this->dynamic_ui_system.at(b->get_name()).activate(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view));
                            action_state = ActionState::FOCUSED;
                            focus = b;
                            std::cout << "focused on " << focus->get_name() << "\n";
                            break;
                        }
                    }
                }                        
                if (msg == "null") {    // if none of interface elements are clicked
                    if (!(action_state == ActionState::PANNING)) {  // if camera is not moving by mouse
                        if (action_state == ActionState::FOCUSED) { // in case of camera focused on some planet
                            action_state = ActionState::PANNING;    // changing from focus to regular camera moving
                            //std::cout << "Stopped focusing on " << focus->get_name() << "\n";
                            focus = nullptr;                        // clearing focus
                            //std::cout << "camera is moving" << " x0 = " << pointerPos.x << " y0 = " << pointerPos.y << "\n";
                            oldPos = pointerPos;
                            break;
                        }   // if camera si not focused 
                        action_state = ActionState::PANNING;    // just move camera
                        //std::cout << "camera is moving" << " x0 = " << pointerPos.x << " y0 = " << pointerPos.y << "\n";
                        oldPos = pointerPos;
                        break;
                    }
                }
            }            
        case sf::Event::MouseButtonReleased: // mouse button released, map can't be moved now
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (action_state == ActionState::PANNING) {
                    action_state = ActionState::NONE;
                    //std::cout << "camera stopped moving = " << " x1 = " << oldPos.x << " y1 = " << oldPos.y << "\n";
                    break;
                }
            }
            break;
        case sf::Event::MouseMoved: { 
            if (action_state != ActionState::PANNING) { //if mouse button isnt pressed (camera isnt moving) highlight interface buttons
                this->static_ui_system.at("speed_controls").highlight(this->static_ui_system.at("speed_controls").
                    getEntry(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view)));
                this->static_ui_system.at("menu_button").highlight(this->static_ui_system.at("menu_button").
                    getEntry(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view)));
                for (auto a: sol->get_systems())    // or planet nameplates for focus
                    for (auto b : a->get_planets()) {
                        this->dynamic_ui_system.at(b->get_name()).highlight(this->dynamic_ui_system.at(b->get_name()).isMouseOver(this->engine->window.mapPixelToCoords(pointerPos, this->ui_view)));
                    }
                break;
            }
            //defining pointer position "in window" coordinates
            const sf::Vector2i newPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            sf::Vector2i delta = oldPos - newPos;   //calculating difference between old and new positions of pointer
            sim_view.setCenter(sim_view.getCenter() + sf::Vector2f(delta) * scale);     //setting center of view as old one plus delta in current scale
            //saving new position as old one
            oldPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            break;
        }
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // closes window on Esc pressed
            {
                this->engine->window.close();
            }
            // moving camera with arrow keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                sim_view.move(-1.f * sf::Vector2f(0, 5 * default_scale * scale));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                sim_view.move(1.f * sf::Vector2f(0, 5 * default_scale * scale));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                sim_view.move(-1.f * sf::Vector2f(5 * default_scale * scale, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                sim_view.move(1.f * sf::Vector2f(5 * default_scale * scale, 0));
            }
        default: 
            break;
        }        
    }
}

void SimState::update_simulation(const float dt) {
    step = simulation_speed.at(simulation_state) * dt * 3600;
    this->sol->simulate(step);      
    time += step;
    // T0D0: 
    // 1. possibly create separate class that handles simulation;
    // 2. multithreaded simulation, broken down into two steps, so coordinates of objects don't change during gravity calculations:
    //  - calculating accelerations and speeds of all cosmic bodies;
    //  - moving all cosmic bodies;
    return;
}

void SimState::update_ui() {
    static_ui_system.at("timer").setEntryText(0, utility::timer(time)); // changes elapsed simulated time on timer bar
    for (auto a : sol->get_systems())   // cycles through all planets and puts corresponding nameplates near them
        for (auto b : a->get_planets()) {
            sf::Vector2i pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(b->get_global_coords().x + (b->get_diameter() / 2 * sin(PI / 4)),
                b->get_global_coords().y + b->get_diameter() / 2 * sin(PI / 4)), sim_view);
            this->dynamic_ui_system.at(b->get_name()).set_position(this->engine->window.mapPixelToCoords(pos, ui_view));
        }
}

void SimState::update(const float dt) {
    update_simulation(dt);
    if (action_state == ActionState::FOCUSED)      // if camera is focused on planet moves view center to it
        sim_view.setCenter(sf::Vector2f(focus->get_global_x(), focus->get_global_y()));
    update_ui();    
}

void SimState::draw(const float dt) {
    this->engine->window.clear(sf::Color::Black);
    this->engine->window.setView(this->sim_view);
    this->sol->draw(this->engine->window);
    this->engine->window.setView(this->ui_view);
    for (auto ui : this->static_ui_system)
        this->engine->window.draw(ui.second);
    for (auto dyn_ui : this->dynamic_ui_system)
        dyn_ui.second.draw(this->engine->window);
}

void SimState::go_to_pause() {
    this->engine->push_state(new PauseMenuState(this->engine));
}
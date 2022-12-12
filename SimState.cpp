#include "SimState.h"

SimState::SimState(Engine* engine) {
    this->engine = engine;
    //this->engine->create_shapes();
    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    this->camera = new Camera(pos);
    this->galactic_factory = GalacticFactory::get_instance(engine);
    this->simulation = new Simulation();
    this->simulation->set_galaxy(this->galactic_factory->create_galaxy(std::vector<SolarSystem*> {this->galactic_factory->initialize_solar_system()}));
    this->camera->world_view.setCenter(this->simulation->get_galaxy()->get_solar_systems()[0]->get_coords().x, this->simulation->get_galaxy()->get_solar_systems()[0]->get_coords().y);
    this->camera->world_view.zoom(this->camera->world_display_scale *= this->camera->default_world_display_scale);
    action_state = ActionState::NONE;
    focus_type = FocusType::NONE;
    initialize_ui();
}

SimState::~SimState() {
    delete simulation;
    delete camera;
}

void SimState::initialize_ui() {    // creating statically placed UI elements
    this->static_ui_system.emplace("speed_controls", Ui(sf::Vector2f(32, 32), 4, true, true, engine->styles.at("button"),
        { std::make_pair("+", "increase_sim_speed"),
        std::make_pair((this->simulation->get_simulation_state() == SimulationState::RUNNING) ? "II" : "I>", "pause/resume"),
        std::make_pair("-", "decrease_sim_speed") }));
    this->static_ui_system.at("speed_controls").setPosition(this->engine->window.getSize().x - this->static_ui_system.at("speed_controls").getSize().x, this->engine->window.getSize().y - 32);
    this->static_ui_system.at("speed_controls").show();
    this->static_ui_system.emplace("focus_tree",
        Ui(sf::Vector2f(230.75, 32), 4, true, true, engine->styles.at("button"),
            { std::make_pair("Galaxy", "galaxy"),
            std::make_pair((focus_solar_system != nullptr) ? (focus_solar_system->get_name()) : "", "focus_solar_system"),
            std::make_pair((focus_ps != nullptr) ? (focus_solar_system->get_name()) : "", "focus_planet_system"),
            std::make_pair((focus_body != nullptr) ? (focus_body->get_name()) : "","focus_planet") }));
    this->static_ui_system.at("focus_tree").setPosition(260, this->engine->window.getSize().y - 32);
    this->static_ui_system.at("focus_tree").show();

    this->static_ui_system.emplace("timer", 
        Ui(sf::Vector2f(this->engine->window.getSize().x - this->static_ui_system.at("speed_controls").getSize().x, 32), 
            4, true, false, engine->styles.at("panel"),
        { std::make_pair(utility::timer(this->simulation->get_time()), "timer") }));
    this->static_ui_system.at("timer").setPosition(sf::Vector2f(0.f, this->engine->window.getSize().y - 32));
    this->static_ui_system.at("timer").show();

    this->static_ui_system.emplace("menu_button", Ui(sf::Vector2f(96, 32), 4, true, true, engine->styles.at("button"),
        { std::make_pair("Menu", "menu_button") }));
    this->static_ui_system.at("menu_button").setPosition(0, 0);
    this->static_ui_system.at("menu_button").show();
    // cycling through all solar systems, planetary systems and planets in galaxy to create corresponding nameplates
    for (auto a : this->simulation->get_galaxy()->get_solar_systems()) {
        this->dynamic_ui_system.emplace(a, DynamicUi(2, engine->styles.at("nameplates"), // creating nameplates for solar systems
            std::make_pair(a->get_name(), a->get_name())));
        // positioning them in the center of solar system
        sf::Vector2i pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(a->get_coords().x, 
            a->get_coords().y), this->camera->world_view);
        this->dynamic_ui_system.at(a).set_position(this->engine->window.mapPixelToCoords(pos, this->camera->ui_view));
        // making them visible
        this->dynamic_ui_system.at(a).show();
        for (auto b : a->get_systems()) {
            this->dynamic_ui_system.emplace(b, DynamicUi(2, engine->styles.at("nameplates"), // creating nameplastes for planet systems
                std::make_pair(b->get_name(), b->get_name())));
            sf::Vector2i pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(b->get_global_coords().x,
                b->get_global_coords().y), this->camera->world_view);
            this->dynamic_ui_system.at(b).set_position(this->engine->window.mapPixelToCoords(pos, this->camera->ui_view));
            // positioning them in the center of corresponding planet system
            for (auto c : b->get_planets()) {
                this->dynamic_ui_system.emplace(c, DynamicUi(2, engine->styles.at("nameplates"), // creating nameplates for planets, satellites etc
                    std::make_pair(c->get_name(), c->get_name())));
                sf::Vector2i pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(c->get_global_coords().x + c->get_diameter() / 2,
                    c->get_global_coords().y + c->get_diameter() / 2), this->camera->world_view);
                this->dynamic_ui_system.at(c).set_position(this->engine->window.mapPixelToCoords(pos, this->camera->ui_view));
                // positioning them down right from center of planet
            }
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
            this->camera->resize(event.size.width, event.size.height);
            sf::Vector2f pos = sf::Vector2f(0.f, event.size.height - 32);       // position of static UI elements in window coordinates
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->camera->ui_view);  // translation to UI view coordinates
            // resizing and putting UI elements to new positions
            this->static_ui_system.at("timer").setDimensions(sf::Vector2f(event.size.width - this->static_ui_system.at("speed_controls").getSize().x, 32));
            this->static_ui_system.at("timer").setPosition(pos);
            this->static_ui_system.at("timer").show();
            pos = sf::Vector2f(this->static_ui_system.at("timer").getSize().x, event.size.height - 32);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->camera->ui_view);
            this->static_ui_system.at("speed_controls").setPosition(pos);
            this->static_ui_system.at("speed_controls").show();
            pos = sf::Vector2f(260, event.size.height - 32);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->camera->ui_view);
            this->static_ui_system.at("focus_tree").setPosition(pos);
            this->static_ui_system.at("focus_tree").show();
            pos = sf::Vector2f(0.f, 0.f);
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->camera->ui_view);
            this->static_ui_system.at("menu_button").setPosition(pos);
            this->static_ui_system.at("menu_button").show();
            break; 
        }
        case sf::Event::MouseWheelScrolled: // zoom in and out by mousewheel
            if (event.mouseWheelScroll.delta > 0) { //wheel up - zoom in
                this->camera->zoom();
            }
            else if (event.mouseWheelScroll.delta < 0) { //wheel down - zoom out
                this->camera->zoom_out();
            }
            break;
            // T0D0: redo UI system and input handle for more automatization of ui interaction
        case sf::Event::MouseButtonPressed:     // handler for LMB click, first go through all UI elements to check if they are clicked
            if (event.mouseButton.button == sf::Mouse::Left) {
                // checking if speed controls interface elements clicked
                std::string msg = this->static_ui_system.at("speed_controls").activate(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view));
                if (msg != "null") { // if true handling button clicks
                    if (msg == "increase_sim_speed") { 
                        this->simulation->increase_simulation_speed();
                        break;
                    } 
                    if (msg == "decrease_sim_speed") { 
                        this->simulation->decrease_simulation_speed();
                        break;
                    } 
                    if (msg == "pause/resume") { 
                        this->simulation->change_simulation_state();
                        if (this->simulation->get_simulation_state() == SimulationState::PAUSED) {
                            this->static_ui_system.at("speed_controls").
                                setEntryText(this->static_ui_system.at("speed_controls").
                                    getEntry(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view)), "I>");
                        }
                        if (this->simulation->get_simulation_state() == SimulationState::RUNNING) {
                            this->static_ui_system.at("speed_controls").
                                setEntryText(this->static_ui_system.at("speed_controls").
                                    getEntry(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view)), "II");
                        }
                        //std::cout << "simulation paused\n";
                        break;
                    }
                }
                msg = this->static_ui_system.at("focus_tree").activate(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view));
                if (msg != "null") {
                    if (msg == "galaxy") {
                        stop_focus(ActionState::NONE);
                        break;
                    }
                    if (msg == "focus_solar_system" && (focus_type == FocusType::SOLARSYSTEM || focus_type == FocusType::PLANETSYSTEM || focus_type == FocusType::BODY)) {

                        set_focus(focus_solar_system);
                        break;
                    }
                    if (msg == "focus_planet_system" && (focus_type == FocusType::PLANETSYSTEM || focus_type == FocusType::BODY)) {
                        set_focus(focus_ps);
                        break;
                    }
                    if (msg == "focus_planet" && focus_type == FocusType::BODY) {
                        set_focus(focus_body);
                        break;
                    }
                }
                // checking if menu button is clicked
                msg = this->static_ui_system.at("menu_button").activate(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view));
                if (msg != "null") { // if true opening pause menu
                    if (msg == "menu_button") {
                        go_to_pause();
                        break;
                    }
                }
                // checking if object nameplates are clicked, focusing on clicked object if true
                for (auto a : this->simulation->get_galaxy()->get_solar_systems()) {
                    if (this->dynamic_ui_system.at(a).isMouseOver(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view))) {
                        msg = this->dynamic_ui_system.at(a).activate(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view));
                        set_focus(a);
                        break;
                    }
                    for (auto b : a->get_systems()) {
                        if (this->dynamic_ui_system.at(b).isMouseOver(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view))) {
                            msg = this->dynamic_ui_system.at(b).activate(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view));
                            set_focus(b);
                            break;
                        }
                        for (auto c : b->get_planets()) {
                            if (this->dynamic_ui_system.at(c).isMouseOver(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view))) {
                                msg = this->dynamic_ui_system.at(c).activate(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view));
                                set_focus(c);
                                break;
                            }
                        }
                    }
                }  
                if (msg == "null") {    // if none of interface elements are clicked
                    if (!(action_state == ActionState::PANNING || action_state == ActionState::FOCUSEDPANNING)) {  // if camera is not moving by mouse                       
                        if (action_state == ActionState::FOCUSED) {         // in case of focusing on some object
                            action_state = ActionState::FOCUSEDPANNING;     // keep focus but move camera
                            oldPos = pointerPos;
                            break;
                        }
                            
                        if (action_state == ActionState::NONE) {    // if camera is not focused
                            action_state = ActionState::PANNING;    // just move camera
                            oldPos = pointerPos;
                            break;
                        }                        
                    }
                }
            }            
        case sf::Event::MouseButtonReleased: // mouse button released, map can't be moved now
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (action_state == ActionState::PANNING ) {     // if camera is moved by mouse
                    action_state = ActionState::NONE;           // stop moving
                    break;
                }
                if (action_state == ActionState::FOCUSEDPANNING) { // if camera is moved by mouse while focused on something
                    action_state = ActionState::FOCUSED;           // stop moving by mouse but continue focus
                    break;
                }
            }
            break;
        case sf::Event::MouseMoved: { 
            if (action_state != ActionState::PANNING && action_state != ActionState::FOCUSEDPANNING) { //if mouse button isnt pressed (camera isnt moving by mouse) highlight interface buttons
                // looping through all static and dynamic UI elements to check if mouse hovering over them
                for (auto a : this->static_ui_system) {
                    if (this->static_ui_system.at(a.first).is_highlightable()) { // checking if this UI element is highlightable
                        this->static_ui_system.at(a.first).highlight(this->static_ui_system.at(a.first).
                                getEntry(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view)));
                    }                    
                }
                for (auto a : this->dynamic_ui_system) {
                    this->dynamic_ui_system.at(a.first).highlight(this->dynamic_ui_system.at(a.first).
                            isMouseOver(this->engine->window.mapPixelToCoords(pointerPos, this->camera->ui_view)));
                }
                break;      // leaving this switch-case iteration, so following code doesn't execute
            }               // if mouse button is pressed
            //defining pointer position "in window" coordinates
            const sf::Vector2i newPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            this->camera->set_input_offset(oldPos - newPos); // calculating offset and moving camera by it
            //saving new position as old one
            oldPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            break;
        }
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // opens pause menu on Esc pressed
            {
                go_to_pause();
            }
            // moving camera with arrow keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                this->camera->set_input_offset(-1 * sf::Vector2i(0, 5));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                this->camera->set_input_offset(1 * sf::Vector2i(0, 5));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                this->camera->set_input_offset(-1 * sf::Vector2i(5, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                this->camera->set_input_offset(1 * sf::Vector2i(5, 0));
            }
        default: 
            break;
        }        
    }
}

void SimState::update_simulation(const float dt) {
    this->simulation->simulate(dt);
    // T0D0:
    // 1. multithreaded simulation, broken down into two steps, so coordinates of objects don't change during gravity calculations:
    //  - calculating accelerations and speeds of all cosmic bodies;
    //  - moving all cosmic bodies;
    //  implement queue for objects to simulate with number of threads, that is less than number of simulatable objects
    return;
}

void SimState::update_ui() {
    static_ui_system.at("timer").setEntryText(0, utility::timer(this->simulation->get_time())); // changes elapsed simulated time on timer bar
    for (auto a : this->simulation->get_galaxy()->get_solar_systems()) {
        sf::Vector2i pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(a->get_coords().x,
            a->get_coords().y), this->camera->world_view);
        this->dynamic_ui_system.at(a).set_position(this->engine->window.mapPixelToCoords(pos, this->camera->ui_view));
        for (auto b : a->get_systems()) {
            pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(b->get_global_coords().x,
                b->get_global_coords().y), this->camera->world_view);
            this->dynamic_ui_system.at(b).set_position(this->engine->window.mapPixelToCoords(pos, this->camera->ui_view));
            for (auto c : b->get_planets()) {
                sf::Vector2i pos = this->engine->window.mapCoordsToPixel(sf::Vector2f(c->get_global_coords().x + (c->get_diameter() / 2 * sin(PI / 4)),
                    c->get_global_coords().y + c->get_diameter() / 2 * sin(PI / 4)), this->camera->world_view);
                this->dynamic_ui_system.at(c).set_position(this->engine->window.mapPixelToCoords(pos, this->camera->ui_view));
            }
        }
    }
}

void SimState::update(const float dt) {
    update_simulation(dt);
    if (action_state == ActionState::FOCUSED || action_state == ActionState::FOCUSEDPANNING)      // if camera is focused on planet moves view center to it
        switch (focus_type) {
        case FocusType::SOLARSYSTEM:
            this->camera->set_world_offset(focus_solar_system->get_speed() * this->simulation->get_step());
            break;
        case FocusType::PLANETSYSTEM:
            this->camera->set_world_offset(Vectorld2d(focus_solar_system->get_speed().x * this->simulation->get_step() + focus_ps->get_speed().x * this->simulation->get_step(),
                focus_solar_system->get_speed().y * this->simulation->get_step() + focus_ps->get_speed().y * this->simulation->get_step()));
            break;
        case FocusType::BODY:
            this->camera->set_world_offset(Vectorld2d(focus_solar_system->get_speed().x * this->simulation->get_step() + focus_ps->get_speed().x * this->simulation->get_step() + focus_body->get_speed().x * this->simulation->get_step(),
                focus_solar_system->get_speed().y * this->simulation->get_step() + focus_ps->get_speed().y * this->simulation->get_step() + focus_body->get_speed().y * this->simulation->get_step()));
            break;
        }            
    this->camera->move();
    update_ui();    
}

void SimState::draw(const float dt) {
    this->engine->window.clear(sf::Color::Black);
    this->engine->window.setView(this->camera->world_view);
    this->simulation->get_galaxy()->draw(this->engine->window);
    this->engine->window.setView(this->camera->ui_view);
    for (auto ui : this->static_ui_system)
        this->engine->window.draw(ui.second);
    for (auto dyn_ui : this->dynamic_ui_system)
        dyn_ui.second.draw(this->engine->window);
}

void SimState::go_to_pause() {
    this->engine->push_state(new PauseMenuState(this->engine));
}

void SimState::set_focus(SolarSystem* target) {
    if (action_state != ActionState::FOCUSED)
        action_state = ActionState::FOCUSED;
    if (focus_type == FocusType::BODY) {
        focus_body = nullptr;
        this->static_ui_system.at("focus_tree").setEntryText(3, "");
        for (auto a : focus_ps->get_planets())
            this->dynamic_ui_system.at(a).hide();
        focus_ps = nullptr;
        this->static_ui_system.at("focus_tree").setEntryText(2, "");
    }
    if (focus_type == FocusType::PLANETSYSTEM) {
        for (auto a : focus_ps->get_planets())
            this->dynamic_ui_system.at(a).hide();
        focus_ps = nullptr;
        this->static_ui_system.at("focus_tree").setEntryText(2, "");
    }
    if (focus_type == FocusType::SOLARSYSTEM) {
        for (auto a : focus_solar_system->get_systems())
            this->dynamic_ui_system.at(a).hide();
        this->dynamic_ui_system.at(focus_solar_system).show();
    }
    focus_type = FocusType::SOLARSYSTEM;
    focus_solar_system = target;
    this->dynamic_ui_system.at(target).hide();
    this->camera->move_to(sf::Vector2f(target->get_coords().x, target->get_coords().y));
    std::cout << "focused on " << focus_solar_system->get_name() << "\n";
    for (auto b : target->get_systems())
        this->dynamic_ui_system.at(b).show();
    this->static_ui_system.at("focus_tree").setEntryText(1, target->get_name());
}

void SimState::set_focus(PlanetSystem* target) {
    if (action_state != ActionState::FOCUSED)
        action_state = ActionState::FOCUSED;
    if (focus_type == FocusType::PLANETSYSTEM) {
        for (auto a : focus_ps->get_planets())
            this->dynamic_ui_system.at(a).hide();
        this->dynamic_ui_system.at(focus_ps).show();
    }
    if (focus_type == FocusType::BODY) {
        focus_body = nullptr;
        this->static_ui_system.at("focus_tree").setEntryText(3, "");
        for (auto a : focus_ps->get_planets())
            this->dynamic_ui_system.at(a).hide();
        this->dynamic_ui_system.at(focus_ps).show();
    }
    focus_type = FocusType::PLANETSYSTEM;
    focus_ps = target;
    this->dynamic_ui_system.at(target).hide();
    this->camera->move_to(sf::Vector2f(target->get_coords().x, target->get_coords().y));
    std::cout << "focused on " << focus_ps->get_name() << "\n";
    for (auto c : target->get_planets())
        this->dynamic_ui_system.at(c).show();
    this->static_ui_system.at("focus_tree").setEntryText(2, target->get_name());
}

void SimState::set_focus(CosmicBody* target) {
    if (action_state != ActionState::FOCUSED)
        action_state = ActionState::FOCUSED;
    focus_type = FocusType::BODY;
    focus_body = target;
    this->camera->move_to(sf::Vector2f(target->get_global_coords().x, target->get_global_coords().y));
    std::cout << "focused on " << focus_body->get_name() << "\n";
    this->static_ui_system.at("focus_tree").setEntryText(3, target->get_name());
}

void SimState::stop_focus(ActionState new_state) {
    action_state = new_state;
    if (focus_body != nullptr) {
        focus_body = nullptr;
        this->static_ui_system.at("focus_tree").setEntryText(3, "");
    }        
    if (focus_ps != nullptr) {
        for (auto a : focus_ps->get_planets())
            this->dynamic_ui_system.at(a).hide();
        this->dynamic_ui_system.at(focus_ps).hide();
        focus_ps = nullptr;
        this->static_ui_system.at("focus_tree").setEntryText(2, "");
    }
    if (focus_solar_system != nullptr) {
        this->dynamic_ui_system.at(focus_solar_system).show();
        for (auto a : focus_solar_system->get_systems())
            this->dynamic_ui_system.at(a).hide();
        focus_solar_system = nullptr;
        this->static_ui_system.at("focus_tree").setEntryText(1, "");
    }
    focus_type = FocusType::NONE;
    std::cout << "Stopped all focusing\n";
}
#include "PauseMenuState.h"

PauseMenuState::PauseMenuState(Engine* engine) {
    this->engine = engine;
    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    view.setSize(pos);
    view.setCenter(pos * 0.5f);    
    this->ui_system.emplace("menu", Ui(sf::Vector2f(192, 32), 4, false, true, engine->styles.at("button"),
        { std::make_pair("Resume simulation", "resume_simulation"),
        std::make_pair("Exit","exit") }));

    this->ui_system.at("menu").setOrigin(96, 32 * 1 / 2);
    this->ui_system.at("menu").setPosition(pos * 0.5f);    
    this->ui_system.at("menu").show();
}

void PauseMenuState::handle_input() {
    sf::Event event;
    sf::Vector2f mousePos = this->engine->window.mapPixelToCoords(sf::Mouse::getPosition(this->engine->window), this->view);
    while (this->engine->window.pollEvent(event))
    {
        switch (event.type)
        {
            // X button on window pressed, window closes
        case sf::Event::Closed:
            this->engine->window.close();  break;
            //window is resized
        case sf::Event::Resized: {
            this->view.setSize(event.size.width, event.size.height);
            sf::Vector2f pos = sf::Vector2f(event.size.width, event.size.height);
            pos *= 0.5f;    // calculating new window center
            // transferring from window to world coords, though they are the same here. Basically its just converting Vector2i into Vector2f
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), this->view);
            this->ui_system.at("menu").setPosition(pos); // setting ui position in the new window center
            break;
        }
        // Highlight menu items.
        case sf::Event::MouseMoved: {
            // highlights ui entry if mouse is hovering over it
            this->ui_system.at("menu").highlight(this->ui_system.at("menu").getEntry(mousePos));
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::string msg = this->ui_system.at("menu").activate(mousePos);

                if (msg == "resume_simulation")     // closing pause menu and resumin simulation
                {
                    this->engine->pop_state();
                    return;                         // using return here for handle_input() loop to actually stop
                }
                else if (msg == "exit")
                    this->engine->window.close();
            }
            break;
        }
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))   // closes pause menu and resumes simulation on Esc pressed
            {
                this->engine->pop_state();
                return;                                             // using return here for handle_input() loop to actually stop
            }
        default: break;
        }
    }
}

void PauseMenuState::update(const float dt) {
    return;
}

void PauseMenuState::draw(const float dt) {
    this->engine->window.clear();
    this->engine->window.setView(this->view);
    for (auto ui : this->ui_system)
        this->engine->window.draw(ui.second);
    //this->engine->window.draw();
}
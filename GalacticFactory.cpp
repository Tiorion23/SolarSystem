#include "GalacticFactory.h"
GalacticFactory* GalacticFactory::instance = nullptr;

GalacticFactory::GalacticFactory(Engine* engine) {
	this->engine = engine;
}

GalacticFactory* GalacticFactory::get_instance(Engine* engine) {
	if (instance == nullptr) {
		instance = new GalacticFactory(engine);
		return instance;
	}
	return instance;		
}

CosmicBody* GalacticFactory::
create_cosmic_body(CosmicBodyType type, std::string name, long double diam, long double m, Vectorld2d coords, Vectorld2d sp) {
	if (this->engine->graphics_handler.get_shapes_manager().is_shape_available(name)) {
		return new CosmicBody(type, name, diam, m, coords, sp, &(this->engine->graphics_handler.get_shapes_manager().get_shape(name)));
	}
	this->engine->graphics_handler.get_shapes_manager().add_shape(name, diam / 2, sf::Color(this->engine->rng->get_random_number(0,255), 
		this->engine->rng->get_random_number(0, 255), this->engine->rng->get_random_number(0, 255), 255));
	return new CosmicBody(type, name, diam, m, coords, sp, &(this->engine->graphics_handler.get_shapes_manager().get_shape(name)));
}

void GalacticFactory::create_solar_system_shapes() {
    this->engine->graphics_handler.get_shapes_manager().add_shape("Sun", 1.392e9 / 2, sf::Color::Yellow);
    this->engine->graphics_handler.get_shapes_manager().add_shape("Mercury", 4.8794e6 / 2, sf::Color::Magenta);
    this->engine->graphics_handler.get_shapes_manager().add_shape("Venus", 1.21036e7 / 2, sf::Color::Green);
    this->engine->graphics_handler.get_shapes_manager().add_shape("Earth", 1.2742e7 / 2, sf::Color::Blue);
    this->engine->graphics_handler.get_shapes_manager().add_shape("Moon", 3.47628e6 / 2, sf::Color::White);
    this->engine->graphics_handler.get_shapes_manager().add_shape("Mars", 6.779e6 / 2, sf::Color::Red);
    this->engine->graphics_handler.get_shapes_manager().add_shape("Phobos", 2.25e4 / 2, sf::Color::Cyan);
    this->engine->graphics_handler.get_shapes_manager().add_shape("Deimos", 1.24e4 / 2, sf::Color(100, 100, 100, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Jupiter", 69.911e6 / 2, sf::Color(255, 165, 0, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Io", 3.6426e4 / 2, sf::Color(50, 50, 50, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Europa", 3.1216e4 / 2, sf::Color(100, 150, 200, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Hanimedes", 5.2682e4 / 2, sf::Color(0, 255, 65, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Kallisto", 4.8206e4 / 2, sf::Color(255, 0, 155, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Saturn", 116.464e6 / 2, sf::Color(124, 64, 48, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Titan", 5.152e6 / 2, sf::Color(205, 133, 63, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Uranus", 50.724e6 / 2, sf::Color(192, 192, 192, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Neptune", 24.622e6 / 2, sf::Color(175, 238, 238, 255));
    this->engine->graphics_handler.get_shapes_manager().add_shape("Triton", 1.3534e6 / 2, sf::Color(128, 128, 128, 255));
}

SolarSystem* GalacticFactory::initialize_solar_system() {
    create_solar_system_shapes();
    PlanetSystem* sun = new PlanetSystem(std::vector<CosmicBody*> {
        create_cosmic_body(CosmicBodyType::STAR, "Sun", 1.392e9, 1.989e30, Vectorld2d(0, 0), Vectorld2d(0, 0))},     
        Vectorld2d(0, 0), Vectorld2d(0, 0)); // coordinates and speed of system
    PlanetSystem* mercury = new PlanetSystem(std::vector<CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Mercury", 4.8794e6, 3.33022e23, Vectorld2d(0, 0), Vectorld2d(0, 0))},
        Vectorld2d(-5.7909227e10, 0), Vectorld2d(0, -47360)); // coordinates and speed of system
    PlanetSystem* venus = new PlanetSystem(std::vector<CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Venus", 1.21036e7, 4.8675e24, Vectorld2d(0, 0), Vectorld2d(0, 0))},
        Vectorld2d(-1.08942109e11, 0), Vectorld2d(0, -35020)); // coordinates and speed of system
    PlanetSystem* earth_moon = new PlanetSystem(std::vector<CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Earth", 1.2742e7, 5.972e24, Vectorld2d(0, 0), Vectorld2d(0, 0)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Moon", 3.47628e6, 7.3477e22, Vectorld2d(4.067e8, 0), Vectorld2d(0, 1023))},
        Vectorld2d(1.495978707e11, 0), Vectorld2d(0, 29999.99999999941)); // coordinates and speed of system
    PlanetSystem* mars = new PlanetSystem(std::vector <CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Mars", 6.779e6, 6.4171e23, Vectorld2d(0, 0), Vectorld2d(0, 0)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Phobos", 2.25e4, 1.072e16, Vectorld2d(9.3772e6, 0), Vectorld2d(0, 2138.45)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Deimos", 1.24e4, 1.48e15, Vectorld2d(2.3458e7, 0), Vectorld2d(0, 1351.28))},
        Vectorld2d(2.2794382e11, 0), Vectorld2d(0, 24130));
    PlanetSystem* jupiter = new PlanetSystem(std::vector<CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Jupiter", 69.911e6, 1.8986e27, Vectorld2d(0, 0), Vectorld2d(0, 0)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Io", 3.6426e4, 8.9319e22, Vectorld2d(4.217e8, 0), Vectorld2d(0, 17334)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Europa", 3.1216e4, 4.8017e22, Vectorld2d(-6.711e8, 0), Vectorld2d(0, 13740)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Hanimedes", 5.2682e4, 1.4819e23, Vectorld2d(1.0704e9, 0), Vectorld2d(0, 10880)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Kallisto", 4.8206e4, 1.075e23, Vectorld2d(-1.8827e9, 0), Vectorld2d(0, 8204))},
        Vectorld2d(7.785472e11, 0), Vectorld2d(0, 13070));
    PlanetSystem* saturn = new PlanetSystem(std::vector<CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Saturn", 116.464e6, 5.6846e26, Vectorld2d(0, 0), Vectorld2d(0, 0)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Titan", 5.152e6, 1.3452e23, Vectorld2d(1.221870e9, 0), Vectorld2d(0, 5570))},
        Vectorld2d(1.4334493695e12, 0), Vectorld2d(0, 9690));
    PlanetSystem* uranus = new PlanetSystem(std::vector <CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Uranus", 50.724e6, 8.6813e25, Vectorld2d(0, 0), Vectorld2d(0, 0))},
        Vectorld2d(2.8766790825e12, 0), Vectorld2d(0, 6810));
    PlanetSystem* neptune = new PlanetSystem(std::vector <CosmicBody*> {
        create_cosmic_body(CosmicBodyType::PLANET, "Neptune", 24.622e6, 1.0243e26, Vectorld2d(0, 0), Vectorld2d(0, 0)),
            create_cosmic_body(CosmicBodyType::SATELLITE, "Triton", 1.3534e6, 2.14e22, Vectorld2d(3.54759e8, 0), Vectorld2d(0, 4390))},
        Vectorld2d(4.5034436615e12, 0), Vectorld2d(0, 5434.9));
    return new SolarSystem(std::vector <PlanetSystem*> { sun, mercury, venus, earth_moon, mars, jupiter, saturn, uranus, neptune },
        Vectorld2d(0, 0), Vectorld2d(0, 0), "Solar System");
}

Galaxy* GalacticFactory::create_galaxy(std::vector <SolarSystem*> systems) {
    return new Galaxy(systems);
}
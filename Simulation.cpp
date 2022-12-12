#include "Simulation.h"

Simulation::Simulation() {
	this->time = 0;
	this->simulation_state = SimulationState::RUNNING;
	simulation_speed.emplace(SimulationState::RUNNING, 1);
	simulation_speed.emplace(SimulationState::PAUSED, 0);
}

Simulation::~Simulation() {
	for (auto a : galaxy->get_solar_systems()) {
		for (auto b : a->get_systems()) {
			for (auto c : b->get_planets())
				delete c;
			delete b;
		}
		delete a;
	}
	delete galaxy;
}

unsigned long long int Simulation::get_time() const {
	return this->time;
}

void Simulation::set_galaxy(Galaxy* galaxy) {
	this->galaxy = galaxy;
}

Galaxy* Simulation::get_galaxy() const {
	return this->galaxy;
}

std::map<SimulationState, int> Simulation::get_simulation_speed() const {
	return this->simulation_speed;
}

void Simulation::increase_simulation_speed() {
	if (simulation_speed.at(SimulationState::RUNNING) < 24) {
		simulation_speed.at(SimulationState::RUNNING) += 1;
		std::cout << "simulation_speed = " << simulation_speed.at(SimulationState::RUNNING) << "\n";
	}
	return;
}

void Simulation::decrease_simulation_speed() {
	if (simulation_speed.at(SimulationState::RUNNING) > 1) {
		simulation_speed.at(SimulationState::RUNNING) -= 1;
		std::cout << "simulation_speed = " << simulation_speed.at(SimulationState::RUNNING) << "\n";
	}
	return;
}

SimulationState Simulation::get_simulation_state() const {
	return this->simulation_state;
}

void Simulation::change_simulation_state() {
	if (simulation_state == SimulationState::RUNNING) {
		simulation_state = SimulationState::PAUSED;
		std::cout << "simulation paused\n";
		return;
	}
	if (simulation_state == SimulationState::PAUSED) {
		simulation_state = SimulationState::RUNNING;
		std::cout << "simulation resumed\n";
		return;
	}
}

void Simulation::set_step(float step) {
	this->step = step;
}

float Simulation::get_step() const {
	return this->step;
}

void Simulation::simulate(const float dt) {
	step = simulation_speed.at(simulation_state) * dt * 3600;
	/*sf::Clock clock;
	sf::Time elapsed = clock.restart();
	float dt = elapsed.asSeconds();
	std::cout << "Simulation tick took " << dt << " seconds";*/
	for (int i = 0; i < this->galaxy->get_solar_systems().size(); i++)
		for (int j = j = i + 1; j < this->galaxy->get_solar_systems().size(); j++)
			this->galaxy->get_solar_systems()[i]->grav_pull(this->galaxy->get_solar_systems()[j]);
	for (const auto a : this->galaxy->get_solar_systems()) {
		a->update_speed(step);
		a->move(step);
	}
	for (auto& a : this->galaxy->get_solar_systems())		// after defining new coordinates of all planetary systems
		a->simulate(step);
	time += step;
}
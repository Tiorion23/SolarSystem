#ifndef SIMULATION
#define SIMULATION
#include "Galaxy.h"

enum class SimulationState { RUNNING, PAUSED };

class Simulation {
	Galaxy* galaxy;						// pointer to the simulated galaxy
	unsigned long long int time;		// number of simulated seconds
	float step;							// simulation time step
	SimulationState simulation_state;	// simulation state may be RUNNING or PAUSED
	std::map<SimulationState, int> simulation_speed;	// simulation speed, contains value for each state to save speed value while simulation is paused
public:
	Simulation();
	~Simulation();
	// getter for simulated time
	unsigned long long int get_time() const;
	// setter for galaxy
	void set_galaxy(Galaxy* galaxy);
	// getter for galaxy
	Galaxy* get_galaxy() const;
	// setter for simulation step
	void set_step(float step);
	// getter for simulation step
	float get_step() const;
	// getter for simulation step
	std::map<SimulationState, int> get_simulation_speed() const;
	// increases simulation speed by 1 hour per second, with maximum speed of 24 hours per second
	void increase_simulation_speed();
	// decreases simulation speed by 1 hour per second with minimum speed of 1 hour per second
	void decrease_simulation_speed();
	// returns current simulation state
	SimulationState get_simulation_state() const;
	// changes simulation state, RUNNING to PAUSED and vice versa
	void change_simulation_state();
	// simulates galaxy, calculating simulation step based on frametime dt and given simulation speed
	void simulate(const float dt);
};

#endif
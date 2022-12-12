#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "StartState.h"
#include <iostream>
#include <iomanip>
#include <math.h>


int main()
{
    Engine engine;
    engine.push_state(new StartState(&engine));
    engine.run();
    return 0;    
}
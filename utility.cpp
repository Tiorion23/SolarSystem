#include "utility.h"

long double utility::mod(long double arg) {
    return sqrt(pow(arg, 2));
}

long double vector_length(std::vector<long double> v) {
    return sqrt(pow(v[0], 2) + pow(v[1], 2));
}

std::vector<long double> utility::mod_vector(std::vector<long double> v, float n) {
    return std::vector<long double> {v[0] * n, v[1] * n };
}

std::vector<long double> utility::vector_sum(std::vector<long double> v1, std::vector<long double> v2) {
    return std::vector<long double>{v1[0] + v2[0], v1[1] + v2[1]};
}

std::vector<long double> utility::rotate_vector(std::vector<long double> v, long double angle) {
    return std::vector<long double>{v[0] * cos(angle) - v[1] * sin(angle), v[0] * sin(angle) + v[1] * cos(angle)};
}
/*
std::vector<long double> utility::grav_force(const Planet& p, std::vector<Planet*> planets) {
    std::vector <long double> f{ 0, 0 ,0 };
    for (int i = 0; i < planets.size(); i++) {
        long double fl = 0;
        if (distance(p, *planets[i]) != 0)
            fl = (G * p.get_mass() * planets[i]->get_mass()) / pow(distance(p, *planets[i]), 2);
        else
            return std::vector <long double> {0, 0};
        long double alpha = acos(utility::mod(p.get_x() - planets[i]->get_x()) / distance(p, *planets[i]));
        long double fx = 0, fy = 0;
        if (planets[i]->get_x() < p.get_x())
            fx = (-fl * cos(alpha));
        else
            fx = (fl * cos(alpha));
        if (planets[i]->get_y() < p.get_y())
            fy = (-fl * sin(alpha));
        else
            fy = (fl * sin(alpha));
        f[1] += fx;
        f[2] += fy;
    }
    f[0] = sqrt(pow(f[1], 2) + pow(f[2], 2));
    return f;
}

std::vector<long double> utility::grav_force(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems) {
    std::vector <long double> f{ 0, 0 ,0 };
    for (int i = 0; i < psystems.size(); i++) {
        long double fl = 0;
        if (distance(ps, *psystems[i]) != 0)
            fl = (G * ps.get_mass() * psystems[i]->get_mass()) / pow(distance(ps, *psystems[i]), 2);
        else
            return std::vector <long double> {0, 0};
        long double alpha = acos(utility::mod(ps.get_x() - psystems[i]->get_x()) / distance(ps, *psystems[i]));
        long double fx = 0, fy = 0;
        if (psystems[i]->get_x() < ps.get_x())
            fx = (-fl * cos(alpha));
        else
            fx = (fl * cos(alpha));
        if (psystems[i]->get_y() < ps.get_y())
            fy = (-fl * sin(alpha));
        else
            fy = (fl * sin(alpha));
        f[1] += fx;
        f[2] += fy;
    }
    f[0] = sqrt(pow(f[1], 2) + pow(f[2], 2));
    return f;
}

std::vector<long double> utility::grav_pull(Planet* p, std::vector<Planet*> planets) {
    std::vector <long double> a{ 0, 0 };
    for (int i = 0; i < planets.size(); i++) {
        long double f = 0;
        if (distance(*p, *planets[i]) != 0)
            f = (G * p->get_mass() * planets[i]->get_mass()) / pow(distance(*p, *planets[i]), 2);
        else
            return std::vector <long double> {0, 0};
        long double alpha = acos(utility::mod(p->get_x() - planets[i]->get_x()) / distance(*p, *planets[i]));
        long double ax = 0, ay = 0;
        if (planets[i]->get_x() < p->get_x())
            ax = (-f * cos(alpha)) / p->get_mass();
        else
            ax = (f * cos(alpha)) / p->get_mass();
        if (planets[i]->get_y() < p->get_y())
            ay = (-f * sin(alpha)) / p->get_mass();
        else
            ay = (f * sin(alpha)) / p->get_mass();
        a[0] += ax;
        a[1] += ay;
    }
    return a;
}

std::vector<long double> utility::grav_pull(PlanetSystem* ps, std::vector<PlanetSystem*> psystems) {
    std::vector <long double> a { 0, 0 };
    for (int i = 0; i < psystems.size(); i++) {
        long double f = 0;
        if (distance(*ps, *psystems[i]) != 0)
            f = (G * ps->get_mass() * psystems[i]->get_mass()) / pow(distance(*ps, *psystems[i]), 2);
        else
            return std::vector <long double> {0, 0};
        long double alpha = acos(utility::mod(ps->get_x() - psystems[i]->get_x()) / distance(*ps, *psystems[i]));
        long double ax = 0, ay = 0;
        if (psystems[i]->get_x() < ps->get_x())
            ax = (-f * cos(alpha)) / ps->get_mass();
        else
            ax = (f * cos(alpha)) / ps->get_mass();
        if (psystems[i]->get_y() < ps->get_y())
            ay = (-f * sin(alpha)) / ps->get_mass();
        else
            ay = (f * sin(alpha)) / ps->get_mass();
        a[0] += ax;
        a[1] += ay;
    }
    return a;
}

std::vector<Planet*> utility::interaction_list(Planet* p, std::vector<Planet*> planets) {
    std::vector<Planet*> result;
    for (const auto& a : planets) {
        if (a != p)
            result.push_back(a);
    }
    return result;
}

std::vector<PlanetSystem*> utility::interaction_list(PlanetSystem* ps, std::vector<PlanetSystem*> psystems) {
    std::vector<PlanetSystem*> result;
    for (const auto& a : psystems) {
        if (a != ps)
            result.push_back(a);
    }
    return result;
}
*/
std::string utility::timer(unsigned long long int time) {
    std::string result;
    std::stringstream myString;
    int years = int(time / 31536000);
    int months = int(time % 31536000 / 2628000);
    int days = int(time % 31536000 % 2628000 / 87600);
    int hours = int(time % 31536000 % 2628000 % 87600 / 3600);
    int minutes = int(time % 31536000 % 2628000 % 87600 % 3600 / 60);
    int seconds = time%60;
    
    myString << years << " years " << months << " months " << days << " days " << hours << " hours " << minutes << " minutes " << seconds << " seconds.\n";
    result = myString.str();
    return result;
}

std::string utility::info(const std::vector<Planet*> &planets) {
    std::string result;
    std::stringstream myString;
    for  (const auto& a : planets) { // for each planet a in planets
        myString << a->get_name() << " F=" << grav_force(*a, interaction_list(*a, planets)).length() <<
            //" Fx=" << grav_force(*a, interaction_list(*a, planets))[0] << 
            //" Fy=" << grav_force(*a, interaction_list(*a, planets))[1] << 
            " V = " << sqrt(pow(a->get_speed()[0],2) + pow(a->get_speed()[1], 2)) << 
            " x = " << a->get_x() << " y = " << a->get_y() << "\n"; 
    }
    result += myString.str();
    return result;
}

std::string utility::info(const PlanetSystem& ps) {
    std::string result;
    std::stringstream myString;
    for (const auto& a : ps.get_planets()) { // for each planet b in planet system
        myString << a->get_name() << " F=" << grav_force(*a, interaction_list(*a, ps.get_planets())).length() <<
            //" Fx=" << grav_force(*a, interaction_list(*a, ps.get_planets()))[0] <<
            //" Fy=" << grav_force(*a, interaction_list(*a, ps.get_planets()))[1] <<
            " V = " << sqrt(pow(a->get_speed()[0], 2) + pow(a->get_speed()[1], 2)) <<
            " x = " << a->get_x() << " y = " << a->get_y() << "\n";
    }
    result += myString.str();
    return result;
}

std::string utility::info(const std::vector<PlanetSystem*>& psystems) {
    std::string result;
    std::stringstream myString;
    for (auto const& a : psystems) { //for each planet system a
        myString << a->get_name() << //" F=" << grav_force(*a, interaction_list(*a, psystems)).length() <<
            //" Fx=" << grav_force(*a, interaction_list(*a, psystems))[0] <<
            //" Fy=" << grav_force(*a, interaction_list(*a, psystems))[1] <<
            " V = " << sqrt(pow(a->get_speed()[0], 2) + pow(a->get_speed()[1], 2)) <<
            " x = " << a->get_x() << " y = " << a->get_y() <<
            " global x = " << a->get_global_x() << " global y = " << a->get_global_y() << "\n";
    }
    result += myString.str();
    return result;
}

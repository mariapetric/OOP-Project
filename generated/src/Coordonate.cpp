
#include "Coordonate.h"
#include <iostream>

//constructor
Coordonate::Coordonate (const int x, const int y) : x{x}, y{y} {}

//cc si op=
Coordonate::Coordonate (const Coordonate& other) : x{other.x}, y{other.y} {}
Coordonate& Coordonate::operator= (const Coordonate& other) {
    if (this != &other) {
      x = other.x;
      y = other.y;
    }
    return *this;
}
//op de afisare
std::ostream& operator<< (std::ostream& os, const Coordonate& obj) {
    os << "( " << obj.x << ", " << obj.y << " )" << '\n';
    return os;
}

//getters si setters
int Coordonate::get_x () const { return x; }
int Coordonate::get_y () const { return y; }

void Coordonate::set_x (int new_x) { x = new_x; }
void Coordonate::set_y (int new_y) { y = new_y; }

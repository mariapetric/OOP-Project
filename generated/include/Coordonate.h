
#ifndef COORDONATE_H
#define COORDONATE_H
#include <iostream>
#include <functional>
#include <cmath>
template <typename T>
class Coordonate {
    T x, y;
public:
  //constructor si destructor
    explicit Coordonate() : x{0}, y{0} {}
  explicit Coordonate (const T x, const T y) : x{x}, y{y} {}
  ~Coordonate () {};

  //cc si op=
  Coordonate (const Coordonate& other) : x{other.x}, y{other.y} {}
    Coordonate& operator= (const Coordonate& other) {
      if (this != &other) {
          x = other.x;
          y = other.y;
      }
      return *this;
  }

  //op de afisare
    template <typename U>
    friend std::ostream& operator<< (std::ostream& os, const Coordonate<U>& ob);

  //getters si setters
  T get_x () const { return x; }
  T get_y () const { return y; }

  void set_x (const T new_x) { x = new_x; }
  void set_y (const T new_y) { y = new_y; }

    bool operator== (const Coordonate& other) const {
        return x == other.x && y == other.y;
    }
    // functie membra
    T distDeLaOrigine() const {
        return static_cast<T> (std::sqrt(x*x + y*y));
    }
    bool operator< (const Coordonate& other) const {
      if (x < other.x) return true;
      if (x > other.x) return false;
      return (y < other.y);
  }
};

template <typename U>
std::ostream& operator<< (std::ostream& os, const Coordonate<U>& ob) {
    os << "( " << ob.x << ", " << ob.y << " )" << '\n';
    return os;
}

// functie libera template
template <typename T>
bool Egale(const Coordonate<T>& a, const Coordonate<T>& b) {
    return a == b;
}

namespace std {
    template <>
    struct hash<Coordonate<int>> {
        size_t operator() (const Coordonate<int>& obj) const {
            return hash<int>()(obj.get_x()) ^ (hash<int>()(obj.get_y()) << 1) ;
        }
    };
}

#endif //COORDONATE_H

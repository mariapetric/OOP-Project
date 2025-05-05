

#ifndef COORDONATE_H
#define COORDONATE_H
#include <iostream>
#include <functional>

class Coordonate {
    int x, y;
public:
  //constructor si destructor
  explicit Coordonate (const int x = 0, const int y = 0 );
  ~Coordonate () {};

  //cc si op=
  Coordonate (const Coordonate& other);
  Coordonate& operator= (const Coordonate& other);

  //op de afisare
  friend std::ostream& operator<< (std::ostream& os, const Coordonate& obj);

  //getters si setters
  int get_x () const;
  int get_y () const;

  void set_x (const int new_x);
  void set_y (const int new_y);

    bool operator== (const Coordonate& other) const;


};

namespace std {
    template <>
    struct hash<Coordonate> {
        size_t operator() (const Coordonate& obj) const {
            return hash<int>()(obj.get_x()) ^ (hash<int>()(obj.get_y()) << 1) ;
        }
    };
}

#endif //COORDONATE_H

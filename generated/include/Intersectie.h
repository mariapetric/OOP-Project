
#ifndef INTERSECTIE_H
#define INTERSECTIE_H

#include <iostream>
#include <memory>
#include "Coordonate.h"

class Strada;

class Intersectie {
    Coordonate CoordonataIntersectie;
    std::shared_ptr<Strada> Strada_verticala;
    std::shared_ptr<Strada> Strada_orizontala;

public:
    explicit Intersectie (const Coordonate& coord_, std::shared_ptr<Strada> strada_vert_, std::shared_ptr<Strada> strada_oriz_);
    ~Intersectie() = default;

    friend std::ostream& operator<< (std::ostream& os, const Intersectie& obj);

};


#endif //INTERSECTIE_H

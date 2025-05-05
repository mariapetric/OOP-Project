
#ifndef INTERSECTIE_H
#define INTERSECTIE_H

#include <iostream>
#include <memory>
#include "Coordonate.h"
#include "Vehicul.h"

class Strada;

class Intersectie {
    Coordonate CoordonataIntersectie;
    std::shared_ptr<Strada> Strada_verticala;
    std::shared_ptr<Strada> Strada_orizontala;

public:
    explicit Intersectie (const Coordonate& coord_, std::shared_ptr<Strada> strada_vert_, std::shared_ptr<Strada> strada_oriz_);
    ~Intersectie() = default;

    friend std::ostream& operator<< (std::ostream& os, const Intersectie& obj);
    std::shared_ptr<Strada> get_CealaltaStrada (const std::shared_ptr<Strada>& strada) const;
    Coordonate get_Coordonate() const;
    std::shared_ptr<Strada> get_StradaVerticala() const;
    std::shared_ptr<Strada> get_StradaOrizontala() const;

};


#endif //INTERSECTIE_H

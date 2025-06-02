
#include <iostream>
#include <memory>
#include "Coordonate.h"
#include "Intersectie.h"
#include "Strada.h"

Intersectie::Intersectie (const Coordonate<int>& coord_, std::shared_ptr<Strada> strada_vert_, std::shared_ptr<Strada> strada_oriz_) :
                          CoordonataIntersectie{coord_}, Strada_verticala{strada_vert_}, Strada_orizontala{strada_oriz_} {}

std::ostream& operator<< (std::ostream& os, const Intersectie& obj) {
    os << obj.CoordonataIntersectie << ' ' << *obj.Strada_verticala << ' ' << *obj.Strada_orizontala << '\n';
    return os;
}

std::shared_ptr<Strada> Intersectie::get_CealaltaStrada (const std::shared_ptr<Strada>& strada) const {
    if (strada == Strada_verticala) return Strada_orizontala;
    if (strada == Strada_orizontala) return Strada_verticala;
    return nullptr;
}

Coordonate<int> Intersectie::get_Coordonate() const {
    return CoordonataIntersectie;
}

std::shared_ptr<Strada> Intersectie::get_StradaVerticala() const {
    return Strada_verticala;
}

std::shared_ptr<Strada> Intersectie::get_StradaOrizontala() const {
    return Strada_orizontala;
}



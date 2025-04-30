
#include <iostream>
#include <memory>
#include "Coordonate.h"
#include "Intersectie.h"
#include "Strada.h"

Intersectie::Intersectie (const Coordonate& coord_, std::shared_ptr<Strada> strada_vert_, std::shared_ptr<Strada> strada_oriz_) :
                          CoordonataIntersectie{coord_}, Strada_verticala{strada_vert_}, Strada_orizontala{strada_oriz_} {}

std::ostream& operator<< (std::ostream& os, const Intersectie& obj) {
    os << obj.CoordonataIntersectie << ' ' << *obj.Strada_verticala << ' ' << *obj.Strada_orizontala << '\n';
    return os;
}

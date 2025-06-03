#include "Sens.h"

Sens opus(Sens s) {
    switch (s) {
        case Sens::Sus:     return Sens::Jos;
        case Sens::Jos:     return Sens::Sus;
        case Sens::Stanga:  return Sens::Dreapta;
        case Sens::Dreapta: return Sens::Stanga;
    }
    return s; // fallback, teoretic unreachable
}
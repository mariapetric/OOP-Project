#ifndef COORDINATES_H
#define COORDINATES_H

#include <iostream>
#include <functional>
#include <cmath>

template<typename T>
class Coordinates {
    T x, y;

public:
    // Constructor and destructor
    explicit Coordinates() : x{0}, y{0} {}

    explicit Coordinates(const T x_, const T y_) : x{x_}, y{y_} {}

    ~Coordinates() = default;

    // Copy constructor and assignment operator
    Coordinates(const Coordinates &other) : x{other.x}, y{other.y} {}

    Coordinates &operator=(const Coordinates &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // Stream output
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Coordinates<U> &obj);

    // Getters and setters
    T get_x() const { return x; }
    T get_y() const { return y; }

    void set_x(const T new_x) { x = new_x; }
    void set_y(const T new_y) { y = new_y; }

    bool operator==(const Coordinates &other) const {
        return x == other.x && y == other.y;
    }

    T distanceFromOrigin() const {
        return static_cast<T>(std::sqrt(x * x + y * y));
    }

    bool operator<(const Coordinates &other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return y < other.y;
    }
};

template<typename U>
std::ostream &operator<<(std::ostream &os, const Coordinates<U> &obj) {
    os << "( " << obj.x << ", " << obj.y << " )" << '\n';
    return os;
}

template<typename T>
bool areEqual(const Coordinates<T> &a, const Coordinates<T> &b) {
    return a == b;
}

namespace std {
    template<>
    struct hash<Coordinates<int>> {
        size_t operator()(const Coordinates<int> &obj) const {
            return hash<int>()(obj.get_x()) ^ (hash<int>()(obj.get_y()) << 1);
        }
    };
}

#endif // COORDINATES_H

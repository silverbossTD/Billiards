#pragma once

#include <tuple>

/*
        My own Vector2d class.
        Read more at: https://gist.github.com/silverbossTD/b3f7abdea5879f4879d9e05460465620
*/
class Vector {
        public:
                using Pos = std::tuple<float, float>;

                Vector(const float &x = 0.0f, const float &y = 0.0f) :
                        x(x),
                        y(y)
                {};

                Vector(const Vector &vector) :
                        x(vector.x),
                        y(vector.y)
                {};

                ~Vector() = default;

                /* Operators */
                auto copy() const -> Vector;
                auto add(const Vector &vector) const -> Vector;
                auto subtract(const Vector &vector) const -> Vector;
                auto mult(const float &scalar) const -> Vector;
                auto addTo(const Vector &vector) -> Vector&;

                auto operator+(const Vector &other) const -> Vector;
                auto operator-(const Vector &other) const -> Vector;
                auto operator*(const float &scalar) const -> Vector;
                auto operator*=(const float &scalar) -> Vector&;
                auto operator+=(const Vector &other) -> Vector&;

                /* Get */
                auto dot(const Vector &vector) const -> float;
                auto getDirection() const -> float;
                auto getMagnitude() const -> float;
                auto angleBetween(const Vector &vector) const -> float;

                /* Set */
                void setDirection(const float &direction);
                void setMagnitude(const float &magnitude);
                void setPosition(const Pos &position);

                /* Utilities */
                auto getPosition() const -> Pos;

                float
                        x,
                        y;
};

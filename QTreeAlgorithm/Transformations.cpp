#include "Transformations.h"
# define M_PI 3.14159265358979323846

namespace McRenderer
{
    sf::Vector2f Transformations::rotate(sf::Vector2f p_vec, double p_angle)
    {
        double l_angle = toRadinas(p_angle);
        return sf::Vector2f(std::cos(l_angle) * p_vec.x - std::sin(l_angle) * p_vec.y,
            std::sin(l_angle) * p_vec.x + std::cos(l_angle) * p_vec.y);
    }

    double Transformations::toRadinas(double p_angle)
    {
        return (p_angle * M_PI) / 180.0f;
    }

    double Transformations::distance(sf::Vector2f p_vec1, sf::Vector2f p_vec2)
    {
        return std::sqrt((p_vec2.x - p_vec1.x) * (p_vec2.x - p_vec1.x)
            + (p_vec2.y - p_vec1.y) * (p_vec2.y - p_vec1.y));
    }

    double Transformations::distanceSQR(sf::Vector2f p_vec1, sf::Vector2f p_vec2)
    {
        return ((p_vec2.x - p_vec1.x) * (p_vec2.x - p_vec1.x)
            + (p_vec2.y - p_vec1.y) * (p_vec2.y - p_vec1.y));
    }

    double Transformations::normalization(double value, double min, double max)
    {
        return clamp((value - min) / (max - min), 0.0, 1.0);
    }

    double Transformations::clamp(double value, double min, double max)
    {
        if (value < min)
        {
            return min;
        }
        if (value > max)
        {
            return max;
        }
        return value;
    }

    double Transformations::lerp(double min, double max, double t)
    {
        return (max - min) * t + min;
    }

    double Transformations::length(sf::Vector2f a)
    {
        return std::sqrt(a.x * a.x + a.y * a.y);
    }

    double Transformations::dot(sf::Vector2f a, sf::Vector2f b)
    {
        return a.x * b.x + a.y * b.y;
    }

    double Transformations::castToVector(sf::Vector2f a, sf::Vector2f b)
    {
        return dot(a, b);
    }

    double Transformations::getAngle(sf::Vector2f a)
    {
        return std::atan2(a.y, a.x);
    }

    double Transformations::remap(double value, double prevMin, double prevMax, double nextMin, double nextMax)
    {
        double t = normalization(value, prevMin, prevMax);
        return lerp(nextMin, nextMax, t);
    }
}//McRenderer
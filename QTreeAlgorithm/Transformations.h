#pragma once
#include <SFML\Graphics.hpp>
namespace McRenderer
{
    class Transformations
    {
    public:
        static sf::Vector2f rotate(sf::Vector2f p_vec, double p_angle);

        static double toRadinas(double p_angle);

        static double distance(sf::Vector2f p_vec1, sf::Vector2f p_vec2);

        static double distanceSQR(sf::Vector2f p_vec1, sf::Vector2f p_vec2);

        static double normalization(double value, double min, double max);

        static double clamp(double value, double min, double max);

        static double lerp(double min, double max, double t);

        static double length(sf::Vector2f a);

        static double dot(sf::Vector2f a, sf::Vector2f b);

        static double castToVector(sf::Vector2f a, sf::Vector2f b);

        static double getAngle(sf::Vector2f a);

        static double remap(double value, double prevMin, double prevMax, double nextMin, double nextMax);
    };
}//McRenderer

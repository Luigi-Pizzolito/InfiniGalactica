#pragma once
#include "SFML/Graphics.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
// for debugging
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec);
namespace VectorMath {

	//returns the unitary vector in direction to the final pos
	sf::Vector2f getUnitaryVector(const sf::Vector2f& initpos, const sf::Vector2f& finalpos);
	sf::Vector2f getUnitaryVector(const sf::Vector2f& vec);
	float getAngleinDegrees(const sf::Vector2f& finalpos, const sf::Vector2f& initpos);
	float getAngleinDegrees(const sf::Vector2f& vectorfromOrigin);
	float getAngleinRadians(const sf::Vector2f& finalpos, const sf::Vector2f& initpos);
	float getAngleinRadians(const sf::Vector2f& vectorfromOrigin);
	sf::Vector2f getAABBMidFront(const sf::Vector2f& topleftpos, const sf::Vector2f& size);
	sf::Vector2f getAABBMidBack(const sf::Vector2f& topleftpos, const sf::Vector2f& size);
	sf::Vector2f getAABBCenter(const sf::Vector2f& topleftpos, const sf::Vector2f& size);
	sf::Vector2f getViewPortTopLeftPos();
	sf::Vector2f getViewportLowerRightPos();
	float degreeToRadians(float angle);
	float radiansToDegrees(float angle);
	namespace Vdirection {
		const sf::Vector2f RIGHT(1.0f, 0.0f);
		const sf::Vector2f LEFT(-1.0f, 0.0f);
		const sf::Vector2f UP(0.0f,-1.0f);
		const sf::Vector2f DOWN(0.0f,1.0f);
		//diagonals
		const sf::Vector2f UPRIGHT(getUnitaryVector(sf::Vector2f(1.0f, 1.0f)));
		const sf::Vector2f UPLEFT(getUnitaryVector(sf::Vector2f(-1.0f, 1.0f)));
		const sf::Vector2f DOWNRIGHT(getUnitaryVector(sf::Vector2f(1.0f, -1.0f)));
		const sf::Vector2f DOWNLEFT(getUnitaryVector(sf::Vector2f(-1.0f, -1.0f)));
	}
}

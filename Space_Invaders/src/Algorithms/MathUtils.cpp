#include "MathUtils.h"
#include <cmath>
#include <iostream>
#include "SceneManager/Scene.h"
//for debugging
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec) {
	stream << vec.x << "," << vec.y;
	return stream;
}
sf::Vector2f VectorMath::getUnitaryVector(const sf::Vector2f& initpos, const sf::Vector2f& finalpos)
{
	sf::Vector2f vec(finalpos - initpos);
	vec /= std::sqrt(vec.x * vec.x + vec.y * vec.y);

	return(vec);

}
sf::Vector2f VectorMath::getUnitaryVector(const sf::Vector2f& vec)
{
	return (vec / std::sqrt(vec.x * vec.x + vec.y * vec.y));
}
float VectorMath::getAngleinDegrees(const sf::Vector2f& finalpos, const sf::Vector2f& initpos)
{
	sf::Vector2f vec(finalpos - initpos);
	//std::cout << getUnitaryVector(vec) << "\n";
	float angle = atan2(vec.y, vec.x) *180.0f / M_PI ;

	return angle;

}
float VectorMath::getAngleinDegrees(const sf::Vector2f& vectorfromOrigin)
{
	float angle = atan2f(vectorfromOrigin.y, vectorfromOrigin.x) *180.0f /M_PI ;

	if (angle <0.0f) {
		
		angle = 360.0f + angle;
		
		
	}
	return angle;
}

float VectorMath::getAngleinRadians(const sf::Vector2f& finalpos, const sf::Vector2f& initpos)
{
	return degreeToRadians(getAngleinDegrees(finalpos, initpos));
}
float VectorMath::getAngleinRadians(const sf::Vector2f& vectorfromOrigin)
{
	return degreeToRadians(getAngleinDegrees(vectorfromOrigin));
}
sf::Vector2f VectorMath::getAABBMidFront(const sf::Vector2f& center, const sf::Vector2f& size)
{
	return (center+sf::Vector2f(size.x/2.0f,0));

}
sf::Vector2f VectorMath::getAABBMidBack(const sf::Vector2f& center, const sf::Vector2f& size)
{
	return (center - sf::Vector2f(size.x / 2.0f, 0));
}

sf::Vector2f VectorMath::getViewPortTopLeftPos()
{
	return sf::Vector2f(SceneManagement::Scene::s_view->getCenter() - SceneManagement::Scene::s_view->getSize() / 2.0f);

}

sf::Vector2f VectorMath::getViewportLowerRightPos()
{
	return sf::Vector2f(SceneManagement::Scene::s_view->getCenter() + SceneManagement::Scene::s_view->getSize() / 2.0f);

}

float VectorMath::degreeToRadians(float angle)
{
	return(angle * M_PI/180.0f);
}
float VectorMath::radiansToDegrees(float angle)
{
	return(angle * 180.0f/ M_PI);

}

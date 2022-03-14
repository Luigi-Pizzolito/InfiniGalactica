#include "MathUtils.h"
#include <cmath>
#include <iostream>
//for debugging
std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& vec) {
	stream << vec.x << "," << vec.y;
	return stream;
}
//Implemented by Daniel 03.06 5:02 PM
sf::Vector2f VectorMath::getUnitaryVector(const sf::Vector2f& initpos, const sf::Vector2f& finalpos)
{
	sf::Vector2f vec(finalpos - initpos);
	vec /= std::sqrt(vec.x * vec.x + vec.y * vec.y);

	return(vec);

}
//Implemented by Daniel 03.06 5:04 PM
sf::Vector2f VectorMath::getUnitaryVector(const sf::Vector2f& vec)
{
	return (vec / std::sqrt(vec.x * vec.x + vec.y * vec.y));
}
//Implemented by Daniel 03.06 5:13 PM
float VectorMath::getAngleinDegrees(const sf::Vector2f& finalpos, const sf::Vector2f& initpos)
{
	sf::Vector2f vec(finalpos - initpos);
	//std::cout << getUnitaryVector(vec) << "\n";
	float angle = atan2(vec.y, vec.x) *180.0f / M_PI ;

	return angle;

}
//Implemented by Daniel 03.06 5:15 PM
float VectorMath::getAngleinDegrees(const sf::Vector2f& vectorfromOrigin)
{
	float angle = atan2f(vectorfromOrigin.y, vectorfromOrigin.x) *180.0f /M_PI ;

	if (angle <0.0f) {
		
		angle = 360.0f + angle;
		
		
	}
	return angle;
}

//Implemented by Daniel 03.06 5:20 PM
float VectorMath::getAngleinRadians(const sf::Vector2f& finalpos, const sf::Vector2f& initpos)
{
	return degreeToRadians(getAngleinDegrees(finalpos, initpos));
}
//Implemented by Daniel 03.06 5:22 PM
float VectorMath::getAngleinRadians(const sf::Vector2f& vectorfromOrigin)
{
	return degreeToRadians(getAngleinDegrees(vectorfromOrigin));
}
//Implemented by Daniel 03.06 5:36 PM
sf::Vector2f VectorMath::getAABBMidFront(const sf::Vector2f& topleftpos, const sf::Vector2f& size)
{
	return (sf::Vector2f(topleftpos.x + size.x, topleftpos.y + size.y/2.0f));

}
//Implemented by Daniel 03.06 5:37 PM
sf::Vector2f VectorMath::getAABBMidBack(const sf::Vector2f& topleftpos, const sf::Vector2f& size)
{
	return (sf::Vector2f(topleftpos.x , topleftpos.y + size.y / 2.0f));
}
//Implemented by Daniel 03.06 5:38 PM
sf::Vector2f VectorMath::getAABBCenter(const sf::Vector2f& topleftpos, const sf::Vector2f& size)
{
	return (sf::Vector2f(topleftpos.x + size.x/2.0f, topleftpos.y + size.y / 2.0f));
}
//Implemented by Daniel 03.06 5:53 PM
float VectorMath::degreeToRadians(float angle)
{
	return(angle * M_PI/180.0f);
}
//Implemented by Daniel 03.06 5:54 PM
float VectorMath::radiansToDegrees(float angle)
{
	return(angle * 180.0f/ M_PI);

}

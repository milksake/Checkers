#include "Vector2.h"
#include <cmath>
#include "CGame.h"

Vector2::Vector2():
	x(0.0f), y(0.0f) {}

Vector2::Vector2(float X, float Y) :
	x(X), y(Y) {}

void Vector2::normalize()
{
	float vLength = length();
	*(this) /= vLength;
}

float Vector2::length() const
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::toOpenGlCoor(int width, int height) const
{
	return Vector2(2.0f * x / (float)width - 1, -(2.0f * y / (float)height - 1));
}

Vector2 Vector2::toPixelCoor(int width, int height) const
{
	return Vector2((x + 1) * width / 2.0f, (-y + 1) * height / 2.0f);
}

Vector2 Vector2::toOpenGlCoor(const CGame* const game) const
{
	return toOpenGlCoor(game->getWidth(), game->getHeight());
}

Vector2 Vector2::toPixelCoor(const CGame* const game) const
{
	return toOpenGlCoor(game->getWidth(), game->getHeight());
}

Vector2 Vector2::abs()
{
	return Vector2(std::abs(x), std::abs(y));
}

float Vector2::eucliDist(const Vector2& rhsVector) const
{
	Vector2 distanceVector = rhsVector - *(this);
	return distanceVector.length();
}

bool Vector2::checkRange(const Vector2& a, const Vector2& b)
{
	return std::min(a.x, b.x) <= x && x <= std::max(a.x, b.x) &&
		std::min(a.y, b.y) <= y && y <= std::max(a.y, b.y);
}

bool Vector2::operator==(const Vector2& rhsVector) const
{
	return x == rhsVector.x && y == rhsVector.y;
}

bool Vector2::operator!=(const Vector2& rhsVector) const
{
	return !operator==(rhsVector);
}

Vector2 Vector2::operator+(const Vector2& rhsVector) const
{
	return Vector2(x + rhsVector.x, y + rhsVector.y);
}

Vector2 Vector2::operator-(const Vector2& rhsVector) const
{
	return Vector2(x - rhsVector.x, y - rhsVector.y);
}

Vector2 Vector2::operator*(float value) const
{
	return Vector2(x * value, y * value);
}

Vector2 Vector2::operator*(const Vector2& rhsVector) const
{
	return Vector2(x * rhsVector.x, y * rhsVector.y);
}

Vector2 Vector2::operator/(float value) const
{
	return Vector2(x / value, y / value);
}

void Vector2::operator+=(const Vector2& rhsVector)
{
	x += rhsVector.x;
	y += rhsVector.y;
}

void Vector2::operator-=(const Vector2& rhsVector)
{
	x -= rhsVector.x;
	y -= rhsVector.y;
}

void Vector2::operator*=(float value)
{
	x *= value;
	y *= value;
}

void Vector2::operator/=(float value)
{
	x /= value;
	y /= value;
}
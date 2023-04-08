#pragma once

class CGame;

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float X, float Y);

	void  normalize();
	float length() const;

	Vector2  toOpenGlCoor(int width, int height) const;
	Vector2  toPixelCoor(int width, int height) const;
	Vector2  toOpenGlCoor(const CGame* const game) const;
	Vector2  toPixelCoor(const CGame* const game) const;

	float eucliDist(const Vector2& rhsVector) const;

	bool checkRange(const Vector2& a, const Vector2& b);

	bool        operator == (const Vector2& rhsVector) const;
	bool        operator != (const Vector2& rhsVector) const;

	Vector2     operator +  (const Vector2& rhsVector) const;
	Vector2     operator -  (const Vector2& rhsVector) const;
	Vector2     operator *  (const float value) const;
	Vector2     operator *  (const Vector2& rhsVector) const;
	Vector2     operator /  (const float value) const;

	void        operator += (const Vector2& rhsVector);
	void        operator -= (const Vector2& rhsVector);
	void        operator *= (const float value);
	void        operator /= (const float value);
};


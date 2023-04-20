#pragma once

class CCheckers;

class Actor
{
protected:
	CCheckers* scene = nullptr;
	bool color;

public:
	void setScene(CCheckers* _scene);

	virtual void update() = 0;

	Actor(bool color);
};

class Player:
	public Actor
{
public:
	Player(bool color);

	// Inherited via Actor
	virtual void update() override;
};

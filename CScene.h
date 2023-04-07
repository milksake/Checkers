#pragma once
#include <map>
#include <vector>
#include "Vector2.h"

class CGame;

class CScene
{
protected:
	CGame* const game = nullptr;
	bool         ended = false;

public:
	CScene(CGame* const _game);

	virtual void begin() = 0;
	virtual void end() = 0;
	virtual void update() = 0;

	bool hasEnded() const;
};

class CMenu : public CScene
{
public:
	CMenu(CGame* const _game);
	Vector2 a;
	Vector2 b;
	Vector2 c;
	Vector2 d;

	// Inherited via CScene
	virtual void begin() override;
	virtual void end() override;
	virtual void update() override;
};

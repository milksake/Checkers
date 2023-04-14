#pragma once
#include "CScene.h"
#include "CBoard.h"
#include "Actor.h"

class CCheckers : public CScene
{
	friend class Player;
	friend class AI;

	CBoard board;
	Vector2 sep;
	Vector2 selectedSquare;
	std::vector<Vector2> highlitedSquares;
	Actor* actors[2];
	bool turn;

	void drawBoard();
	void drawPiece(const Vector2& pos, bool color);
	void selectSquare(const Vector2& pos);
	void deSelectSquare();

public:
	CCheckers(CGame* const _game, Actor* a1, Actor* a2, bool _turn);
	~CCheckers();

	// Inherited via CScene
	virtual void begin() override;
	virtual void end() override;
	virtual void update() override;
};
#pragma once
#include "Actor.h"
#include "CBoard.h"

class AI :
	public Actor
{
protected:
	int p;

	struct MinMaxNode
	{
		CBoard board;
		int alfa;
		int beta;
		bool color;
		std::vector<MinMaxNode*> children;

		MinMaxNode(CBoard board, bool color, std::vector<MinMaxNode*>& children, int alfa = 0x80000000, int beta = 0x7FFFFFFF):
			board(board), alfa(alfa), beta(beta), color(color), children(children) {}
		MinMaxNode(CBoard board, bool color, int alfa = 0x80000000, int beta = 0x7FFFFFFF) :
			board(board), alfa(alfa), beta(beta), color(color) {}
	};

public:
	AI(bool color, int p);
	int staticEvaluation(CBoard* const b);
	MinMaxNode* buildTree();
	void buildTree(int _p, MinMaxNode* n);
	virtual int processTree(MinMaxNode* n);
	void deleteTree(MinMaxNode* n);

	// Inherited via Actor
	virtual void update() override;
};

class AlphaBeta : public AI
{
public:
	AlphaBeta(bool color, int p);

	virtual int processTree(MinMaxNode* n) override;
};

#include "AI.h"
#include "CCheckers.h"
#include <iostream>
#include <algorithm>

AI::AI(bool color, int p) :
	Actor(color), p(p) {}

void AI::update()
{
	auto n = buildTree();
	if (n->children.empty())
	{
		std::cout << "End of Game.";
		return;
	}
	std::vector<int> v;
	for (auto& node : n->children)
	{
		v.push_back(processTree(node));
	}
	int maxI = 0;
	bool (*less)(int, int) = [](int a, int b) { return a < b; };
	bool (*greater)(int, int) = [](int a, int b) { return a > b; };
	bool (*comp)(int, int) = color ? greater : less;
	for (int i = 0, max = (int)0x80000000 - 1 * !color; i < v.size(); i++)
	{
		if (comp(v[i], max))
		{
			max = v[i];
			maxI = i;
		}
	}
	// Move
	scene->board = n->children[maxI]->board;

	// Delete
	deleteTree(n);

	// Change Turn
	scene->turn = !scene->turn;
}

int AI::staticEvaluation(CBoard* const b)
{
	return b->countPieces(true) - b->countPieces(false);
}

typename AI::MinMaxNode* AI::buildTree()
{
	auto n = new MinMaxNode(scene->board, color);
	buildTree(p - 1, n);
	return n;
}

void AI::buildTree(int _p, MinMaxNode* n)
{
	for (auto& piece : n->board.getPieces(n->color))
	{
		for (auto& move : n->board.possibleMoves(piece, n->color))
		{
			auto child = new MinMaxNode(n->board, !n->color);
			child->board.movePiece(piece, move);
			if (_p >= 1)
				buildTree(_p - 1, child);
			n->children.push_back(child);
		}
	}
}

int AI::processTree(MinMaxNode* n)
{
	if (n->children.empty())
		return staticEvaluation(&(n->board));
	std::vector<int> v;
	for (auto node : n->children)
	{
 		v.push_back(processTree(node));
	}
	if (n->color)
		return *std::max_element(v.begin(), v.end());
	else
		return *std::min_element(v.begin(), v.end());
}

void AI::deleteTree(MinMaxNode* n)
{
	for (auto& node : n->children)
		deleteTree(node);
	delete n;
}

AlphaBeta::AlphaBeta(bool color, int p):
	AI(color, p)
{
}
/*
void AlphaBeta::buildTree(int _p, MinMaxNode* n)
{
	for (auto& piece : n->board.getPieces(n->color))
	{
		for (auto& move : n->board.possibleMoves(piece, n->color))
		{
			auto child = new MinMaxNode(n->board, !n->color);
			child->board.movePiece(piece, move);
			if (_p >= 1)
				buildTree(_p - 1, child);
			n->children.push_back(child);
		}
	}
}*/

int AlphaBeta::processTree(MinMaxNode* n)
{
	if (n->children.empty())
		return staticEvaluation(&(n->board));
	std::vector<int> v;
	for (auto node : n->children)
	{
		int num = processTree(node);
		v.push_back(num);
		if (n->color)
			n->alfa = std::max(n->alfa, num);
		else
			n->beta = std::min(n->beta, num);
		if (n->beta <= n->alfa)
			break;
	}
	if (n->color)
		return *std::max_element(v.begin(), v.end());
	else
		return *std::min_element(v.begin(), v.end());
}
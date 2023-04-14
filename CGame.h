#pragma once
#include "CScene.h"
#include <GLFW/glfw3.h>

struct Input
{
	int key;
	int action;
	Vector2 pos;
};

struct Color
{
	float r, g, b, a;
	static const Color Black;
	static const Color White;
	static const Color AlphaGrey;
	static const Color Red;
	static const Color AlphaRed;
	static const Color Green;
	static const Color AlphaGreen;
};

void mouseCallback(GLFWwindow* window, int button, int action, int mods);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class CGame
{
	GLFWwindow* window;
	CScene* currentScene;
	int frame_time;
	int frame_count;
	int current_frame;
	int wWidth, wHeight;

public:

	CGame(int frameT = 0xE);
	bool init(int windowW, int windowH);

	void run();

	const int getHeight() const;
	const int getWidth() const;

	void changeScene(CScene* newScene);

	// Draw
	void beginDrawing();
	void endDrawing();

	// Input
	std::vector<Input> inputBuffer;
	Vector2 getMouseLocation();

	// Helper functions
	void drawLine(const Vector2& a, const Vector2& b, Color color = Color::White);
	void drawLines(const std::vector<Vector2>& points, Color color = Color::White);
	void drawContLines(const std::vector<Vector2>& points, Color color = Color::White);
	void drawRects(const std::vector<Vector2>& points, Color color = Color::White);
	void drawCircle(const Vector2& pos, const Vector2& length, Color color = Color::White);
	void drawHollowCircle(const Vector2& pos, const Vector2& length, Color color = Color::White);
};

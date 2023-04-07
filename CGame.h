#pragma once
#include "CScene.h"
#include <GLFW/glfw3.h>

struct Input
{
	int key;
	int action;
	Vector2 pos;
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

	template<typename T>
	void changeScene();

	// Draw
	void beginDrawing();
	void endDrawing();

	// Input
	std::vector<Input> inputBuffer;
	Vector2 getMouseLocation();

	// Helper functions
	void drawLine(const Vector2& a, const Vector2& b);
	void drawLines(std::vector<Vector2> points);
	void drawContLines(std::vector<Vector2> points);
	void drawRects(std::vector<Vector2> points);
};

template<typename T>
inline void CGame::changeScene()
{
	delete currentScene;
	currentScene = new T;
}

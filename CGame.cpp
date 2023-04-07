#include "CGame.h"
#include "Vector2.h"

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    CGame* game = static_cast<CGame*>(glfwGetWindowUserPointer(window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    game->inputBuffer.push_back({ button, action, Vector2(x, y) });
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    CGame* game = static_cast<CGame*>(glfwGetWindowUserPointer(window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    game->inputBuffer.push_back({ key, action, Vector2(x, -y) });
}

CGame::CGame(int frameT) :
    frame_time(frameT), current_frame(0), frame_count(frameT)
{
    currentScene = new CMenu(this);
}

bool CGame::init(int windowW, int windowH)
{
    /* Initialize the library */
    if (!glfwInit())
        return false;

    /* Create a windowed mode window and its OpenGL context */
    wWidth = windowW;
    wHeight = windowH;
    window = glfwCreateWindow(windowW, windowH, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Extra configurations*/
    glClearColor(0, 0, 0, 1);
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);

    return true;
}

void CGame::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (frame_count == frame_time)
        {
            frame_count = 0;
            current_frame++;
            currentScene->update();
        }
        frame_count++;
    }
    glfwTerminate();
}

const int CGame::getHeight() const
{
    return wHeight;
}

const int CGame::getWidth() const
{
    return wWidth;
}

void CGame::beginDrawing()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void CGame::endDrawing()
{
    glfwSwapBuffers(window);
    inputBuffer.clear();
    glfwPollEvents();
}

Vector2 CGame::getMouseLocation()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return Vector2(x, y);
}

void CGame::drawLine(const Vector2& a, const Vector2& b)
{
    glBegin(GL_LINES);
        auto _a = a.toOpenGlCoor(this);
        auto _b = b.toOpenGlCoor(this);
        glVertex2f(_a.x, _a.y);
        glVertex2f(_b.x, _b.y);
    glEnd();
}

void CGame::drawLines(std::vector<Vector2> points)
{
    glBegin(GL_LINES);
        for (int i = 0; i < points.size(); i++)
        {
            auto p = points[i].toOpenGlCoor(this);
            glVertex2f(p.x, p.y);
        }
    glEnd();
}

void CGame::drawContLines(std::vector<Vector2> points)
{
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i < points.size(); i++)
        {
            auto p = points[i].toOpenGlCoor(this);
            glVertex2f(p.x, p.y);
        }
    glEnd();
}

void CGame::drawRects(std::vector<Vector2> points)
{
    glBegin(GL_QUADS);
        for (int i = 0; i < points.size(); i++)
        {
            auto p = points[i].toOpenGlCoor(this);
            glVertex2f(p.x, p.y);
        }
    glEnd();
}

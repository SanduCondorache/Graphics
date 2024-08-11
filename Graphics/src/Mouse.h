#pragma once

#include <GLFW/glfw3.h>

class Mouse {
public:
	Mouse();
	// Callbacks
	static void cursorPosCallback(GLFWwindow* window, double _x, double _y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);

	static inline double getMouseX() { return m_X; }
	static inline double getMouseY() { return m_Y; }

	static double getMouseDX();
	static double getMouseDY();

	static double getMouseScrollDX();
	static double getMouseScrollDY();

	static bool button(int button);
	static bool buttonChanged(int button);
	static bool buttonWentUp(int button);
	static bool buttonWentDown(int button);

	static void centerCursor(bool val);

private:
	static double m_X, m_Y;

	static double m_LastX, m_LastY;

	static double m_dx, m_dy;

	static double m_ScrollDx, m_ScrollDy;

	static bool m_FirstMouse;

	static bool m_Buttons[GLFW_MOUSE_BUTTON_LAST];
	static bool m_ButtonsChanged[GLFW_MOUSE_BUTTON_LAST];

};

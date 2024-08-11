#include "Mouse.h"

double Mouse::m_X = 0; 
double Mouse::m_Y = 0;

double Mouse::m_LastX = 0; 
double Mouse::m_LastY = 0;

double Mouse::m_dx = 0; 
double Mouse::m_dy = 0;

double Mouse::m_ScrollDx = 0; 
double Mouse::m_ScrollDy = 0;

bool Mouse::m_FirstMouse = true;

bool Mouse::m_Buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::m_ButtonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };


void Mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y) {
	m_X = _x;
	m_Y = _y;

	if (m_FirstMouse) {
		m_LastX = m_X;
		m_LastY = m_Y;
		m_FirstMouse = false;
	}

	m_dx = m_X - m_LastX;
	m_dy = m_LastY - m_Y;

	m_LastX = m_X;
	m_LastY = m_Y;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_RELEASE) {
		if (m_Buttons[button]) {
			m_ButtonsChanged[button] = true;
		}
		m_Buttons[button] = false;
	}

	if (action == GLFW_PRESS) {
		if (!m_Buttons[button]) {
			m_ButtonsChanged[button] = true;
		}
		m_Buttons[button] = true;
	}
}

void Mouse::mouseWheelCallback(GLFWwindow* window, double dx, double dy) {
	m_ScrollDx = dx;
	m_ScrollDy = dy;
}

double Mouse::getMouseDX() {
	double dx = m_dx;
	m_dx = 0;
	return dx;
}

double Mouse::getMouseDY() {
	double dy = m_dy;
	m_dy = 0;
	return dy;
}

double Mouse::getMouseScrollDX() {
	double scrollDx = m_ScrollDx;
	m_ScrollDx = 0;
	return scrollDx;
}

double Mouse::getMouseScrollDY() {
	double scrollDy = m_ScrollDy;
	m_ScrollDy = 0;
	return scrollDy;
}

bool Mouse::button(int button) {
	return m_Buttons[button];
}

bool Mouse::buttonChanged(int button) {
	bool ret = m_ButtonsChanged[button];
	m_ButtonsChanged[button] = false;
	return ret;
}

bool Mouse::buttonWentUp(int button) {
	return !m_Buttons[button] && buttonChanged(button);
}

bool Mouse::buttonWentDown(int button)
{
	return m_Buttons[button] && buttonChanged(button);
}

#include "Window.h"

bool Window::s_keys[MAX_KEYS];
bool Window::s_mouseButtons[MAX_MOUSE_BUTTONS];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->s_keys[key] = action != GLFW_RELEASE;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->s_mouseButtons[button] = action != GLFW_RELEASE;
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->GetCamera()->onCameraMouseMove(xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->GetCamera()->adjustFov(yoffset);
}

bool Window::IsMouseButtonPressed(uint32_t buttCode)
{
	if (buttCode > MAX_MOUSE_BUTTONS)
		return false;
	return s_mouseButtons[buttCode];
}
bool Window::IsKeyPressed(uint32_t keycode)
{
	if (keycode > MAX_KEYS)
		return false;
	return s_keys[keycode];
}

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
	m_camera = CreateRef<Camera>(width, height);
	if (glfwInit())
	{
		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!m_window)
			glfwTerminate();
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(0);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);
		glfwSetScrollCallback(m_window, scroll_callback);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}
Window::~Window()
{
	glfwTerminate();
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(m_window);
}

void Window::OnUpdate()
{
	glfwSwapBuffers(m_window);

	glfwPollEvents();
}


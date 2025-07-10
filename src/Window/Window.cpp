/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:22:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/09 17:15:40 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Window/Window.hpp>

float	Window::width = WWIDTH;
float	Window::height = WHEIGHT;
bool	Window::rotate = true;
bool	Window::light = false;
bool	Window::torch = false;
bool	Window::shadow = false;
float	Window::typeMix = 1;
float	Window::textMix = 1;
float	Window::typeMixDiff = 0.01;
float	Window::textMixDiff = 0.01;
math::v3		Window::mixWay = {1, 0, 0};
bool	Window::select = false;
math::v3		Window::mousePos = {0, 0, 0};
math::v3		Window::lightColor = {1, 1, 1};

void framebuffer_size_callback(GLFWwindow* window, int nWidth, int nHeight)
{
	Window::width = nWidth;
	Window::height = nHeight;
    glViewport(0, 0, nWidth, nHeight);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
		Window::rotate = !Window::rotate;

    if (key == GLFW_KEY_F && action == GLFW_PRESS)
		Window::light = !Window::light;
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
		Window::shadow = !Window::shadow;

    if (key == GLFW_KEY_T && action == GLFW_PRESS)
		Window::typeMixDiff *= -1;
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
		Window::textMixDiff *= -1;

    if (key == GLFW_KEY_H && action == GLFW_PRESS)
		Window::mixWay = {Window::mixWay.z, Window::mixWay.x, Window::mixWay.y};

    if (action != GLFW_RELEASE)
	{
		Window::lightColor.x = std::max(std::min(Window::lightColor.x + ((key == GLFW_KEY_U) - (key == GLFW_KEY_J)) / 10.0f, 1.0f), 0.0f);
		Window::lightColor.y = std::max(std::min(Window::lightColor.y + ((key == GLFW_KEY_I) - (key == GLFW_KEY_K)) / 10.0f, 1.0f), 0.0f);
		Window::lightColor.z = std::max(std::min(Window::lightColor.z + ((key == GLFW_KEY_O) - (key == GLFW_KEY_L)) / 10.0f, 1.0f), 0.0f);
	}
		
}

void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		Window::torch = !Window::torch;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		Window::select = true;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window::mousePos.x = xpos;
	Window::mousePos.y = ypos;
}

Window::Window()
{
	if (glfwInit() == GLFW_FALSE)
		throw(std::runtime_error(RED BOLD "GLFW did not initialize" CLR));

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width, height, "ft_vox", NULL, NULL);
	if (!_window)
	{
		std::cout << "Erm What Da Hell" << std::endl;
		glfwTerminate();
		exit (0);
	}
	glfwMakeContextCurrent(_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw(std::runtime_error(RED BOLD "Glad Failed to load" CLR));
	glViewport(0, 0, width, height);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_TRUE);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (mode == NULL)
		throw(std::runtime_error(RED BOLD "Monitor Failed to be loaded" CLR));
    _monitorWidth = mode->width;
    _monitorHeight = mode->height;
	glfwSetWindowPos(_window, 0, _monitorHeight / 2 - height / 2);

	glfwSetKeyCallback(_window, keyCallback);
	glfwSetMouseButtonCallback(_window, mouseBtnCallback);
	glfwSetCursorPosCallback(_window, mouse_callback);

	glfwSetWindowSize(_window, _monitorWidth / 2, _monitorHeight);
	framebuffer_size_callback(_window, _monitorWidth / 2, _monitorHeight);

	_deltaTime = 0.016666667;
}

Window::~Window()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

GLFWwindow *Window::getContext() const
{
	return (_window);
}

float	Window::startRenderLoop()
{
	_oldTime = glfwGetTime();
	if (_oldTime == 0)
		throw(std::runtime_error(RED BOLD "<glfwGetTime> Failed" CLR));
	glfwPollEvents();
	glClearColor(0.17f, 0.13f, 0.07f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Window::typeMix = std::min(std::max(Window::typeMix + Window::typeMixDiff, -1.0f), 1.0f);
	Window::textMix = std::min(std::max(Window::textMix + Window::textMixDiff, -1.0f), 1.0f);

	return _deltaTime;
}

void	Window::endRenderLoop()
{
	glfwSwapBuffers(_window);
	_deltaTime = glfwGetTime() - _oldTime;
	std::stringstream	fps;
	fps << "fps: ";
	fps << (1 / _deltaTime);
	glfwSetWindowTitle(_window, fps.str().c_str());
}

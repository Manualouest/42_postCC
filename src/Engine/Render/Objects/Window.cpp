/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:05:33 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/06 13:14:17 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Render/Objects/Window.hpp>

int WWIDTH = 1080;
int WHEIGHT = 1080;

Window	*Window::_instance = NULL;

void	opengErrorMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	std::string severityColor;
	switch (severity){
		case GL_DEBUG_SEVERITY_LOW:
			severityColor = GRN BOLD;
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			severityColor =  ORG BOLD;
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			severityColor =  RED BOLD;
			break;
		default:
			return ; //these are notifications and not really important
			severityColor =  WHT BOLD;
    }

	PRINT DSTR BOLD "Opengl Message: " << severityColor;

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			PRINT "ERROR; ";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			PRINT "DEPRECATED_BEHAVIOR; ";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			PRINT "UNDEFINED_BEHAVIOR; ";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			PRINT "PORTABILITY; ";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			PRINT "PERFORMANCE; ";
			break;
		case GL_DEBUG_TYPE_OTHER:
			PRINT "OTHER; ";
			break;
		default:
			PRINT "NO TYPE; ";
	}

	PRINT message CENDL;
}

Window::Window()
{
	if (!_instance)
		_instance = this;

	if (!glfwInit())
		throw std::runtime_error(RED BOLD UNDL "GLFW Initialisation Failed\n" CLR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	GLFWmonitor	*monitor = NULL;
	
	_windowData = glfwCreateWindow(WWIDTH, WHEIGHT, WNAME, monitor, NULL);
	if (!_windowData)
	{
		glfwTerminate();
		throw std::runtime_error(RED BOLD UNDL "Window Creation Failed\n" CLR);
	}
	glfwMakeContextCurrent(_windowData);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw std::runtime_error(RED BOLD UNDL "Glad Failed to Init\n" CLR);
	}
	
	glViewport(0, 0, WWIDTH, WHEIGHT);

    glDebugMessageCallback(opengErrorMsg, 0);

	glfwSetInputMode(_windowData, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetFramebufferSizeCallback(_windowData, _resize);
	glfwSetKeyCallback(_windowData, _keyInput);
	glfwSetMouseButtonCallback(_windowData, _mouseInput);

	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE); Put Back Later ==================
	// glCullFace(GL_BACK);
	// glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetCursorPos(_windowData, WWIDTH / 2, WHEIGHT / 2);
	glfwGetCursorPos(_windowData, &_mousePos.x, &_mousePos.y);
}

Window::~Window()
{
	glfwDestroyWindow(_windowData);
	glfwTerminate();

	PRINT DSTR BOLD "Window Destroyed" CENDL;
}

void	Window::startFrame()
{
	_checkInstance();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_instance->_frameTime = glfwGetTime();
	_instance->_deltaTime = _instance->_frameTime - _instance->_lastFrameTime;
	glfwPollEvents();
}

void	Window::endFrame()
{
	_checkInstance();

	_instance->_refreshMouse();
	glfwSwapBuffers(_instance->_windowData);

	if (glfwWindowShouldClose(_instance->_windowData))
		_instance->_running = false;

	_instance->_lastFrameTime = _instance->_frameTime;
}

void	Window::_checkInstance()
{
	if (!_instance)
		throw(std::runtime_error(RED BOLD UNDL "Window instance not created" CLR));
}

void	Window::_refreshMouse()
{
	glfwGetCursorPos(_windowData, &_mousePos.x, &_mousePos.y);
	if (_lockMouse)
		glfwSetCursorPos(_windowData, WWIDTH / 2, WHEIGHT / 2);
}

void	Window::_resize(GLFWwindow *window, int width, int height)
{
	(void)window;

	glViewport(0, 0, width, height);
	WWIDTH = width;
	WHEIGHT = height;
}

void	Window::_keyInput(GLFWwindow *window, int key, int, int action, int)
{
	_checkInstance();

	(void)window;

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		_instance->_inputs[key] = true;
	else
		_instance->_inputs[key] = false;
}

void	Window::_mouseInput(GLFWwindow* window, int button, int action, int)
{
	_checkInstance();

	(void)window;

	if (action == GLFW_PRESS)
		_instance->_inputsMouse[button] = true;
	else
		_instance->_inputsMouse[button] = false;
}


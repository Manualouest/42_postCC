/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:49:41 by mbirou            #+#    #+#             */
/*   Updated: 2025/11/03 15:51:50 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine/Engine.hpp>

int WWIDTH = 1080;
int WHEIGHT = 1080;

std::array<bool, MAX_KEYS>			Engine::_inputs;
std::array<bool, MAX_MOUSE_KEYS>	Engine::_inputsMouse;
glm::dvec2							Engine::_mousePos = {0, 0};
bool								Engine::_lockMouse = false;
float								Engine::_deltaTime = 0;

Engine::Engine()
{
}

Engine::~Engine()
{

}

void	Engine::run()
{
	_init();
	
	_renderLoop();
}

void	opengErrorMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	PRINT DSTR BOLD "Opengl Message: " CLR;

	switch (severity){
		case GL_DEBUG_SEVERITY_LOW:
			PRINT GRN BOLD;
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			PRINT ORG BOLD;
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			PRINT RED BOLD;
			break;
		default:
			PRINT WHT BOLD;
    }

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

void	Engine::_init()
{
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

	computeNormals();
}

void	Engine::_frameStart()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_frameTime = glfwGetTime();
	_deltaTime = _frameTime - _lastFrameTime;
	glfwPollEvents();
}

void	Engine::_renderLoop()
{
	_running = true;

	/*========= TESTING ==================================================*/
	ShaderManager::addShader("modeltest", "assets/shaders/modeltest");
	ModelManager::addModel("dragon", "assets/objects/TerrorBird/rapid.obj");


	// TextureManager::loadImage("0", "assets/textures/bmp/cat.bmp");
	// TextureManager::loadImage("1", "assets/textures/bmp/wsRF1.bmp");
	// TextureManager::loadImage("2", "assets/textures/bmp/wsRF2.bmp");
	// TextureManager::loadImage("3", "assets/textures/bmp/wsRF3.bmp");
	// TextureManager::loadImage("4", "assets/textures/bmp/wsRF4.bmp");
	// TextureManager::loadImage("5", "assets/textures/bmp/wsRF5.bmp");
	// TextureManager::loadImage("6", "assets/textures/bmp/wsRF6.bmp");

	ModelManager::getModel("dragon").requestTextures();

	TextureManager::makeRequestArray();
	// TextureManager::makeArray({"1", "2", "3", "4", "5", "6"});
	// TextureManager::makeArray({"0"});

	camera.selfUpdate();
	/*===========================================================*/


	while (_running)
	{
		_frameStart();

		// add when scenemanager is coded
		// scenes.getCurrent().processInputs(_deltaTime);

		/*========= TESTING ==================================================*/
		
		if (getPressInput(GLFW_KEY_LEFT_CONTROL))
		{
			_lockMouse = !_lockMouse;
			if (_lockMouse)
				glfwSetInputMode(_windowData, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			else
				glfwSetInputMode(_windowData, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		if (getPressInput(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(_windowData, GLFW_TRUE);


		if (getRepeatInput(GLFW_KEY_KP_7))
			ModelManager::getModel("dragon").rotate(glm::vec3(1, 0, 0));
		if (getRepeatInput(GLFW_KEY_KP_8))
			ModelManager::getModel("dragon").rotate(glm::vec3(0, 1, 0));
		if (getRepeatInput(GLFW_KEY_KP_9))
			ModelManager::getModel("dragon").rotate(glm::vec3(0, 0, 1));

		if (getRepeatInput(GLFW_KEY_KP_4))
			ModelManager::getModel("dragon").rotate(glm::vec3(-1, 0, 0));
		if (getRepeatInput(GLFW_KEY_KP_5))
			ModelManager::getModel("dragon").rotate(glm::vec3(0, -1, 0));
		if (getRepeatInput(GLFW_KEY_KP_6))
			ModelManager::getModel("dragon").rotate(glm::vec3(0, 0, -1));




		ShaderManager::bindShader("modeltest");

		Model::sendNormals();

		TextureManager::useArray("texts", 0);

		if (_lockMouse)
			camera.selfUpdate();
		camera.setViewProjMatrix();


		ModelManager::getModel("dragon").draw();
		
		/*===========================================================*/

		if (glfwWindowShouldClose(_windowData))
			return;

		_refreshMouse();

		// add when scenemanager is coded
		// scenes.getCurrent().update(_deltaTime);
		// scenes.getCurrent().draw();

		_frameEnd();
	}
}

void	Engine::_frameEnd()
{
	glfwSwapBuffers(_windowData);

	_lastFrameTime = _frameTime;
}

void	Engine::_refreshMouse()
{
	glfwGetCursorPos(_windowData, &_mousePos.x, &_mousePos.y);
	if (_lockMouse)
		glfwSetCursorPos(_windowData, WWIDTH / 2, WHEIGHT / 2);
}

void	Engine::_resize(GLFWwindow *window, int width, int height)
{
	(void)window;

	glViewport(0, 0, width, height);
	WWIDTH = width;
	WHEIGHT = height;
}

void	Engine::_keyInput(GLFWwindow *window, int key, int, int action, int)
{
	(void)window;

	// if (action == GLFW_REPEAT)
	// 	inputsRepeat[key] = true;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		_inputs[key] = true;
	else
		_inputs[key] = false;
}

void	Engine::_mouseInput(GLFWwindow* window, int button, int action, int)
{
	(void)window;

	if (action == GLFW_PRESS)
		_inputsMouse[button] = true;
	else
		_inputsMouse[button] = false;
}


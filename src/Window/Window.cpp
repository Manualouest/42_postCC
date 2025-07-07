/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:22:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/07 15:55:25 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Window/Window.hpp>

float	Window::width = WWIDTH;
float	Window::height = WHEIGHT;

void framebuffer_size_callback(GLFWwindow* window, int nWidth, int nHeight)
{
	Window::width = nWidth;
	Window::height = nHeight;
    glViewport(0, 0, nWidth, nHeight);
}

Window::Window()
{
	glfwInit();

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
	gladLoadGL();
	glViewport(0, 0, width, height);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_TRUE);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	glfwPollEvents();
	glClearColor(0.17f, 0.13f, 0.07f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:22:40 by mbirou            #+#    #+#             */
/*   Updated: 2025/06/01 16:28:56 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Window/Window.hpp>

void framebuffer_size_callback(GLFWwindow* window, int nWidth, int nHeight)
{
	(void) nWidth;
	(void) nHeight;
    glViewport(0, 0, WWIDTH, WHEIGHT);
}

Window::Window()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(WWIDTH, WHEIGHT, "ft_vox", NULL, NULL);
	if (!_window)
	{
		std::cout << "Erm What Da Hell" << std::endl;
		glfwTerminate();
		exit (0);
	}
	
	glfwMakeContextCurrent(_window);
	gladLoadGL();
	glViewport(0, 0, WWIDTH, WHEIGHT);

	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_TRUE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

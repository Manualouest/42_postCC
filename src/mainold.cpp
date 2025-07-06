/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainold.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:20:14 by mbirou            #+#    #+#             */
/*   Updated: 2025/07/06 13:15:20 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION

#include <bitset>
#include <iomanip>

#include <Window/Window.hpp>

int width = 1000;
int height = 1000;

void	printTime(const timespec &time1, const timespec &time0)
{
	double	time = (time1.tv_sec - time0.tv_sec) + (time1.tv_nsec - time0.tv_nsec) / 1000000000.;
	if (time > 1)
		PRINT "Took " AND std::fixed AND std::setprecision(9) AND time AND " seconds";
	else if (time * 1000 > 1)
		PRINT "Took " AND std::fixed AND std::setprecision(6) AND time * 1000 AND " miliseconds";
	else if (time * 1000000 > 1)
		PRINT "Took " AND std::fixed AND std::setprecision(3) AND time * 1000000 AND " microseconds";
	else if (time * 1000000000 > 1)
		PRINT "Took " AND time * 1000000000 AND " nanoseconds";
}

void framebuffer_size_callback(GLFWwindow* window, int nWidth, int nHeight) //
{ //
	width = nWidth; //
	height = nHeight; //
    glViewport(0, 0, width, height); //
} //

int	main()
{
	glfwInit(); //

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //

	GLFWwindow	*window = glfwCreateWindow(width, height, "ft_vox", NULL, NULL); //
	if (!window) //
	{ //
		std::cout << "Erm What Da Hell" << std::endl; //
		glfwTerminate(); //
		return (-1); //
	} //
	
	glfwMakeContextCurrent(window); //
	gladLoadGL(); //
	glViewport(0, 0, width, height); //

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE); //////

	Shader	shader("shaders/default.vert", "shaders/default.frag"); //////

	// VAO VAO1;
	// VAO1.Bind();

	// VBO	VBO1(vertices, sizeof(vertices));
	// EBO	EBO1(indices, sizeof(indices));

	// VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	// VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// VAO1.Unbind();
	// VBO1.Unbind();
	// EBO1.Unbind();

	Texture	cat("textures/cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); //////
	cat.texUnit(shader, "tex0", 0); //////

	glEnable(GL_DEPTH_TEST); //
	glEnable(GL_CULL_FACE); //
	glCullFace(GL_FRONT); //

	Camera camera(glm::vec3(0.0f, 100.0f, 0.0f)); //////

	GLuint uniID = glGetUniformLocation(shader.ID, "indexs"); //////

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //


	camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix", width, height); //////

	double	lastTime; //////
	double	currentTime; //////
	double	delta; //////
	float	nbFrames; //////
	

	lastTime = glfwGetTime(); //////

	// glfwSwapInterval(0); //danger

	// timespec				Start;
	// timespec				End;
	// timespec_get(&Start, TIME_UTC);
	// Chunk	test(glm::vec2(0, 0));
	// timespec_get(&End, TIME_UTC);

	
	// PRINT BOLD "time take for 97: ";
	// printTime(End, Start);
	// PRINT "" CENDL;

	// for (int i = 0; i < 256; ++i)
	// {
	// 	PRINT BOLD AND i CENDL;
	// 	for (int ii = 0; ii < 32; ++ii)
	// 	{
	// 		if (test.chunkData.find(i * 32 + ii) != test.chunkData.end())
	// 		{
	// 			std::bitset<32> bits = test.chunkData.find(i * 32 + ii)->second;
	// 			PRINT bits CENDL;
	// 		}
	// 	}
	// 	NEWL;
	// }


	// ChunkHandler	chunkHandler;


	while (!glfwWindowShouldClose(window))
	{


		// glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.17f, 0.13f, 0.07f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 10000.0f, shader, "camMatrix", width, height);
		shader.Activate();

		cat.Bind();

		glfwSwapBuffers(window);
		
		currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		nbFrames++;
		if (delta >= 1.0)
		{
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);
			// glfwSetCursorPos(window, width / 2, height / 2);
			std::stringstream	fps;
			fps << "player pos: " << camera.Position.x << "; " << camera.Position.z << ", fps:";
			fps  << (nbFrames / delta);
			glfwSetWindowTitle(window, fps.str().c_str());
			nbFrames = 0;
			lastTime = currentTime;
		}

	}
	shader.Delete();
	cat.Delete();

	glfwDestroyWindow(window); //
	glfwTerminate(); //
	return (0);
}

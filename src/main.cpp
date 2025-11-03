//
// Created by bvasseur on 10/8/25.
//

// #include "include.hpp"
// #include "Engine/Procedural/Noise/Wave.hpp"
#include <Engine/Engine.hpp>


int main() {

	Engine	game;

	game.run();

	// glfwInit();

	// float lastTime = glfwGetTime() - 1.0f / 60.0f;
	// float deltaTime = 0;
	// Wave wave(1337);
	// glm::vec2 size(95, 55);

	// while (true) {
	// 	deltaTime = glfwGetTime() - lastTime;
	// 	lastTime = glfwGetTime();
	// 	std::vector<float> noiseOutput = wave.generateUniformGrid("2D",
	// 		glm::vec4(30, 30, 0, 0), glm::vec4(size, 0, 0), 0.08f);

	// 	std::cout << "\033[0m\033[100A\r";
	// 	// std::cout << "deltaTime : " << deltaTime << std::endl;
	// 	for (size_t y = 0; y < size.y; y++) {
	// 		for (size_t x = 0; x < size.x; x++) {
	// 			std::string color = std::to_string((int)((noiseOutput[y * size.x + x] + 1.0f) * 0.5f * 255.0f));
	// 			std::cout << "\033[48;2;" + color + ";" + color + ";" + color + "m " << " ";
	// 		}
	// 		std::cout << "\033[0m" << std::endl;
	// 	}
	// 	wave.update(deltaTime);
	// 	usleep(10000);
	// }
	// return 0;
}

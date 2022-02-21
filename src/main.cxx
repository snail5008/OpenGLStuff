#include <iostream>
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Vao.h"
#include "Vbo.h"
#include "Ebo.h"
#include "Renderer.h"
#include "Primitives.h"

#define is_pressed(window, key) glfwGetKey(window.window, key) == GLFW_PRESS
#define is_released(window, key) glfwGetKey(window.window, key) == GLFW_RELEASE

int main() {
#ifdef DEBUG
	std::cout << "Debug build\n";
#else
	std::cout << "Release build\n";
#endif


	Window window(800, 600, "triangle");
	window.create_context();
	window.load_opengl();
	window.enable_vsync();
	window.enable_msaa();
	window.update_when_resized();

	Vao vao;
	Vbo vbo;
	vao.bind();
	vbo.bind();
	vbo.data(sizeof(Primitives::QUAD_WITHOUT_EBO), Primitives::QUAD_WITHOUT_EBO);
	vao.vertex_attrib_ptr(0, 2, sizeof(float) * 2);
	
	Shader program("res/shaders/default.glsl");
	int u_Time = program.uniform_location("u_Time");
	int u_AnimationDisabled = program.uniform_location("u_AnimationDisabled");
	program.set_uniform1i(u_AnimationDisabled, false);
	program.get_errors();
	program.use();

	Renderer renderer;

	while (!window.should_close()) {
		program.set_uniform1f(u_Time, (float)glfwGetTime());

		renderer.clear_colour(0.2, 0.2, 0.2);

		vao.draw_arrays(6);

		if (is_pressed(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window.window, true);
		}
	}

	return 0;
}
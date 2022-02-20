#include <iostream>
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Vao.h"
#include "Vbo.h"
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


	Window window(800, 600, "triangle", 4);
	window.create_context();
	window.load_opengl();
	window.enable_vsync();
	window.enable_msaa();
	window.update_when_resized();

	Vao vao;
	vao.bind();

	Vbo vbo;
	vbo.data(sizeof(Primitives::QUAD), Primitives::QUAD, GL_DYNAMIC_DRAW);

	vao.vertex_attrib_ptr(0, Vao::THREE_DIMENSIONAL, sizeof(float) * 2);

	Shader program("res/shaders/default.glsl");
	program.get_errors();

	program.use();
	int u_Time_location = program.uniform_location("u_Time");

	Renderer renderer;
	//renderer.wireframe(true);
	while (!window.should_close()) {
		//Input::poll_input(window);
		renderer.clear_colour(0.2f, 0.4f, 0.7f);
		program.set_uniform1f(u_Time_location, (float)glfwGetTime());
		vao.draw_arrays(6);

		window.swap_buffers();
		window.poll_events();



		if (is_pressed(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window.window, true);
		}
		
	}

	return 0;
}
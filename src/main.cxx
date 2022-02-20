#include <iostream>
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Vao.h"
#include "Vbo.h"
#include "Renderer.h"
#include "Primitives.h"


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
	vao.bind();

	Vbo vbo;
	vbo.data(sizeof(Primitives::triangle), Primitives::triangle);

	vao.vertex_attrib_ptr(0, Vao::THREE_DIMENSIONAL, sizeof(float) * 2);

	Shader program("res/shaders/default.glsl");
	program.get_errors();

	program.use();
	check(int loc = glGetUniformLocation(program.program, "u_Time"));

	Renderer renderer;
	while (!window.should_close()) {
		renderer.clear_colour(0.2f, 0.5f, 0.7f);

		check(glUniform1f(loc, (float)glfwGetTime()));

		vao.draw_arrays(3);

		window.swap_buffers();
		window.poll_events();
	}

	return 0;
}
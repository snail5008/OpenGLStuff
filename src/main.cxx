#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "Vbo.h"
#include "Renderer.h"


int main() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window(800, 600, "triangle");
	window.create_context();
	window.load_opengl();

	float triangle[6] = {
		0.f, .5f,
		.5, -.5f,
		-.5f, -.5f
	};

	Vbo vbo;
	vbo.data(sizeof(triangle), triangle);

	Shader default_shader("res/shaders/default.glsl");
	default_shader.get_errors();

	check(glEnableVertexAttribArray(0));
	check(glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*2, (const void*)0));

	glfwSwapInterval(1);

	default_shader.use();

	Renderer renderer;
	while (!window.should_close()) {
		renderer.clear_colour(0.2, 0.5, 0.7);

		check(glDrawArrays(GL_TRIANGLES, 0, 3));

		window.swap_buffers();
		window.poll_events();
	}

	return 0;
}
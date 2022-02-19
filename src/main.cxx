#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "Vbo.h"


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

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*2, (const void*)0);

	while (!window.should_close()) {
		default_shader.use();

		glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.swap_buffers();
		window.poll_events();
	}

	return 0;
}
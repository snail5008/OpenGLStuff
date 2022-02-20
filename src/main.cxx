#include <iostream>
#include <vector>

#include "Window.h"
#include "Shader.h"
#include "Vbo.h"
#include "Renderer.h"


int main() {
	Window window(800, 600, "triangle", 4, 4, 6);
	window.create_context();
	window.load_opengl();

	check(glViewport(0, 0, 800, 600));
	glfwSetWindowSizeCallback(window.window, [](GLFWwindow* window, int width, int height) {
		check(glViewport(0, 0, width, height));
	});

	check(glEnable(GL_MULTISAMPLE));

	float triangle[6] = {
		0.f, .5f,
		.5, -.5f,
		-.5f, -.5f
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Vbo vbo;
	vbo.data(sizeof(triangle), triangle);

	std::cout << glGetString(GL_VERSION) << '\n';

	Shader program("res/shaders/default.glsl");
	program.get_errors();

	check(glEnableVertexAttribArray(0));
	check(glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*2, (const void*)0));
	

	glfwSwapInterval(1);
	

	program.use();
	check(int loc = glGetUniformLocation(program.program, "u_Time"));

	Renderer renderer;
	while (!window.should_close()) {
		renderer.clear_colour(0.2f, 0.5f, 0.7f);

		check(glUniform1f(loc, (float)glfwGetTime()));
		check(glDrawArrays(GL_TRIANGLES, 0, 3));

		window.swap_buffers();
		window.poll_events();
	}

	return 0;
}
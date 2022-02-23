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

Window window(800, 600, "triangle", 4);

bool FULLSCREEN = false;
void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		window.should_close(true);
	}

	if ((key == GLFW_KEY_F && action == GLFW_PRESS) || (key == GLFW_KEY_F11 && action == GLFW_PRESS)) {
		FULLSCREEN = !FULLSCREEN;
		window.fullscreen(FULLSCREEN);
	}
}

int main() {
	window.default_setup();
	window.set_key_callback(key_callback);
	window.info();

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

		window.swap_buffers();
		window.poll_events();
	}

	return 0;
}
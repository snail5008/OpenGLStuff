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
	if ((key == GLFW_KEY_F && action == GLFW_PRESS) || (key == GLFW_KEY_F11 && action == GLFW_PRESS)) {
		FULLSCREEN = !FULLSCREEN;
		window.fullscreen(FULLSCREEN);
	}
}

void reload_shader(Shader* program, bool& pressed) {
	
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

	Shader* program = new Shader("res/shaders/default.glsl");
	program->get_errors();
	program->use();
	int u_Time = program->uniform_location("u_Time");
	int u_AnimationDisabled = program->uniform_location("u_AnimationDisabled");


	Renderer renderer;
	bool r_pressed = false;
	bool w_pressed = false;
	bool wireframe = false;
	while (!window.should_close()) {

		program->set_uniform1f(u_Time, (float)glfwGetTime());
		program->set_uniform1i(u_AnimationDisabled, false);

		renderer.clear_colour(0.2f, 0.2f, 0.2f);

		vao.draw_arrays(6);

		window.swap_buffers();
		window.poll_events();


		// reload shaders on 'R'
		if (is_pressed(window, GLFW_KEY_R)) {
			if (!r_pressed) {
				program = new Shader("res/shaders/default.glsl");
				std::cout << "\n--- RELOADED SHADERS ---\n\n";
				program->get_errors();
				program->use();
				std::cout << "--------\n\n";
			}
			r_pressed = true;
		}
		else {
			r_pressed = false;
		}

		// change to wireframe on 'W'
		if (is_pressed(window, GLFW_KEY_W)) {
			if (!w_pressed) {
				wireframe = !wireframe;
				renderer.wireframe(wireframe);
			}
			w_pressed = true;
		}
		else {
			w_pressed = false;
		}
		

		// exit on 'ESC'
		if (is_pressed(window, GLFW_KEY_ESCAPE)) {
			window.should_close(true);
		}
		
	}

	delete program;

	return 0;
}
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* wrapper class around GLFW */
class Window {
public:
	GLFWwindow* window;
public:
	Window(unsigned int width, unsigned int height, const char* title) : window() {
		glfwInit();
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	}
	~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void create_context() {
		glfwMakeContextCurrent(window);
	}

	void load_opengl() {
		gladLoadGL();
	}

	void swap_buffers() {
		glfwSwapBuffers(window);
	}

	void poll_events() {
		glfwPollEvents();
	}

	bool should_close() {
		return glfwWindowShouldClose(window);
	}

	void set_title(const char* title) {
		glfwSetWindowTitle(window, title);
	}
};
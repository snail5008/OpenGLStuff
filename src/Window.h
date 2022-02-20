#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* wrapper class around GLFW */
class Window {
public:
	GLFWwindow* window;
public:
	Window(unsigned int width, unsigned int height, const char* title, int samples = 4, int version_major = 4, int version_minor = 6) : window() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_SAMPLES, samples);
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
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Errors.h"

/* wrapper class around GLFW */
class Window {
public:
	GLFWwindow* window;
	int msaa_samples;
	const char* window_title;
	int window_x, window_y, window_width, window_height;
public:
	Window(int width, int height, const char* title, int samples = 4, int version_major = 4, int version_minor = 6) : window() {
		glfwInit();
		window_hints(samples, version_major, version_minor);
		create_window(window, nullptr, width, height, title);

		window_height = height;
		window_width = width;
		window_title = title;
		msaa_samples = samples;

		glfwGetWindowPos(window, &window_x, &window_y);
		glfwGetWindowSize(window, &window_width, &window_height);
	}
	~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void window_hints(int samples = 4, int version_major = 4, int version_minor = 6, bool fullscreen = false) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, samples);
	}

	void create_window(GLFWwindow* &window, GLFWmonitor* monitor, int w, int h, const char* t) {
		window = glfwCreateWindow(w, h, t, monitor, nullptr);
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

	void enable_vsync() {
		glfwSwapInterval(1);
	}

	void enable_msaa() {
		check(glEnable(GL_MULTISAMPLE));
	}

	void disable_msaa() {
		check(glDisable(GL_MULTISAMPLE));
	}

	void update_when_resized() {
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			check(glViewport(0, 0, width, height));
		});
	}

	void default_setup() {
		create_context();
		load_opengl();
		enable_vsync();
		enable_msaa();
		update_when_resized();
	}

	void info() {
	#ifdef DEBUG
		std::cout << "Debug build\n";
	#else
		std::cout << "Release build\n";
	#endif
		std::cout << msaa_samples << "x MSAA\n";

		std::cout << "---\n\n";
	}

	void should_close(bool should_close) {
		glfwSetWindowShouldClose(window, true);
	}

	void fullscreen(bool fullscreen) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		if (fullscreen) {
			glfwGetWindowPos(window, &window_x, &window_y);
			glfwGetWindowSize(window, &window_width, &window_height);
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
		}
		else
			glfwSetWindowMonitor(window, nullptr, window_x, window_y, window_width, window_height, 0);
	}

	void set_key_callback(GLFWkeyfun key_callback) {
		glfwSetKeyCallback(window, key_callback);
	}
};
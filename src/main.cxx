#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Renderer.h"
#include "Mesh.h"

float cube[108]{
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

int main() {
	Window window(800, 600, "OpenGL");
	window.default_setup();

	Renderer renderer;
	Mesh3D mesh(cube, 108);
	
	Shader shader("res/shaders/default.glsl");
	shader.get_errors();
	shader.use();

    mesh.set_scale(0.5f, 0.5f, 0.5f);
    mesh.set_translation(0.0f, 0.0f, -4.0f);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    int transform_location = shader.uniform_location("transform");
    int projection_location = shader.uniform_location("projection");

    shader.set_uniform_matrix4f(projection_location, glm::value_ptr(projection));



	while (!window.should_close()) {
		renderer.clear_colour(0.1f, 0.1f, 0.1f);
		mesh.draw();

        mesh.set_rotation_x((float)sin(glfwGetTime()));
        mesh.set_rotation_y((float)sin(glfwGetTime()));
        mesh.set_rotation_z((float)cos(glfwGetTime())*2);

        shader.set_uniform_matrix4f(transform_location, glm::value_ptr(mesh.transform));

		window.swap_buffers();
		window.poll_events();
	}

	return 0;
}
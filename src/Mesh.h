#pragma once

#include <iostream>
#include "Vao.h"
#include "Vbo.h"
#include <glm/glm.hpp>

class Mesh2D {
public:
	float* vertices;
	int vertex_count;
	Vao vertex_array;
	Vbo buffer;

public:
	Mesh2D(float* verts, int float_count) {
		vertices = verts;
		vertex_count = float_count;
		vertex_array.bind();
		buffer.bind();
		recreate();
	}

	void recreate() {
		buffer.data(vertex_count * sizeof(float), vertices);
		vertex_array.vertex_attrib_ptr(0, 2, 2 * sizeof(float));
	}

	void draw() {
		vertex_array.draw_arrays(vertex_count / 2);
	}
};

class Mesh3D {
public:
	float* vertices;
	int vertex_count;
	Vao vertex_array;
	Vbo buffer;
	glm::mat4 transform = glm::mat4(1.0f);

public:
	Mesh3D(float* verts, int float_count) {
		vertices = verts;
		vertex_count = float_count;
		vertex_array.bind();
		buffer.bind();
		recreate();
	}

	void recreate() {
		buffer.data(vertex_count * sizeof(float), vertices);
		vertex_array.vertex_attrib_ptr(0, 3, 3 * sizeof(float));
	}

	void draw() {
		vertex_array.draw_arrays(vertex_count / 3);
	}

	void set_scale(float x, float y, float z) {
		transform = glm::scale(transform, glm::vec3(x, y, z));
	}

	void set_translation(float x, float y, float z) {
		transform = glm::translate(transform, glm::vec3(x, y, z));
	}

	void set_rotation_x(float degrees) {
		transform = glm::rotate(transform, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void set_rotation_y(float degrees) {
		transform = glm::rotate(transform, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void set_rotation_z(float degrees) {
		transform = glm::rotate(transform, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
	}
};
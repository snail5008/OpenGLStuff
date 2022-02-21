#pragma once

#include <glad/glad.h>
#include "Errors.h"

class Vbo {
public:
	unsigned int buffer;
public:
	Vbo(): buffer() {
		check(glGenBuffers(1, &buffer));
	}

	~Vbo() {
		check(glDeleteBuffers(1, &buffer));
	}

	void bind(int target = GL_ARRAY_BUFFER) {
		check(glBindBuffer(target, buffer));
	}

	void unbind() {
		check(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void data(long long int size, const void* data, int usage = GL_STATIC_DRAW, unsigned int target = GL_ARRAY_BUFFER) {
		check(glBufferData(target, size, data, usage));
	}
};
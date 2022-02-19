#pragma once

#include <glad/glad.h>

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

	void bind(int target = GL_STATIC_DRAW) {
		check(glBindBuffer(target, buffer));
	}

	void data(long long int size, const void* data, int usage = GL_STATIC_DRAW, unsigned int target = GL_ARRAY_BUFFER, bool should_bind=true) {
		if (should_bind)
			bind(target);
		check(glBufferData(target, size, data, usage));
	}
};
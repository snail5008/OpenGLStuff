#pragma once

#include <glad/glad.h>
#include "Errors.h"

class Vao {
public:
	unsigned int vao;
	enum VERTEX_DIMS { ONE_DIMENSIONAL = 1, TWO_DIMENSIONAL, THREE_DIMENSIONAL, FOUR_DIMENSIONAL };
public:
	Vao(): vao() {
		check(glGenVertexArrays(1, &vao));
	}

	~Vao() {
		check(glDeleteVertexArrays(1, &vao));
	}

	void bind() {
		check(glBindVertexArray(vao));
	}

	void vertex_attrib_ptr(int idx, int size, int stride, int type = GL_FLOAT, const void* pointer = 0, bool normalised = false) {
		bind();
		check(glEnableVertexAttribArray(idx));
		check(glVertexAttribPointer(idx, size, type, normalised, stride, pointer));
	}

	// @param count: the amount of verts
	// @param mode: the primarive to draw with (def. GL_TRIANGLES)
	// @param first: the vert to start drawing at
	void draw_arrays(int count, unsigned int mode = GL_TRIANGLES, int first = 0) {
		bind();
		check(glDrawArrays(mode, first, count));
	}
};
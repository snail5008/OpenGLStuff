#pragma once

#include <glad/glad.h>
#include "Vbo.h"
#include "Vao.h"
#include "Shader.h"
#include "Primitives.h"

class Renderer {
public:
	Renderer() {

	}

	~Renderer() {

	}

	void clear_colour(float red, float green, float blue) {
		check(glClearColor(red, green, blue, 1.0f));
		check(glClear(GL_COLOR_BUFFER_BIT));
	}

	void wireframe(bool use_wireframe) {
		if (use_wireframe) {
			check(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		else {
			check(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
	}
};
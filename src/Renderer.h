#pragma once

#include <glad/glad.h>
#include "Vbo.h"
#include "Shader.h"

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
};
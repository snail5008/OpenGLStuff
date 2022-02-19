#pragma once

#include <glad/glad.h>
#include <iostream>

#define check(fn) clearErrors();fn;getError(__func__, __FILE__, __LINE__);

void clearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

bool getError(const char* fn, const char* file, int line) {
	unsigned int e = glGetError();
	while (e) {
		std::cout << "Error: " << e << " in function '" << fn << " in file '" << file << "' on line " << line << '\n';
		return false;
	}
	return true;
}
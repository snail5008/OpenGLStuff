#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Errors.h"




class Shader {
public:
	const char* vertex_source;
	const char* fragment_source;

	unsigned int vertex_shader;
	unsigned int fragment_shader;

	unsigned int program;

public:
	Shader(std::string& vertex_src, std::string& fragment_src) {
		vertex_source = vertex_src.c_str();
		fragment_source = fragment_src.c_str();

		check(vertex_shader = glCreateShader(GL_VERTEX_SHADER));
		check(fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));

		check(glShaderSource(vertex_shader, 1, &vertex_source, nullptr));
		check(glShaderSource(fragment_shader, 1, &fragment_source, nullptr));

		check(glCompileShader(vertex_shader));
		check(glCompileShader(fragment_shader));


		check(program = glCreateProgram());

		check(glAttachShader(program, vertex_shader));
		check(glAttachShader(program, fragment_shader));

		check(glLinkProgram(program));
		check(check(glValidateProgram(program)));

		check(glDeleteShader(vertex_shader));
		check(glDeleteShader(fragment_shader));
	}

	Shader(std::string filename) {
		std::ifstream file(filename);
		std::string line;

		std::stringstream vertex_src;
		std::stringstream fragment_src;

		
		/*
			0 - nothing selected
			1 - vertex shader
			2 - fragment shader
		*/
		char current_shadertype = 0;

		while (getline(file, line)) {

			if (line.find("#[vertex]") != std::string::npos) {
				current_shadertype = 1;
				continue;
			}

			else if (line.find("#[fragment]") != std::string::npos) {
				current_shadertype = 2;
				continue;
			}

			if (current_shadertype == 1) {
				vertex_src << line << '\n';
			}

			else if (current_shadertype == 2) {
				fragment_src << line << '\n';
			}

		}


		std::string vertex_source_string = vertex_src.str();
		std::string fragment_source_string = fragment_src.str();
		vertex_source = vertex_source_string.c_str();
		fragment_source = fragment_source_string.c_str();


		check(vertex_shader = glCreateShader(GL_VERTEX_SHADER));
		check(fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));

		check(glShaderSource(vertex_shader, 1, &vertex_source, nullptr));
		check(glShaderSource(fragment_shader, 1, &fragment_source, nullptr));

		check(glCompileShader(vertex_shader));
		check(glCompileShader(fragment_shader));


		check(program = glCreateProgram());

		check(glAttachShader(program, vertex_shader));
		check(glAttachShader(program, fragment_shader));

		check(glLinkProgram(program));
		check(glValidateProgram(program));

		check(glDeleteShader(vertex_shader));
		check(glDeleteShader(fragment_shader));
	}

	void get_errors() {
		int success;
		char message[1024];


		check(glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success));
		if (!success) {
			check(glGetShaderInfoLog(vertex_shader, 1024, 0, message));

			std::cout << "--- vertex shader failed to compile ---\n\n" << message << "--------\n\n";
		}
		else
			std::cout << "vertex shader successfully compiled\n";


		check(glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success));
		if (!success) {
			check(glGetShaderInfoLog(fragment_shader, 1024, 0, message));

			std::cout << "--- fragment shader failed to compile ---\n\n" << message << "--------\n\n";
		}
		else
			std::cout << "fragment shader successfully compiled\n";

		check(glGetProgramiv(program, GL_LINK_STATUS, &success));
		if (!success) {
			check(glGetShaderInfoLog(program, 1024, 0, message));

			std::cout << "--- shader program failed to link ---\n\n" << message << "--------\n\n";
		}
		else
			std::cout << "shader program linked successfully\n";
	}
	
	~Shader() {
		check(glDeleteProgram(program));
	}

	void use() {
		check(glUseProgram(program));
	}

	int uniform_location(const char* uniform_name) {
		check(return glGetUniformLocation(program, uniform_name));
	}
};
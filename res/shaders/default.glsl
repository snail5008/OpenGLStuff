#[vertex]
#version 460 core
layout(location = 0) in vec3 pos;

uniform mat4 transform;
uniform mat4 projection;

void main() {
	gl_Position = projection * transform * vec4(pos, 1);
}

#[fragment]
#version 460 core
out vec3 color;

void main() {
	color = vec3(0.3, 0.6, 0.4);
}
#[vertex]
#version 460 core
layout(location = 0) in vec3 pos;
void main() {
	gl_Position.xyz = pos;
	gl_Position.w = 1.0;
}


#[fragment]
#version 460 core
out vec3 color;
void main() {
	color = vec3(0.2, 0.8, 0.3);
}
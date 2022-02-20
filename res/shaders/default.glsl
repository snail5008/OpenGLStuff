#[vertex]
#version 460 core
layout(location = 0) in vec3 pos;

uniform float u_Time;

void main() {
	gl_Position.xyz = pos*abs(sin(u_Time));
	gl_Position.w = 1;
}


#[fragment]
#version 460 core
out vec3 color;

uniform float u_Time;

void main() {
	color = vec3(abs(cos(u_Time*0.5)), 0.9, abs(sin(u_Time)));
}
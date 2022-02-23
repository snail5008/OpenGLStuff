#[vertex]
#version 460 core
layout(location = 0) in vec3 pos;

uniform float u_Time;
uniform bool u_AnimationDisabled;

void main() {
	if (!u_AnimationDisabled)
		gl_Position.xyz = pos*sin(abs((u_Time)));
	else
		gl_Position.xyz = pos;
		
	gl_Position.w = 1;
}


#[fragment]
#version 460 core
out vec3 color;

uniform float u_Time;
uniform bool u_AnimationDisabled;

void main() {
	if (!u_AnimationDisabled)
		color = vec3(abs(cos(u_Time*0.5)), 0.9, abs(sin(u_Time)));
	else
		color = vec3(0.6, 0.6, 1);
}
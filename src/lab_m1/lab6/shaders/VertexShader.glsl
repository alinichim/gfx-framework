#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 vertex_position;
in vec3 vertex_color;
in vec3 vertex_normal;
in vec3 vertex_texture;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_texture;
out vec3 frag_color;

void main()
{
    // TODO(student): Send output to fragment shader
    frag_color = vertex_color + vec3(sin(Time), cos(Time), sin(Time));
    frag_position = vertex_position + vec3(sin(Time), cos(Time), sin(Time));
    frag_normal = vertex_normal;
    frag_texture = vertex_texture;

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(vertex_position, 1.0) + vec4(sin(Time), cos(Time), sin(Time), 0);

}

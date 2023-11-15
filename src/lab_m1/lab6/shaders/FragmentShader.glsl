#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_normal;
in vec3 frag_texture;
in vec3 frag_color;

// Output
out vec3 vertex_color;
out vec3 vertex_normal;
out vec3 vertex_texture;


void main()
{
    // TODO(student): Write pixel out color
    vertex_color = frag_color;
    vertex_normal = frag_normal;

}

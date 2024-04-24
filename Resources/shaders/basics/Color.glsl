#type vertex
#version 330 core

// In this Color.glsl demonstrates how to set a color from OpenGL to GLSL

// If you want to set a color from OpenGL to GLSL you can use the vertex shader
//  for setting the vertex buffer
//  Vertex Buffer would be used for any thing geometry-related.

// Fragment shaders is where you set the pixels and the way things are rendered.

// These are our attributes
// These are accessed by specifying the location
// In this case location of this attribute is at index 0
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec3 v_Position;
out vec4 v_Color; 

// Something to Note is that gl_Position is vec4 by default!
// If we convert position to vec3 then we get unexpected compilation error with this shader
void main(){
    v_Position = a_Position;
    v_Color = a_Color;
    gl_Position = vec4(a_Position, 1.0);
}

#type fragment
#version 330 

out vec4 a_Color;

// we set this u_Color variable in the OpenGL code
uniform vec4 u_Color;

void main(){
    a_Color = u_Color;
}
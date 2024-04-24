#type vertex
#version 330 core
// These are our attributes
// These are accessed by specifying the location
// In this case location of this attribute is at index 0
layout(location = 0) in vec3 position;

// Something to Note is that gl_Position is vec4 by default!
// If we convert position to vec3 then we get unexpected compilation error with this shader
void main(){
    gl_Position = vec4(position, 1.0);
}

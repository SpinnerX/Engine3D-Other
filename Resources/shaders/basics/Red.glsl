#type vertex
#version 330 core
// These are our attributes
// These are accessed by specifying the location
// In this case location of this attribute is at index 0
layout(location = 0) in vec3 position;

void main(){
    gl_Position = position;
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

void main(){

    // The color we are outputting
    color = vec4(1.0, 0.0, 0.0, 1.0);
}
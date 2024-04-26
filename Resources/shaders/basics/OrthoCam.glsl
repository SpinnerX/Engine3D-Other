#type vertex
#version 330 core

// These are the locations that we specify in our vertex array attributes
// Keep in mind setting this up you must specify these in your buffer layouts
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

// This is what is specified in OpenGL Code.
out vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
    gl_Position = proj * view * model * vec4(a_Position, 1.0);
    v_TexCoord = a_TexCoord;
    // gl_Position = vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

// This is what will be your output that you'll be using in your OpenGL code.
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
// uniform vec3 u_Color;
// This tells us that the texture sampler
// Essentially used when creating a 2D Texture
uniform sampler2D u_Texture;

void main(){
    // color = vec4(v_TexCoord, 0.0, 1.0);
    color = texture(u_Texture, v_TexCoord);
}
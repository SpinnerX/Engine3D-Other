#type vertex
#version 330 core

// These are the locations that we specify in our vertex array attributes
// Keep in mind setting this up you must specify these in your buffer layouts
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

// This is what is specified in OpenGL Code.
out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;

void main(){
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
    v_TexIndex = a_TexIndex;
    // gl_Position = vec4(a_Position, 1.0);
    gl_Position = vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

// This is what will be your output that you'll be using in your OpenGL code.
layout(location = 0) out vec4 color;


in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
// uniform vec3 u_Color;
// This tells us that the texture sampler
// Essentially used when creating a 2D Texture
// This is an array of textures to be read
// uniform sampler2D u_Texture;

uniform sampler2D u_Textures[32];

void main(){
    // color = vec4(v_TexCoord, 0.0, 1.0);
    color = texture(u_Textures[int(v_TexIndex)], v_TexCoord) * v_Color;
}
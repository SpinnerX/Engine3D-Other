#type vertex
#version 330 core

// -- Overview --
// -- When using glsl, you set your geometry information through vertex shaders
// -- And fragment shaders are where you set how they'll be rendering
// -- In other words, pixel and color data would be used there
// -- vertex shaders are how you can set the information of the geometry to render using fragment shaders

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

//! @note These are geomeotry information set by OpenGL
//! @note How we set our positions
out vec3 v_Position;
out vec4 v_Color;
out vec2 v_TexCoord;

// Something to Note is that gl_Position is vec4 by default!
// If we convert position to vec3 then we get unexpected compilation error with this shader
void main(){
    v_Position = a_Position;
    v_Color = a_Color;
    gl_Position = vec4(a_Position, 1.0);
}

#type fragment
#version 330 

in vec4 a_Color;
in vec3 a_TexCoord; // our actual texture

// NOTE -- we set this u_Color, u_TexCoord variables are set in the OpenGL code
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){
    a_Color = u_Color;
    u_TexCoord = texture(u_Texture, a_TexCoord);
}
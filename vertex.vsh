#version 120

// Input vertex data
attribute vec3 vPosition;
attribute vec3 vertexColor;

// Output data
varying vec3 fragmentColor;

// Uniform data
uniform mat4 MVP;
uniform vec3 move;

void main() {
    gl_Position = MVP * vec4(vPosition, 1);
    fragmentColor = vertexColor;
}

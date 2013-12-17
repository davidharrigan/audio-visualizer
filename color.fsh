#version 330 core

// interpolated values from vertex shaders
//in vec3 fragmentColor;

// output
//out vec3 color;
uniform vec4 color

void main() {
    //color = fragmentColor;
    gl_FragColor = color;
}

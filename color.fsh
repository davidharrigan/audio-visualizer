#version 330 core

in vec3 fragmentColor;
out vec3 color;

void main() {
    //gl_FragColor = color;
    //gl_FragColor = vec4(fragmentColor, 1);
    //color = vec3(0,0,1);
    color = fragmentColor;
}

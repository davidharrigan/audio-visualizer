#version 120

uniform vec3 fragmentColor;

void main() {
    //gl_FragColor = color;
    gl_FragColor = vec4(fragmentColor, 1);
}

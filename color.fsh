#version 120

// Output data
varying vec3 fragmentColor;

void main() {
    gl_FragColor = vec4(fragmentColor, 1);
}

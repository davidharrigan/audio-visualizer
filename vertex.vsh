

uniform mat4 projXmv;
attribute vec4 vPosition;

void main() {
    gl_Position = projXmv * vPosition;
}

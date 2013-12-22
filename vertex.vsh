#version 120

// Input vertex data
attribute vec3 vPosition;

// Output data
varying vec3 normal, light, halfVector;
varying vec4 diffuse, ambient;
varying vec4 fragmentColor;

// Uniform data
uniform mat4 MVP;
uniform mat4 translation;
uniform mat4 scale;
uniform vec4 vertexColor;

void main() {
    float freq = scale[1][1];

    mat4 transform = translation * scale;
    vec4 v = transform * vec4(vPosition, 1);
    gl_Position = MVP * v; 
   
    normal = normalize(gl_NormalMatrix * gl_Normal);
    light  = normalize(vec3(gl_LightSource[0].position));
    halfVector = normalize(gl_LightSource[0].halfVector.xyz);

    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient * vertexColor;

    fragmentColor = vertexColor;
}

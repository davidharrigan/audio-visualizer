#version 120

// Output data
varying vec4 diffuse, ambient, fragmentColor;
varying vec3 normal, light, halfVector;

void main() {

    vec3 n, hv;
    vec4 color = ambient;
    float intensity, hv_intensity;
    
    n = normalize(normal);
    intensity = max(dot(n, light), 0.0);

    if (intensity > 0.0) {
        color += diffuse*intensity;
        hv = normalize(halfVector);
        hv_intensity = max(dot(n,hv),0.0);
        color += gl_FrontMaterial.specular*gl_LightSource[0].specular*pow(hv_intensity,gl_FrontMaterial.shininess);
    }

    gl_FragColor = fragmentColor;
}

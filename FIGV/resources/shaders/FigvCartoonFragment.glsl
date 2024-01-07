#version 400

in vec3 position;
in vec3 normal;
// FIGV 4

uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform vec3 lightPosition;

uniform vec3 cameraPosition;

uniform bool solidColor;
uniform int levels;
uniform float threshold;
uniform float multiplier;

// FIGV 5

layout (location = 0) out vec4 fragColor;

// FIGV 6
vec3 cartoon()
{
    vec3 n = normalize( normal );
    vec3 v = normalize( cameraPosition - position );
    float edge = step(fwidth(dot(v, n)) * multiplier, threshold );
    
    vec3 color;
    if (solidColor) {
        color = vec3(1.0);
    } else {
        vec3 l = normalize( lightPosition - position );
        float diff = max(dot(n, l), 0.0f);
        float quantizedDiff = floor(diff * levels) / (levels-1);

        vec3 diffuse = quantizedDiff * Id;
        // FIGV 7
        color = (Ia + diffuse) * Kd;
    }
    return color * edge;
}

void main() {
    // FIGV 8
    fragColor = vec4(cartoon(), 1.0);
}


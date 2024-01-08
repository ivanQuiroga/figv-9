#version 400
in vec3 normal; 
in vec3 position; 

uniform vec3 skyColor; 
uniform vec3 groundColor; 
uniform vec3 lightDirection; 

layout (location = 0) out vec4 fragColor; 

void main()
{
    vec3 norm = normalize(normal); 
    vec3 lightDir = normalize(lightDirection);

    float factor = dot(norm, lightDir) * 0.5 + 0.5;
    vec3 color = mix(groundColor, skyColor, factor);

    fragColor = vec4(color, 1.0); 
}

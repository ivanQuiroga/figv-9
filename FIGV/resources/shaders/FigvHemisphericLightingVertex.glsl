#version 400

layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal;

out vec3 normal; 
out vec3 position; 

uniform mat4 mModel; 
uniform mat4 mViewProjection;

void main()
{
    position = vec3(mModel * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(mModel))) * aNormal;
    gl_Position = mViewProjection * vec4(position, 1.0); 
}

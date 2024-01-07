#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
// FIGV 1

uniform mat4 mViewProjection;
uniform mat4 mModel;

out vec3 position;
out vec3 normal;
// FIGV 2

void main() {
    normal = vec3(mModel * vec4(vNormal, 0.0));
    position = vec3(mModel * vec4(vPosition, 1.0));
    // FIGV 3
    gl_Position = (mViewProjection * mModel) * vec4(vPosition, 1.0);
}


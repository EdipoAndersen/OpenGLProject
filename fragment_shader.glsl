#version 330 core

in vec3 vertexColor;  // Interpolated color from the vertex shader

out vec4 FragColor;

void main() {
    FragColor = vec4(vertexColor, 1.0);  // Final fragment color
}

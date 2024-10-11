#version 330 core

layout (location = 0) in vec3 aPos;     // Posição dos vértices
layout (location = 1) in vec3 aNormal;  // Normais para iluminação

out vec3 FragPos;  // Posição no espaço mundial
out vec3 Normal;   // Normal para o cálculo de iluminação

uniform mat4 model;       // Matriz de modelagem
uniform mat4 view;        // Matriz de visualização
uniform mat4 projection;  // Matriz de projeção

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

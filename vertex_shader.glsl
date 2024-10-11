#version 330 core

layout (location = 0) in vec3 aPos;     // Posi��o dos v�rtices
layout (location = 1) in vec3 aNormal;  // Normais para ilumina��o

out vec3 FragPos;  // Posi��o no espa�o mundial
out vec3 Normal;   // Normal para o c�lculo de ilumina��o

uniform mat4 model;       // Matriz de modelagem
uniform mat4 view;        // Matriz de visualiza��o
uniform mat4 projection;  // Matriz de proje��o

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

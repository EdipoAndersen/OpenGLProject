#version 330 core
out vec4 FragColor;

in vec3 FragPos;  // Posição do fragmento no espaço do mundo
in vec3 Normal;   // Normal interpolada

uniform vec3 lightPos;  // Posição da luz
uniform vec3 viewPos;   // Posição da câmera
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // Propriedades do material
    float shininess = 32.0f;

    // Iluminação ambiente
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Iluminação difusa
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Iluminação especular (Blinn-Phong)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = spec * lightColor;

    // Combinar os três componentes de iluminação
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
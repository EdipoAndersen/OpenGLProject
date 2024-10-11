#version 330 core

in vec3 FragPos;  
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;    // Posição da luz
uniform vec3 viewPos;     // Posição da câmera
uniform vec3 lightColor;  // Cor da luz
uniform vec3 objectColor; // Cor do objeto

void main() {
    // Componente de iluminação ambiente
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Componente de iluminação difusa (modelo de Lambert)
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Componente de iluminação especular (reflexão Phong)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    
    // Resultado final
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}

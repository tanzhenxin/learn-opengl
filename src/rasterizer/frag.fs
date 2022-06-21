#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Light {
    vec3 pos;
    vec3 color;
    float ambient;
};

struct Material {
    vec3 ka;
    vec3 kd;
    vec3 ks;
    
    float shininess;
};

uniform sampler2D texture1;
uniform vec3 eyePos;
uniform Light lights[2];
uniform Material material;

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(eyePos - FragPos);
    
    vec3 result = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < 2; ++i)
        result += CalcPointLight(lights[i], norm, FragPos, viewDir);
        
    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.pos - fragPos);
    
    // light intensity
    float distance = length(light.pos - fragPos);
    float attenuation = 1.0 / (distance * distance);
    vec3 I = light.color * attenuation;
    
    // ambient
    vec3 ambient = light.color * light.ambient * material.ka;
    
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = I * diff * vec3(texture(texture1, TexCoords));
    
    // specular
    vec3 halfDir = normalize(viewDir + lightDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), material.shininess);
    vec3 specular = I * spec * material.ks;
    
    return (ambient + diffuse + specular);
}

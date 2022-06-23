#ifndef RENDER_RASTERIZER_H
#define RENDER_RASTERIZER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/model.h>
#include <core/camera.h>
#include <core/shader_m.h>

// lights
struct Light {
    glm::vec3 pos;
    glm::vec3 color;
    float ambient;
};

struct Material {
    glm::vec3 ka;
    glm::vec3 kd;
    glm::vec3 ks;
    float shininess;
    
    string texture_diffuse;
    string texture_specular;
    string texture_bump;
};

class Rasterizer {
public:
    Rasterizer() {
        this->window = this->initialize();
    }
    
    GLFWwindow* initialize();
    
    int draw(Camera &camera, std::vector<Light> lights, Model &model, Material &material, Shader &shader);
    
private:
//    Camera *camera;
//    std::vector<Light> lights;
    GLFWwindow *window;
};

#endif

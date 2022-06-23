#include <render/rasterizer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/filesystem.h>
#include <core/shader_m.h>
#include <core/camera.h>
#include <core/model.h>

#include <iostream>

int main()
{
    Rasterizer rasterizer;
    
    // camera
    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

    // lights
    std::vector<Light> lights = {
        {glm::vec3(20.f, 20.f, 20.f), glm::vec3(500.f, 500.f, 500.f), 0.02},
        {glm::vec3(-20.f, 20.f, 0.f), glm::vec3(500.f, 500.f, 500.f), 0.02},
    };

    // load models
    // -----------
    string modelPath = FileSystem::getPath("resources/objects/spot/spot_triangulated_good.obj");
    Model ourModel(modelPath);
    
    // load material
    Material material{
        glm::vec3(0.005, 0.005, 0.005),
        glm::vec3(148.f/255.f,121.f/255.f,92.f/255.f),
        glm::vec3(0.7937, 0.7937, 0.7937),
        150.f,
        
        FileSystem::getPath("resources/objects/spot/spot_texture.png")
    };
    
    // build and compile shaders
    // -------------------------
    Shader ourShader("vertex.vs", "frag.fs");
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
    model = glm::rotate(model, glm::radians(140.f), glm::vec3(0.f, 1.f, 0.f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    
    ourShader.use();
    ourShader.setMat4("model", model);
    
    return rasterizer.draw(camera, lights, ourModel, material, ourShader);
}

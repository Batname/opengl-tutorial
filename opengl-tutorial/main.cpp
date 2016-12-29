// c lib
#include <stdio.h>
#include <stdlib.h>

// c++ standart lib
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM for math
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

int main(int argc, const char * argv[]) {
    // init glfw
    if (!glfwInit()) {
        fprintf(stderr, "Failed to init glfw\n");
        return EXIT_FAILURE;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    GLFWwindow * window;
    window = glfwCreateWindow(1024, 786, "Tutorial 01", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failad to open GLFW window\n");
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failad init GLEW \n");
        return EXIT_FAILURE;
    }
    
    // glfw settings
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    do{
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    

    return 0;
}

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

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, +0.0f,
    +1.0f, -1.0f, +0.0f,
    +1.0f, +1.0f, +0.0f
};

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
    
    // init binding open gl
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    GLuint VertexBufferID;
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    do{
        glfwPollEvents();

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (GLvoid *)0
        );
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(window);
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    

    return 0;
}

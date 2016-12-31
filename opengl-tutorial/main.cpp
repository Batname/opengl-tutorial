// c lib
#include <stdio.h>
#include <stdlib.h>

// c++ standart lib
#include <iostream>
#include <vector>
#include <fstream>

// for accert
#include <cassert>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM for math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// local files
#include "LoadShaders.h"

using namespace std;
using namespace glm;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, +0.0f,
    +1.0f, -1.0f, +0.0f,
    +0.0f, +1.0f, +0.0f
};

int WIDTH = 1024, HEIGHT = 786;

int main(int argc, const char * argv[]) {

    assert(glfwInit() && "Failed to init glfw");
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    GLFWwindow * window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Tutorial 01", NULL, NULL);
    
    assert(window && "Failad to open GLFW window");

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    assert((glewInit() == GLEW_OK) && "Failad init GLEW");
    
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
    GLuint programID = LoadShaders("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    
    do{
        // setup matrix coordinates
        mat4 Projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        mat4 View = glm::lookAt(
            vec3(4.0f, 3.0f, 3.0f),
            vec3(0.0f, 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f)
        );
        mat4 Model = mat4(1.0f);
        mat4 mvp = Projection * View * Model;

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        glUseProgram(programID);
        
        glUniformMatrix4fv(
            glGetUniformLocation(programID, "MVP"),
            1,
            GL_FALSE,
            ((float *)((vec4 *)(&mvp) + 0) + 0) // == &mvp[0][0]
        );
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(window);
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    

    return 0;
}

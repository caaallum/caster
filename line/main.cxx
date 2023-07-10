#include <iostream>
#include <vector>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
 
using glm::mat4;
using glm::vec3;
using glm::radians;
using glm::lookAt;
using std::vector;
 
void processInput(GLFWwindow *window);
 
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
 
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
 
// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;
 
class Camera {
public:
    vec3 position;
    Camera() {
        position = vec3(0,0,0);
    }
};
Camera camera;
 
class Line {
    int shaderProgram;
    unsigned int VBO, VAO;
    vector<float> vertices;
    vec3 startPoint;
    vec3 endPoint;
    mat4 MVP = mat4(1.0);
    vec3 lineColor;
public:
    Line(vec3 start, vec3 end) {
 
        startPoint = start;
        endPoint = end;
        lineColor = vec3(1,1,1);
 
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform mat4 MVP;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec3 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(color, 1.0f);\n"
            "}\n\0";
 
        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
 
        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
 
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
 
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
 
        vertices = {
             start.x, start.y, start.z,
             end.x, end.y, end.z,
        };
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
 
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
 
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
 
    }
 
    int setMVP(mat4 mvp) {
        MVP = mvp;
        return 1;
    }
 
    int setColor(vec3 color) {
        lineColor = color;
        return 1;
    }
 
    int draw() {
        glUseProgram(shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        return 1;
    }
 
    ~Line() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }
};
 
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
 
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Line", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
 
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    camera.position = vec3(3,3,3);
 
    // 3d lines example
    Line line1(vec3(0,0,0), vec3(1,0,0));
    line1.setColor(vec3(1,0,0));
    Line line2(vec3(0,0,0), vec3(0,1,0));
    line2.setColor(vec3(0,1,0));
    Line line3(vec3(0,0,0), vec3(0,0,1));
    line3.setColor(vec3(0,0,1));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
 
    float angle = 0.0f;
    float rotationSpeed = 50.0f;
 
    // 2d line example
    vec3 start = vec3(10,10,0);
    vec3 end = vec3(20,20,0);
 
    float x1 = start.x;
    float y1 = start.y;
    float x2 = end.x;
    float y2 = end.y;
    float w = SCR_WIDTH;
    float h = SCR_HEIGHT;
 
    // convert 3d world space position 2d screen space position
    x1 = 2*x1 / w - 1;
    y1 = 2*y1 / h - 1;
 
    x2 = 2*x2 / w - 1;
    y2 = 2*y2 / h - 1;
 
    start.x = x1;
    start.y = y1;
    end.x = x2;
    end.y = y2;
 
    Line line4(start, end);
 
 
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        // input
        // -----
        processInput(window);
 
        // render
        // ------
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
 
        angle = deltaTime * rotationSpeed;
 
        // update camera position (rotating)
        camera.position = vec3(3*cos(radians(angle)), 3, 3*sin(radians(angle)));
        mat4 view = lookAt(camera.position, vec3(0,0,0), vec3(0,1,0));
 
 
        line1.setMVP(projection * view);
        line2.setMVP(projection * view);
        line3.setMVP(projection * view);
 
        line1.draw();
        line2.draw();
        line3.draw();

 
        line4.draw();
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
 
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
 
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

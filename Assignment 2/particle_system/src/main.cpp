#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

const char* vertexShaderSource = R"( 
#version 300 es
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aVelocity;
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aStartTime;

uniform float uTime;
uniform vec2 uResolution;

out vec4 vColor;
out float vLifetime;

void main() {
    float age = uTime - aStartTime;
    if(age < 0.0) {
        // Particle not born yet
        gl_Position = vec4(-2.0, -2.0, 0.0, 1.0);
        vColor = vec4(0.0);
        vLifetime = 0.0;
        return;
    }
    float lifetime = 5.0; // lifetime in seconds
    if(age > lifetime) {
        // Particle died
        gl_Position = vec4(-2.0, -2.0, 0.0, 1.0);
        vColor = vec4(0.0);
        vLifetime = 0.0;
        return;
    }
    vec2 position = aPos + aVelocity.xy * age;
    // Gravity effect
    position.y -= 9.8 * age * age * 0.5;

    vec2 clipPos = (position / uResolution) * 2.0 - 1.0;
    clipPos.y = -clipPos.y; // Flip Y for OpenGL coords

    gl_Position = vec4(clipPos, 0.0, 1.0);
    gl_PointSize = 10.0;

    vColor = aColor;
    vLifetime = 1.0 - age / lifetime;
}
)";

const char* fragmentShaderSource = R"(
#version 300 es
precision mediump float;

in vec4 vColor;
in float vLifetime;
out vec4 FragColor;

void main() {
    vec4 color = vColor;
    color.a *= vLifetime;
    FragColor = color;
}
)";

void checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "Shader Compilation Error (" << type << "):
" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "Program Linking Error (" << type << "):
" << infoLog << std::endl;
        }
    }
}

GLuint compileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
    return shader;
}

int main() {
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // Request OpenGL ES 3.0 context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GPU Particle System", NULL, NULL);
    if(!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD for OpenGL ES
    if(!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compile shaders and link program
    GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Particle data
    const int maxParticles = 1000;
    struct Particle {
        float x, y;
        float vx, vy, vz;
        float r, g, b, a;
        float startTime;
    };

    std::vector<Particle> particles(maxParticles);

    // Initialize particles at center with random velocities
    for(int i=0; i<maxParticles; ++i) {
        particles[i].x = 400.0f; // center screen x
        particles[i].y = 300.0f; // center screen y
        float angle = (float)i / maxParticles * 6.283185f;
        float speed = 100.0f + (rand() % 50);
        particles[i].vx = cos(angle) * speed;
        particles[i].vy = sin(angle) * speed;
        particles[i].vz = 0.0f;
        particles[i].r = (rand() % 100) / 100.0f;
        particles[i].g = (rand() % 100) / 100.0f;
        particles[i].b = (rand() % 100) / 100.0f;
        particles[i].a = 1.0f;
        particles[i].startTime = 0.0f;
    }

    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_DYNAMIC_DRAW);

    // Attribute 0: position (vec2)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, x));
    glEnableVertexAttribArray(0);

    // Attribute 1: velocity (vec3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, vx));
    glEnableVertexAttribArray(1);

    // Attribute 2: color (vec4)
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, r));
    glEnableVertexAttribArray(2);

    // Attribute 3: startTime (float)
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, startTime));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    float startTime = (float)glfwGetTime();

    while(!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime() - startTime;

        // Clear with additive blending for glow effect
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glUseProgram(shaderProgram);

        glUniform1f(glGetUniformLocation(shaderProgram, "uTime"), currentTime);
        glUniform2f(glGetUniformLocation(shaderProgram, "uResolution"), 800.0f, 600.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, maxParticles);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
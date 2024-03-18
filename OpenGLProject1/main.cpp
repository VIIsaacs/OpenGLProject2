#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Motion", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set up OpenGL viewport
    glViewport(0, 0, 800, 600);

    // Main rendering loop
    float velocity = 0.005f; // Decreased velocity for slower motion
    while (!glfwWindowShouldClose(window)) {
        // Input handling
        processInput(window);

        // Rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw shadow
        glColor3f(0.0f, 0.0f, 0.0f); // Black
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // Center of circle
        for (int i = 0; i <= 100; i++) {
            float theta = 2.0f * static_cast<float>(i) / static_cast<float>(100) * static_cast<float>(M_PI);
            float x = 0.5f * cosf(theta); // Slightly larger radius for the shadow
            float y = 0.5f * sinf(theta); // Slightly larger radius for the shadow
            glVertex2f(x, y);
        }
        glEnd();

        // Draw circle
        float radius = 0.5f;
        int numSegments = 100;
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(0.0f, 0.0f); // Center of circle
        for (int i = 0; i <= numSegments; i++) {
            float theta = 2.0f * static_cast<float>(i) / static_cast<float>(numSegments) * static_cast<float>(M_PI);
            float x = radius * cosf(theta);
            float y = radius * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();

        // Update circle position (e.g., translate horizontally)
        static float xpos = 0.0f;
        xpos += velocity;
        if (xpos > 1.0f || xpos < -1.0f) {
            velocity = -velocity; // Reverse direction when hitting window edges
        }

        glLoadIdentity();
        glTranslatef(xpos, 0.0f, 0.0f);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up GLFW
    glfwTerminate();
    return 0;
}

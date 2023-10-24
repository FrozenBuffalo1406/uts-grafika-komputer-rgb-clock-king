// main.cpp : This file contains the 'main' function.Program execution begins and ends there.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include "Util.h"

const float velocitySecondPointer = -6.0f / 2;
const float velocityMinutePointer = -0.1f / 2;
const float velocityHourPointer = -0.0083333f / 2;

float currentSecondPointer = 270.0f;
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

float inputHour, inputMinute, inputSecond;

unsigned int program;

GLint color1Loc, color2Loc, color3Loc;

float color1[] = { 1.0, 0.0, 0.0, 1.0 };
float color2[] = { 0.0, 1.0, 0.0, 1.0 };
float color3[] = { 0.0, 0.0, 1.0, 1.0 };

bool isKeyPressed = true;
float speed = 1.0f;
float current = speed;

int buttonHeld = 0;
double pressStartTime = 0.0;
double requiredHoldTime = 2.0; // The duration you want to hold the button (in seconds)


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //fast button
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        std::cout << "Speed set faster" << std::endl;
        speed += 5.0f;
        current = speed;
    }
    //slower button
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        std::cout << "Speed set slower" << std::endl;
        speed /= 1.8f;
        glfwSetTime(currentTime + speed);
        current = speed;

    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        std::cout << "Speed reset." << std::endl;
        speed = 1.0f;
        current = speed;

    }
    //pause/resume button
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (isKeyPressed) {
            std::cout << "Pause" << std::endl;
            speed = 0.0f;
            isKeyPressed = !isKeyPressed;
        }
        else {

            std::cout << "Resume" << std::endl;
            speed = current;
            isKeyPressed = !isKeyPressed;
        }
    }
    //randomize color
    else if (key == GLFW_KEY_C && action == GLFW_PRESS) {

        std::cout << "Randomize Color" << std::endl;
        for (int i = 0; i < 4; i++)
        {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
            color3[i] = (rand() * 1.0f) / RAND_MAX;
        }

        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
    }
    //randomize (hold) button
    else if (key == GLFW_KEY_C && action == GLFW_REPEAT)
    {
        std::cout << "Randomize Color" << std::endl;
        for (int i = 0; i < 4; i++)
        {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
            color3[i] = (rand() * 1.0f) / RAND_MAX;
        }

        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
    }

    //hour forward button
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        std::cout << "hour +1" << std::endl;
        glfwSetTime(currentTime + 3600);
    }

    //hour backward button
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        std::cout << "hour -1" << std::endl;
        glfwSetTime(currentTime - 3600);
    }

    //minute forward button
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        std::cout << "minute +1" << std::endl;
        glfwSetTime(currentTime + 60);
    }

    //hour forward button
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        std::cout << "minute -1" << std::endl;
        glfwSetTime(currentTime - 60);
    }

    //costum clock set button
    else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        float inputHour, inputMinute, inputSecond;
        std::cout << "Set Time: " << std::endl;
        std::cout << "Jam : ";
        std::cin >> inputHour;

        std::cout << "Menit : ";
        std::cin >> inputMinute;

        std::cout << "Detik : ";
        std::cin >> inputSecond;

        float hour = inputHour * 3600;
        float minute = inputMinute * 60;
        float second = inputSecond;
        glfwSetTime(hour + minute + second);

        cout << "Time has been Changed." << endl;
    }

    //terminate clock
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwTerminate();
        ExitProcess(0);
    }
   
    else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        if (!buttonHeld) {
            pressStartTime = glfwGetTime();
            buttonHeld = 1;
        }
    }
    else {
        buttonHeld = 0;
    }

    // Check if the button has been held for the required duration
    if (buttonHeld && (glfwGetTime() - pressStartTime >= requiredHoldTime)) {
        // Execute the step when the button has been held for the required duration
        // Replace this with your specific action

        std::cout << "Button held for %f seconds: " << requiredHoldTime << std::endl;
    }
}




int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(900, 900, "RGB Clock", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    float vertices[] = {
        1.0f, 1.0f,
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
    };
    const unsigned int verticesSize = sizeof(vertices) / sizeof(vertices[0]);

    unsigned int indexArr[] = {
        0, 1, 2,
        0, 2, 3
    };
    const unsigned int indexSize = sizeof(indexArr) / sizeof(indexArr[0]);

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesSize, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexSize, indexArr, GL_STATIC_DRAW);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);

    GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
    GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
    GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");

    color1Loc = glGetUniformLocation(program, "color1");
    glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);

    color2Loc = glGetUniformLocation(program, "color2");
    glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);

    color3Loc = glGetUniformLocation(program, "color3");
    glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime) * speed;
        lastTime = currentTime;

        currentSecondPointer += (deltaTime * velocitySecondPointer);
        currentMinutePointer += (deltaTime * velocityMinutePointer);
        currentHourPointer += (deltaTime * velocityHourPointer);

        glUniform1f(currentSecondPointerLoc, currentSecondPointer * 3.14159265f / 180.0f);
        glUniform1f(currentMinutePointerLoc, currentMinutePointer * 3.14159265f / 180.0f);
        glUniform1f(currentHourPointerLoc, currentHourPointer * 3.14159265f / 180.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
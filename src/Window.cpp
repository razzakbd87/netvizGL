#include <GL/glew.h>
#include "../inc/Renderable.h"
#include <iostream>
#include "../inc/Window.h"
#include "../inc/line.h"

//
// Created by werl on 21/09/16.
//

Window *Window::windowInstance = NULL;

Window *Window::Instance() {
    if (!windowInstance)   // Only allow one instance of class to be generated.
        windowInstance = new Window(1280, 720);
    return windowInstance;
}


Window::Window(const int WIDTH, const int HEIGHT) {

    pitch = 0;
    heading = 0;
    bank = 0;

    translateX = 0;
    translateY = 0;
    translateZ = 1;

    mouseLEFT = false;
    mouseRIGHT = false;

    this->windowWidth = WIDTH;
    this->windowHeight = HEIGHT;

    GLInit();

    point = new Point(.01, 6, 6, 10, 10, 0);
    point2 = new Point(.01, 6, 6, 0, 0, 0);
    point3 = new Point(.01, 6, 6, 10, 10, 10);
    point4 = new Point(.01, 6, 6, 30, -5, 10);
    line = new Line(0, 0, 0, .1, .1, .1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Window::display() {
    while (!glfwWindowShouldClose(window)) {

        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        glClearColor(0.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        gluPerspective(45, (double) windowWidth / (double) windowHeight, .1, 100);
//
//        if(mouseLEFT || (mouseLEFT == mouseRIGHT)){
//            glRotatef(pitch, 1, 0, 0);
//            glTranslatef(translateX, translateY, -translateZ);
//            glRotatef(heading, 0, 1, 0);
//        }
//        if(mouseRIGHT){
//            glTranslatef(translateX, translateY, -translateZ);
//            glRotatef(pitch, 1, 0, 0);
//            glRotatef(heading, 0, 1, 0);
//        }

        glTranslatef(translateX, translateY, -translateZ);
        glRotatef(pitch, 1, 0, 0);
        glRotatef(heading, 0, 1, 0);

        glLineWidth(4.0);

        point->draw();
        point2->draw();
        point3->draw();
        point4->draw();
        line->draw();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void Window::GLInit() {

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
    }
    glfwWindowHint(GLFW_SAMPLES, 8);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(windowWidth, windowHeight, "netvizGL", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowPos(window, 320, 180);

    glewExperimental = GL_TRUE;

    GLenum err = glewInit();

    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glfwSetKeyCallback(window, keyPressedEvent);
    glfwSetMouseButtonCallback(window, mousePressedEvent);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    glfwSetCursorPosCallback(window, mousePositionEvent);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetScrollCallback(window, this->scrollEvent);


}

void Window::scrollEvent(GLFWwindow *window, double xoffset, double yoffset) {
    Window::Instance()->translateZ += yoffset / 16;
}

void Window::mousePressedEvent(GLFWwindow *window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        Window::Instance()->mouseRIGHT = true;
        //printf("GLFW_MOUSE_BUTTON_RIGHT::%d\n",Window::Instance()->mouseRIGHT);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        Window::Instance()->mouseRIGHT = false;
        //printf("GLFW_MOUSE_BUTTON_RIGHT::%d\n",Window::Instance()->mouseRIGHT);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        Window::Instance()->mouseLEFT = true;
        //printf("GLFW_MOUSE_BUTTON_LEFT::%d\n",Window::Instance()->mouseLEFT);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        Window::Instance()->mouseLEFT = false;
        //printf("GLFW_MOUSE_BUTTON_LEFT::%d\n",Window::Instance()->mouseLEFT);
    }
}

void Window::mousePositionEvent(GLFWwindow *window, double xpos, double ypos) {


    if (Window::Instance()->mouseLEFT || Window::Instance()->mouseRIGHT) {
        Window::Instance()->heading += (xpos - Window::Instance()->mouseX) / 8;
        Window::Instance()->pitch += (ypos - Window::Instance()->mouseY) / 8;
        Window::Instance()->mouseX = xpos;
        Window::Instance()->mouseY = ypos;
    }

    Window::Instance()->mouseX = xpos;
    Window::Instance()->mouseY = ypos;
}

void Window::keyPressedEvent(GLFWwindow *window, int key, int scancode, int action, int mode) {

    //printf("Window::keyPressedEvent::%d\n", key);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_LEFT) {
        Window::Instance()->translateX += .01;
    }
    if (key == GLFW_KEY_RIGHT) {
        Window::Instance()->translateX -= .01;
    }

    if (key == GLFW_KEY_DOWN) {
        Window::Instance()->translateY += .01;
    }
    if (key == GLFW_KEY_UP) {
        Window::Instance()->translateY -= .01;
    }

}



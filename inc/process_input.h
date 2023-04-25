#pragma once

#include <GLFW/glfw3.h>

void KeyCallbackSet(GLFWwindow* window, int key, int scancode, int action, int mods);
void KeyReciever();
void MouseCallbackSet(GLFWwindow* window, double xpos, double ypos);
void ESCKeyPressed();
void WireFrameKeyPressed();

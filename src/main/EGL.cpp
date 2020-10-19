// EGL.cpp: определяет точку входа для приложения.
//

#include "EGL.h"
#include "../external/FINI/fini.h"

using namespace std;
using namespace fini;
int main(int argc , char *args[])
{
    cFINIin file;

    cout << args[0] << endl;

    file.open("res/test.ini");
    file.print_fbuf();
    file.openGrup("12345678901234567");
    file.openGrup("Grupp");
    getchar();
    return 0;
    //GLFWwindow* window;

    ///* Initialize the library */
    //if (!glfwInit())
    //{
    //    cout << "Not ini GLFW " << " Preset All key " << endl;
    //    getchar();
    //    return -1;
    //}

    ///* Create a windowed mode window and its OpenGL context */
    //window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    //if (!window)
    //{
    //    glfwTerminate();
    //    return -1;
    //}

 
    ///* Make the window's context current */
    //glfwMakeContextCurrent(window);

    //InstructionSet::support_message("SSE", InstructionSet::SSE());

    //if (!gladLoadGL())
    //{
    //    cout << "glad not init " << " Preset All key " << endl;
    //    getchar();
    //    return 0;
    //}

    //cout << "OpenGL: " << GLVersion.major << " - " << GLVersion.minor << endl;

    //glClearColor(1.0, 0.0, 0.0, 0);

    ///* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(window))
    //{
    //    /* Render here */
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    /* Swap front and back buffers */
    //    glfwSwapBuffers(window);

    //    /* Poll for and process events */
    //    glfwPollEvents();
    //}

    //glfwTerminate();
    //return 0;
}

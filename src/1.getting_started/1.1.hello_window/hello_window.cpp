#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    // 调用glfwInit函数来初始化GLFW
    glfwInit();
    // glfwWindowHint函数来配置GLFW, 第一个参数代表选项的名称, 第二个参数代表选项的值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用核心模式: 只包含最新的功能, 不再需向后兼容特性

// 如果是Mac系统, 需要加上下面这行代码, 否则会报错
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
    glfwMakeContextCurrent(window);
    // 然而，当用户改变窗口的大小的时候，视口也应该被调整。这里注册一个回调函数，每当窗口被调整大小的时候，这个回调函数就会被调用。
    // 我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。这个回调函数的原型如下：
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    // 初始化GLAD, GLAD是用来管理OpenGL的函数指针的
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // render loop 渲染循环
    // -----------
    // glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，
    // 如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        // glClearColor来设置清空屏幕所用的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，
        // 可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。
        // 由于现在我们只关心颜色值，所以我们只清空颜色缓冲。
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        // glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
        // 它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。双缓冲：交换(Swap)前缓冲和后缓冲
        glfwSwapBuffers(window);
        // glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，
        // 并调用对应的回调函数（可以通过回调方法手动设置）。
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
    // glfwGetKey函数，它需要一个窗口以及一个按键作为输入。这个函数将会返回这个按键是否正在被按下。是否按下了返回键(Esc)
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // glfwSetwindowShouldClose使用把WindowShouldClose属性设置为 true的方法关闭GLFW。
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    // viewport(视口): 渲染窗口的尺寸大小
    // glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
    glViewport(0, 0, width, height);
}

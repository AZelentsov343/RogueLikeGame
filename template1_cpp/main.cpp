#include "outer_includes/common.h"
#include "Image.h"
#include "Player.h"
#include "Sprite.h"
#include "SpriteController.h"
#include "Door.h"
#include "Enemy.h"

#define GLFW_DLL

#include <fstream>
#include <string>
#include <GLFW/glfw3.h>
#include "shared.h"

struct InputState {
    bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
    GLfloat lastX = 400, lastY = 300; //исходное положение мыши
    bool firstMouse = true;
    bool captureMouse = true;  // Мышка захвачена нашим приложением или нет?
    bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


void OnKeyboardPressed(GLFWwindow *window, int key, int scancode, int action, int mode) {
    switch (key) {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_1:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case GLFW_KEY_2:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        default:
            if (action == GLFW_PRESS)
                Input.keys[key] = true;
            else if (action == GLFW_RELEASE)
                Input.keys[key] = false;
    }
}

void processPlayerMovement(Player *player) {
    if (Input.keys[GLFW_KEY_W])
        player->move(MovementDir::UP);
    else if (Input.keys[GLFW_KEY_S])
        player->move(MovementDir::DOWN);
    else
        player->stopY();
    if (Input.keys[GLFW_KEY_A])
        player->move(MovementDir::LEFT);
    else if (Input.keys[GLFW_KEY_D])
        player->move(MovementDir::RIGHT);
    else
        player->stopX();

    if (Input.keys[GLFW_KEY_SPACE]) {
        Input.keys[GLFW_KEY_SPACE] = false;
        player->Interact();
    }

    if (Input.keys[GLFW_KEY_Q]) {
        Input.keys[GLFW_KEY_Q] = false;
        player->ThrowFireball();
    }
}

void OnMouseButtonClicked(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        Input.captureMouse = !Input.captureMouse;

    if (Input.captureMouse) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Input.capturedMouseJustNow = true;
    } else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow *window, double xpos, double ypos) {
    if (Input.firstMouse) {
        Input.lastX = float(xpos);
        Input.lastY = float(ypos);
        Input.firstMouse = false;
    }

    GLfloat xoffset = float(xpos) - Input.lastX;
    GLfloat yoffset = Input.lastY - float(ypos);

    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow *window, double xoffset, double yoffset) {
    // ...
}


int initGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    std::cout << "Controls: " << std::endl;
    std::cout << "press right mouse button to capture/release mouse cursor  " << std::endl;
    std::cout << "W, A, S, D - movement  " << std::endl;
    std::cout << "press SPACE to open doors" << std::endl;
    std::cout << "press Q to throw fireball" << std::endl;
    std::cout << "press ESC to exit" << std::endl;

    return 0;
}

std::string read_level(const std::string &filename) {
    std::ifstream infile(filename);
    std::string s;
    std::string res;

    while (std::getline(infile, s)) {
        res += s;
    }
    return res;
}

int main(int argc, char **argv) {
    if (!glfwInit())
        return -1;


//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Game", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, OnKeyboardPressed);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
    glfwSetScrollCallback(window, OnMouseScroll);

    if (initGL() != 0)
        return -1;

    //Reset any OpenGL errors which could be present for some reason
    GLenum gl_error = glGetError();
    while (gl_error != GL_NO_ERROR)
        gl_error = glGetError();

    std::vector<std::string> levels = {"../level_tunnel.txt", "../level_drunkards.txt"}; // "../level_tunnel.txt",

    bool next_level = true;

    for (auto& levelFile : levels) {
        if (!next_level) {
            break;
        }
        std::string level = read_level(levelFile);
        SpriteController sc;

        for (int j = 0; j < WINDOW_HEIGHT; j += tileSize) {
            for (int i = 0; i < WINDOW_WIDTH; i += tileSize) {
                int index = (j / tileSize) * (WINDOW_HEIGHT / tileSize) + (i / tileSize);
                if (level[index] == '.') {
                    auto sp = new Sprite("floor", "../resources/floor32x32.png", {i, WINDOW_HEIGHT - tileSize - j});
                    sc.addSprite(sp);
                } else if (level[index] == ' ') {
                    auto sp = new Sprite("hole", "../resources/pit32x32.png", {i, WINDOW_HEIGHT - tileSize - j},
                                         RenderPriority::BACKGROUND, true);
                    sc.addSprite(sp);
                } else if (level[index] == '#') {
                    auto sp = new Sprite("wall", "../resources/wall.png", {i, WINDOW_HEIGHT - tileSize - j},
                                         RenderPriority::BACKGROUND, true);
                    sp->cutSprite({0, 0}, {32, 32});
                    sc.addSprite(sp);
                } else if (level[index] == '@') {
                    auto sp = new Sprite("floor", "../resources/floor32x32.png", {i, WINDOW_HEIGHT - tileSize - j});
                    sc.addSprite(sp);
                    auto player = new Player("../resources/player.png", {i, WINDOW_HEIGHT - tileSize - j}, 2);
                    sc.addPlayer(player);
                    player->setController(&sc);
                } else if (level[index] == 'X') {
                    auto sp = new Sprite("exit", "../resources/exit32x32.png", {i, WINDOW_HEIGHT - tileSize - j},
                                         RenderPriority::BACKGROUND, true);
                    sc.addSprite(sp);
                } else if (level[index] == 'D') {
                    auto door = new Door("../resources/door.png", {i, WINDOW_HEIGHT - tileSize - j});
                    sc.addSprite(door);
                } else if (level[index] == 'E') {
                    auto sp = new Sprite("floor", "../resources/floor32x32.png", {i, WINDOW_HEIGHT - tileSize - j});
                    sc.addSprite(sp);
                    auto enemy = new Enemy("../resources/enemy.png", {i, WINDOW_HEIGHT - tileSize - j}, 2);

                    enemy->setController(&sc);

                    enemy->followPlayer(sc.getPlayer());

                    sc.addSprite(enemy);
                }
            }
        }

        //Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);

        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        GL_CHECK_ERRORS;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        GL_CHECK_ERRORS;

        //game loop
        while (!glfwWindowShouldClose(window) && !sc.died()) {
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            glfwPollEvents();

            processPlayerMovement(dynamic_cast<Player *>(sc.getPlayer()));
            sc.update();


            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            GL_CHECK_ERRORS;
            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, sc.Data());
            GL_CHECK_ERRORS;

            glfwSwapBuffers(window);
        }

        if (!sc.didPass()) {
            next_level = false;
        }

        sc.curScreen().Save("screen.png");
    }
    system("rm screen.png");
    glfwTerminate();
    return 0;
}

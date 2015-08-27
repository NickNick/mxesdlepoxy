#define SDL_MAIN_HANDLED
#ifdef _WIN32
#define EPOXY_IMPORTEXPORT
#endif
#include <epoxy/gl.h>
#ifdef _WIN32
#include <epoxy/wgl.h>
#endif


#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>

#define ASTRANT_STREAM_CURRENT_PLACE_INFORMATION std::string(__FILE__) + ":" << std::setw(4) << std::to_string(__LINE__) << "(" <<  std::setw(15) << __FUNCTION__ << ")"

#define ACOUT  std::cout << ASTRANT_STREAM_CURRENT_PLACE_INFORMATION  << "\n"
#define ASDOUT std::cout << ASTRANT_STREAM_CURRENT_PLACE_INFORMATION  << ": "
#define ACERR  std::cerr << ASTRANT_STREAM_CURRENT_PLACE_INFORMATION  << "\n"
#define ASDERR std::cerr << ASTRANT_STREAM_CURRENT_PLACE_INFORMATION  << ": "

int main(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error("Unable to initialize SDL: " + std::string(SDL_GetError()));
    }

    auto const double_buffer_result = SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
    if (double_buffer_result) {
        ASDERR << "Failed to enable double_buffering" << std::endl;
    }

    // As of writing, we use glsl version 330, so the minimum opengl version is 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    auto const core_activated = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    auto const wanted_resolution_width = 200;
    auto const wanted_resolution_height = 200;

    ASDOUT << "Creating window sized " << wanted_resolution_width << " x " << wanted_resolution_height << std::endl;
    auto window = SDL_CreateWindow("SDL <3 Epoxy",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              wanted_resolution_width,
                              wanted_resolution_height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::string const sdl_error{SDL_GetError()};
        throw std::runtime_error("Failed to create SDL_Window: " + sdl_error);
    } else {
        ASDOUT << "Succesfully created window" << std::endl;
    }

    auto context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    if (!context) {
        throw std::runtime_error("Failed to create OpenGL Context: " + std::string(SDL_GetError()));
    }

    if (SDL_GL_SetSwapInterval(1) != 0) { // Vsync
        ASDERR << "Failed to set swap interval" << std::endl;
    }

    ASDOUT << epoxy_gl_version() << std::endl;
    ASDOUT << epoxy_is_desktop_gl() << std::endl;

    bool done = false;
    while(!done){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) done = true;
        }
        auto r = std::sin(float(SDL_GetTicks()) * 0.010);
        auto g = std::sin(float(SDL_GetTicks()) * 0.015);
        auto b = std::sin(float(SDL_GetTicks()) * 0.020);
        glClearColor(r, g, b, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        GLuint texture = 0;
        glGenTextures(1, &texture);
        glDeleteTextures(1, &texture);
        SDL_GL_SwapWindow(window);
    }
}


#include <Yeno/Window.hpp>
#include <Yeno/Log.hpp>
#include <Yeno/Shader.hpp>
#include <Yeno/Config.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace Yeno
{
	Window::Window(const char *title, int width, int height)
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

		SDL_ClearError();
		window = SDL_CreateWindow(title,
		                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		                          width, height,
		                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (window == nullptr) {
			Log::Fatal("Fatal Error: Failed to create window: %s\n", SDL_GetError());
			return;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_ClearError();
		context = SDL_GL_CreateContext(window);
		if (context == nullptr) {
			Log::Fatal("Fatal Error: Failed to create OpenGL context: %s\n", SDL_GetError());
			return;
		}

		if (!gladLoadGL()) {
			Log::Fatal("Fatal Error: Failed to initialize OpenGL\n");
			return;
		}
		Log::Info("Info: Using OpenGL %s\n", glGetString(GL_VERSION));

		GLint gl_major, gl_minor;
		glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
		glGetIntegerv(GL_MAJOR_VERSION, &gl_minor);

		GLint extension_count;
		glGetIntegerv(GL_NUM_EXTENSIONS, &extension_count);
		Config::use_persistent_mapping = false;
		for (GLint i = 0; i < extension_count; i++) {
			const char *extension_name = (const char *)glGetStringi(GL_EXTENSIONS, i);
			if (strcmp(extension_name, "GL_ARB_buffer_storage") == 0) {
				Config::use_persistent_mapping = true;
			}
		}
		if (!Config::use_persistent_mapping) {
			Log::Warn("Warning: Driver doesn't support persistent buffer mapping\n");
		}
		/*if (gl_major >= 4 && gl_minor >= 4) {
			Config::use_persistent_mapping = true;
		}
		else {
			Config::use_persistent_mapping = false;
			Log::Warn("Warning: Driver doesn't support persistent buffer mapping\n");
		}*/

		SDL_GL_SetSwapInterval(Config::vsync * -1);

		//Initialize imgui
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = nullptr;
		ImGui_ImplSDL2_InitForOpenGL(window, context);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}
	Window::~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		if (context != nullptr) SDL_GL_DeleteContext(context);
		if (window != nullptr) SDL_DestroyWindow(window);
		window = nullptr;
	}

	void Window::ProcessEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					open = false;
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						const int width  = event.window.data1;
						const int height = event.window.data2;
						glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
						glm::mat4 view(1.0f);
						glViewport(0, 0, width, height);
						glBindBuffer(GL_UNIFORM_BUFFER, Shader::uniform_buffer);
						glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projection[0][0]);
						glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &view[0][0]);
					}
					break;
			}
		}
		if (SDL_GL_GetSwapInterval() != (Config::vsync * -1)) {
			SDL_GL_SetSwapInterval(Config::vsync * -1);
		}
		if (glIsEnabled(GL_MULTISAMPLE) != Config::antialiasing) {
			if (Config::antialiasing) {
				glEnable(GL_MULTISAMPLE);
			}
			else {
				glDisable(GL_MULTISAMPLE);
			}
		}
	}

	bool Window::IsOpen()
	{
		return open;
	}

	void Window::Clear()
	{
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffer()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}
}
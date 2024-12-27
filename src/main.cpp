#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include <glad/glad.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>

#include <fmt/core.h>

#include <glm/glm.hpp>

#include "SystemSimulation.h"

constexpr uint32_t WIDTH{ 1920 };
constexpr uint32_t HEIGHT{ 1080 };

Simulation simulation{ WIDTH, HEIGHT };

int main(int, char**) {
	// setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD) != 0) {
		fmt::println("Error: SDL_Init(): {}", SDL_GetError());
		return -1;
	}

	const char* glslVersion{ "#version 460" };
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	// create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	uint32_t windowFlags{ SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN };
	SDL_Window* window{ SDL_CreateWindow("glSolarSystem", WIDTH, HEIGHT, windowFlags) };
	if (window == nullptr) {
		fmt::println("Error: SDL_CreateWindow(): {}", SDL_GetError());
		return -1;
	}
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_GLContext glContext{ SDL_GL_CreateContext(window) };
	SDL_GL_MakeCurrent(window, glContext);
	SDL_GL_SetSwapInterval(1);	// enable vsync
	SDL_ShowWindow(window);
	SDL_SetWindowRelativeMouseMode(window, true);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		fmt::println("Failed to initialise GLAD");
		return -1;
	}

	// setup dear imgui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// enable keyboard controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	// enable gamepad controls

	// setup dear imgui style
	ImGui::StyleColorsDark();

	// setup platform/renderer backends
	ImGui_ImplSDL3_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init(glslVersion);

	// imgui state
	glm::vec4 clearColour{ 0.0f, 0.0f, 0.0f, 1.0f };

	// main loop
	simulation.init();
	bool done{ false };

	float deltaTime{};
	float lastFrame{};

	while (!done) {
		glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));

		float currentFrame{ static_cast<float>(SDL_GetTicks()) };
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		SDL_Event event{};
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_EVENT_MOUSE_MOTION) {
				float xOffset{ event.motion.xrel };
				float yOffset{ -event.motion.yrel };

				simulation.processMouse(xOffset, yOffset);
			}

			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
				done = true;
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		simulation.processKey(deltaTime);
		simulation.update(deltaTime);

		// start the dear imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		{
			static float f{ 0.0f };
			static int counter{ 0 };

			ImGui::Begin("Debug Window");

			ImGui::ColorEdit3("clear colour", reinterpret_cast<float*>(&clearColour));

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// rendering
		ImGui::Render();

		glClearColor(clearColour.x * clearColour.w, clearColour.y * clearColour.w, clearColour.z * clearColour.w, clearColour.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		simulation.render();


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	// cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
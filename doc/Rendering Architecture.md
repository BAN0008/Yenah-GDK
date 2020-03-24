# Rendering Architecture

## Potential batch splitters
- Too many textures
- Different shaders
- Layers / Depth
- Different vertex data (for example a particle system)
- Uniforms
- Too many vertices

## Ideas
- Custom allocator to improve allocation performance for dynamic batch creation

## Texture sampling
- Sample all texture units into a colour array and then chose which colour to use
- Use a switch statement to choose sampler

## Quad drawing process
### Method 1
```c++
class Drawable {
public:
	GetVertices();
	GetLayer();
};
class Quad : public Drawable;

std::vector<Drawable *> draw_list;

int main() {
	draw_list.push_back(new Quad(position, size, rotation, texture, colour, Layer));

	// Sort draw_list by layer
	// Sort draw_list by shader respecting layer
	// Sort draw_list by texture unit respecting shader and layer

	for (int i = 0; i < draw_list.size(); i++) {
		// Add draw_list item vertex data to render batch
		// Flush batch when required (See Potential batch splitters)
	}
	// Flush batch if not empty
}
```

# Profiler Features
- FPS
- FPS Limit
- VSYNC
- Frame time
- Lowest frame time
- Highest frame time
- Breakdown of frame time (In a timeline)
	- Event processing time
	- Object update time
	- CPU graphics time
		- Draw list sorting
		- Draw list submission time
	- GPU time
- Single frame advance (Doesn't mess up the delta time)
- Custom delta time multiplier
- Display of OpenGL extensions used
- Number of draw calls
- Number of vertices
- Number of textures used
- Pause game / profiling (For viewing the data)
- Number of game objects
- Record all of this information for the last x frames and view data for any frame

# Rendering Architecture Restructure
```lua
-- Main.lua
while running do
	Profiler.BeginFrame()
	running = ProcessEvents()
	Profiler.Time("Event Processing")

	-- Calculate delta time
	delta_time = ...

	for object in objects do
		object.update(delta_time)
	end
	Profiler.object_count = objects.count() 

	Renderer.RenderFrame()
	Profiler.EndFrame()
end
```

```c++
// Renderer.cpp
namespace Renderer
{
	void RenderFrame()
	{
		// Sort draw list
		...

		Profiler.Time("Draw list sorting")

		// Submit draw list
		...
		Profiler.Time("Draw list rendering")
		Profiler.SetDrawCalls(...);
		Profiler.SetVertices(...);
		Profiler.SetTextures(...);
		Profiler.SetGameObjects(...);

		// Draw imgui
		...
		Profiler.Time("Imgui rendering");
	}
}
```

```c++
// Profiler.cpp
namespace Profiler
{
	struct FrameInfo
	{
		float time; // Frame time

		// Breakdown of frame time
		float time_breakdown[6];
		const char * breakdown_descriptions[6];
		unsigned int breakdown_count;

		unsigned int draw_calls;   // Number of draw calls
		unsigned int vertices;     // Number of vertices
		unsigned int textures;     // Number of texture units
		unsigned int game_objects; // Number of game objects updated
	};

	FrameInfo *frames = nullptr;
	unsigned int frame_count = 0;

	unsigned long start_time = 0;
	unsigned long previous_time = 0;

	float highest_time = -1.0f, lowest_time = -1.0f

	Frame frame;

	void BeginFrame()
	{
		start_time = SDL_GetPerformanceCounter();
		previous_time = start_time;
		frame.breakdown_count = 0;
		frame.draw_calls   = 0;
		frame.vertices     = 0;
		frame.textures     = 0;
		frame.game_objects = 0;
	}

	void Time(const char *description)
	{
		frame.breakdown_descriptions[frame.breakdown_count] = description;
		const current_time = SDL_GetPerformanceCounter();
		frame.time_breakdown[frame.breakdown_count] = ((float)(current_time - previous_time) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
		previous_time = current_time;
		frame.breakdown_count++;
	}

	void SetDrawCalls(unsigned int number) {
		frame.draw_calls = number;
	}

	void SetVertices(unsigned int number) {
		frame.vertices = number;
	}

	void SetTextures(unsigned int number) {
		frame.textures = number;
	}

	void SetGameObjects(unsigned int number) {
		frame.game_objects = number;
	}

	void EndFrame()
	{
		float time = ((float)(SDL_GetPerformanceCounter() - start_time) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
		frame.time = time;

		if (!profile) {
			if (time > highest_time || highest_time < 0.0f) highest_time = time;
			if (lowest_time > time  || lowest_time < 0.0f)  lowest_time = time;

			(*frames[frame_count++]) = frame;
		}
	}

	void Show()
	{
		/*
		Q: What does pause do?
		A: Stop calls to:
			- <object>.update()
			- game.pre_update()
			- game.post_update()
			- Disables furthur profiling
				Q: How?
				A: Store frame info in a buffer that is pushed to `frames` on EndFrame() if profiling is enabled

		*/
		if (ImGui::Button("Pause")) {

		}
		if (ImGui::Button("Advance Frame")) {

		}

		FrameInfo &frame = frames[frame_count];
		ImGui::Begin("Profiler");
		ImGui::Text("Frame Time / FPS: %f / %f", frame.time, 1000.0f / frame.time);
		ImGui::Text("Highest Frame Time / Lowest FPS: %f / %f", highest_time, 1000.0f / highest_time);
		ImGui::Text("Lowest Frame Time / Highest FPS: %f / %f", lowest_time,  1000.0f / lowest_time);

		bool vsync = Renderer::GetVSync();
		ImGui::Checkbox("VSYNC", &vsync);
		Renderer::SetVSync(vsync);

		// Draw time breakdown
		...

		ImGui::Text("Draw Calls: %u", frame.draw_calls);
		ImGui::Text("Vertices: %u", frame.vertices);
		ImGui::Text("Textures: %u", frame.textures);
		ImGui::Text("Game Objects: %u", frame.game_objects);
		ImGui::End();
	}
}
```
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
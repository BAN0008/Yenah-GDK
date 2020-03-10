# Features
- Shaders
- Camera
- Primitive drawing
- Textures
- Render targets
- Physics
- Audio

# Lua API
```
yeno.shader.create_from_file(shader_name, vertex_fname, fragment_fname)
yeno.shader.create_from_strings(shader_name, vertex_code, fragment_code)
yeno.shader.bind(shader_name)
yeno.shader.set_float(shader_name, value)
yeno.shader.set_int(shader_name, value)
yeno.shader.set_vec2(shader_name, value)
yeno.shader.set_vec3(shader_name, value)
yeno.shader.set_vec4(shader_name, value)
yeno.shader.set_mat3(shader_name, value)
yeno.shader.set_mat4(shader_name, value)

yeno.camera.setPosition(position)
yeno.camera.setRotation(radians)
yeno.camera.setSize(size)
yeno.camera.setScale(scale)

yeno.drawing.set_colour(colour)
yeno.drawing.draw_circle(position, radius)
yeno.drawing.draw_rectangle(position, rotation, size)
yeno.drawing.draw_line(position1, position2, thickness)
yeno.drawing.draw_poly(positions)

yeno.texture.create_from_file(fname)
yeno.texture.create_from_render_target(render_target, offset, size)
yeno.texture.create_from_atlas(name)
yeno.texture.draw(position, rotation, scale)

yeno.render_target.create(colour)
yeno.render_target.clear(colour)
yeno.render_target.bind()
yeno.render_target.bind_default()

yeno.audio.play(sound_name)
```
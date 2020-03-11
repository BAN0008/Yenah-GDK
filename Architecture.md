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
yenah.shader.create_from_file(shader_name, vertex_fname, fragment_fname)
yenah.shader.create_from_strings(shader_name, vertex_code, fragment_code)
yenah.shader.bind(shader_name)
yenah.shader.set_float(shader_name, value)
yenah.shader.set_int(shader_name, value)
yenah.shader.set_vec2(shader_name, value)
yenah.shader.set_vec3(shader_name, value)
yenah.shader.set_vec4(shader_name, value)
yenah.shader.set_mat3(shader_name, value)
yenah.shader.set_mat4(shader_name, value)

yenah.camera.setPosition(position)
yenah.camera.setRotation(radians)
yenah.camera.setScale(scale)

yenah.drawing.set_colour(colour)
yenah.drawing.draw_circle(position, radius)
yenah.drawing.draw_rectangle(position, rotation, size)
yenah.drawing.draw_line(position1, position2, thickness)
yenah.drawing.draw_poly(positions)

yenah.texture.create_from_file(fname)
yenah.texture.create_from_render_target(render_target, offset, size)
yenah.texture.create_from_atlas(name)
yenah.texture.draw(position, rotation, scale)

yenah.render_target.create(colour)
yenah.render_target.clear(colour)
yenah.render_target.bind()
yenah.render_target.bind_default()

yenah.audio.play(sound_name)
```
# Lua API

## Important Features
### Textures
**Functions**
### Shaders
**Functions**
```
Yenah.Shader.Create() -- Returns shader_id
Yenah.Shader.Bind(shader_id) -- All rendering uses the currently bound shader
Yenah.Shader.SetUniform(shader_id, name, value)
Yenah.Shader.Delete(shader_id)
```

### Renderer
**Functions**

### Camera
**Functions**
```
Yenah.Camera.SetPosition(x, y)
Yenah.Camera.GetPosition() -- Returns x and y
Yenah.Camera.SetZoom(x_scale, y_scale)
Yenah.Camera.GetZoom() -- Returns x_scale and y_scale
Yenah.Camera.SetRotation(radians)
Yenah.Camera.GetRotation() -- Returns radians
```

### Objects
**Requirements**
- Every object should have a unique id which can be used to:
	- access the object with constant time complexity
	- safely check if the object still exists

- Every object should be stored in a data structure that can:
	- be iterated over efficiently by the game engine
	- allow insertion without moving other objects
	- maintain the order of objects within the list

- Every object should have an update and draw method as well as a constructor / destructor

**Functions**
```
Yenah.Object.Create()
Yenah.Object.Get(id)
Yenah.Object.Destroy()
```
### Keyboard / Mouse input
**Functions**
```
Yenah.Keyboard.GetKeyState(key) -- Returns either Pressed, Released, Down, Up or Repeat
Yenah.Mouse.GetButtonState(button) -- Returns either Pressed, Released, Down or Up
Yenah.Mouse.GetPosition() -- Returns x and y
Yenah.Mouse.SetPosition(x, y)
Yenah.Mouse.ShowCursor(show_cursor);
```

## Less Important Features
### Render targets
### Text rendering
### Audio
### Physics

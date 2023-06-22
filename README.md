![image](https://github.com/MaxineCodes/BubblesRT/blob/main/img/Banner@2x.png)

# Bubbles Raytracing Renderer
 
### The Bubbles raytracing rendering engine is a offline/CPU raytracing engine project.
The goal of this project is to stay away from external libraries, and really understand how raytracing works under the hood.  
This ray-tracer is not particularly efficient or feature-rich. It is a learning exercise after all. :)

[BubblesRT trello page.](https://trello.com/b/EzgDRD4m/bubblesrt)

---

## Rendering results:

Render output at 22-06-2023 using only spheres and lambert materials:

![image](https://github.com/MaxineCodes/BubblesRT/blob/main/RenderOutputs/renderOutput_22-06-2023.png)

---

## Feature overview:

### Basics
- [x] Basic raytracing algorithm
- [x] OpenGL viewport to display the rendered image
- [ ] Binary space partitioning
- [ ] HDR environment maps
- [ ] Texture mapping
- [ ] Using .USD ASCII files as input
- [ ] Multithreading
- [ ] Command line interface

### Outputs
- [x] Exporting rendered image as .ppm file
- [ ] Exporting rendered image as .png file

### Supported Lights
- [x] Environment lights
- [ ] Point lights
- [ ] Directional lights
- [ ] Area lights
- [ ] Emissive materials

### Supported Geometry
- [x] Spheres
- [ ] Meshes
- [ ] Vertex normals
- [ ] Normal smoothing

### Supported Materials
- [x] Lambert materials
- [ ] Phong materials
- [ ] Glass materials
- [ ] Metallic materials
- [ ] PBR materials

---

### Dependencies:
- OpenGL
- GLEW
- GLFW

---

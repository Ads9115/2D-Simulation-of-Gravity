# OpenGL 2D Gravity Simulation 🌍🚀

This project is a real-time 2D gravity and orbit simulation built using **C++** and **OpenGL**. Two circular bodies interact through Newtonian gravity, orbit each other, and collide naturally all in a custom shader-based render loop.

---

## 🔧 Features

- Two-body gravitational interaction
- Circular orbit approximation
- Real-time OpenGL rendering (GLSL shaders)
- Scalable rendering via uniforms (`u_position`, `u_scale`)
- Soft boundaries to keep objects in frame

---

## 🧠 What I Learned

- Manual 2D vertex construction (circle using triangle fan)
- OpenGL buffer/VAO/VBO setup
- GLSL uniform handling
- Newton's Law of Gravitation
- Orbital mechanics (velocity balancing for stable center-of-mass)
- Practical use of `glm` for physics simulation

---

## 🛠 Tech Stack

- C++
- OpenGL (Core Profile 3.3)
- GLFW
- GLAD
- GLSL shaders
- GLM (for vectors and math)

---

## 📦 Build Instructions

Make sure you have:
- GLFW
- GLAD
- GLM
- A C++17-compatible compiler

### CMake (optional)
```bash
mkdir build
cd build
cmake ..
make

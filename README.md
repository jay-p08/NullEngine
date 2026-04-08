# NullEngine 🚀
**A High-Performance C++ Game Engine Study Project**

NullEngine은 게임 엔진의 핵심 아키텍처와 로우레벨 그래픽스 API를 학습하기 위해 밑바닥부터 빌드하는 C++ 게임 엔진입니다.

## 🛠 Tech Stack
* **Language:** C++ 17
* **Build System:** CMake
* **Package Manager:** vcpkg
* **Graphics API:** OpenGL 4.5
* **Libraries:** GLFW, GLAD, GLM, spdlog

## 🏗 Architecture
* **Core:** Window management, Application lifecycle, Event system.
* **Graphics:** Shader abstraction, Vertex/Index Buffer management.
* **Math:** Custom wrappers for linear algebra using GLM.

## 🚀 How to Build
1. **Clone the repo:** `git clone https://github.com/YourID/NullEngine.git`
2. **Install dependencies:** `vcpkg install`
3. **Configure & Build:** - Use VS Code CMake Tools 
   - Select Kit (MSVC 2022)
   - Press `F7` to Build

## 📅 Roadmap
- [x] Engine Heart (Application & Window)
- [ ] Shader & Buffer Abstraction (In Progress)
- [ ] 2D Batch Renderer
- [ ] Entity Component System (ECS)
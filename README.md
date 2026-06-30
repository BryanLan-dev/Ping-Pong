# 🏓 Ping Pong Game

https://github.com/user-attachments/assets/beb32f70-3629-4e66-9b97-8b2aefe11b6a

A classic Pong game built in **C++** using the **Raylib** library. Play against a CPU opponent — first to 7 points wins!

---

## 🎮 Gameplay

- **Player paddle** — right side, controlled with ↑ / ↓ arrow keys  
- **CPU paddle** — left side, automatically tracks the ball  
- **First to 7 points wins**  
- Ball speeds up with each paddle hit (up to a max speed)  
- Hit effects flash on paddle contact for visual feedback

---

## 🛠️ Built With

- **C++17**
- **[Raylib](https://www.raylib.com/)** — simple and easy-to-use game development library
- **MSYS2 / UCRT64** toolchain on Windows
- **VS Code**

---

## 📦 Prerequisites

Install Raylib via MSYS2:

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```

---

## 🔧 Building & Running

This project is based on the [Raylib C++ Starter Template](https://github.com/educ8s/Raylib-CPP-Starter-Template-for-VSCode-V2). The included `.vscode/tasks.json` and `c_cpp_properties.json` are configured for the template's **w64devkit** toolchain. If you're using **MSYS2/UCRT64** (recommended), compile manually with:

```bash
g++ main.cpp -o ping_pong \
  -I"C:/msys64/ucrt64/include" \
  -L"C:/msys64/ucrt64/lib" \
  -lraylib -lopengl32 -lgdi32 -lwinmm
```

Then run:

```bash
./ping_pong.exe
```

---

## 🗂️ Project Structure

```
ping_pong/
├── main.cpp          # All game logic
├── .vscode/
│   ├── tasks.json              # Build tasks (configured for w64devkit starter template)
│   ├── launch.json             # Debug/run configurations
│   ├── c_cpp_properties.json   # IntelliSense paths (configured for w64devkit starter template)
│   └── settings.json           # Editor settings
└── README.md
```

---

## ✨ Features

- Smooth paddle and ball physics
- CPU AI that tracks the ball in real time
- Score display for both player and CPU
- Animated hit effects on paddle collisions
- Win screen overlay when a player reaches 7 points
- Ball speed escalation for increasing difficulty

---

## 🚀 Future Ideas

- [ ] Add sound effects
- [ ] Main menu screen
- [ ] Difficulty settings for CPU speed
- [ ] Two-player local multiplayer

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE.txt).



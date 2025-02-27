 # CMakeList.txt : CMake project for Nebula, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
 set(CMAKE_TOOLCHAIN_FILE "C:Dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
         CACHE STRING "")
endif()

# Set the project name
project ("NebulaEngine")

# Packages
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

include_directories(${GLM_INCLUDE_DIRS})

# Add Shared Library
add_library(Nebula 
    SHARED

    # Core
    NebulaEngine/src/Core/Application.cpp

    # Logger
    NebulaEngine/src/Logger/Log.cpp 

    # Platform - Windows
    NebulaEngine/src/Platforms/Windows/WindowsWindow.cpp NebulaEngine/src/Platforms/Windows/WindowsInput.cpp
    
    # Platform - OpenGL - Context
    NebulaEngine/src/Platforms/OpenGL/Context/OpenGLContext.cpp 
    
    # Platform - OpenGL - Buffer
    NebulaEngine/src/Platforms/OpenGL/Buffer/IndexBuffer/OpenGLIndexBuffer.cpp NebulaEngine/src/Platforms/OpenGL/Buffer/VertexBuffer/OpenGLVertexBuffer.cpp
    
    # Platform - OpenGL - Renderer
    NebulaEngine/src/Platforms/OpenGL/RendererApi/OpenGLRendererApi.cpp

    # Platform - OpenGL - VertexArray
    NebulaEngine/src/Platforms/OpenGL/VertexArray/OpenGLVertexArray.cpp
    
    # Renderer - Graphics
    NebulaEngine/src/Renderer/Graphics/GraphicsContext.cpp

    # Renderer - Manager
    NebulaEngine/src/Renderer/Manager/RendererManager.cpp

    # Renderer - Command
    NebulaEngine/src/Renderer/Command/RendererCommand.cpp

    # Renderer - Render - Shader
    NebulaEngine/src/Renderer/Render/Shader/Shader.cpp

    # Renderer - Buffer - VertexBuffer
    NebulaEngine/src/Renderer/Buffer/VertexBuffer/VertexBuffer.cpp

    # Renderer - Buffer - InderBuffer
    NebulaEngine/src/Renderer/Buffer/IndexBuffer/IndexBuffer.cpp

    # Renderer - Shape - Rectangle
    NebulaEngine/src/Renderer/Shape/Rectangle/RectangleShape.cpp

    # Renderer - Shape - Triangle
    NebulaEngine/src/Renderer/Shape/Triangle/TriangleShape.cpp

    # Renderer - VertexArray
    NebulaEngine/src/Renderer/VertexArray/VertexArray.cpp

    # Renderer - Manager
    NebulaEngine/src/Renderer/Manager/RendererManager.cpp

    # Renderer - Api
    NebulaEngine/src/Renderer/Api/RendererApi.cpp

    # Renderer - Camera
    NebulaEngine/src/Renderer/Camera/OrthographicCamera.cpp

    # Renderer - Render - Texture
    NebulaEngine/src/Renderer/Render/Texture/Texture.cpp

    # Inputs
    NebulaEngine/src/Inputs/InputManager.cpp

    # Layer 
    NebulaEngine/src/Layer/Layer.cpp NebulaEngine/src/Layer/LayerStack.cpp

    # ImGui
    NebulaEngine/src/ImGui/ImGuiLayer.cpp
    )
target_compile_definitions(Nebula PRIVATE NEBULA_EXPORTS)

target_sources(Nebula
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS
  NebulaEngine/include
  FILES
  # Nebula
  NebulaEngine/include/Nebula.h

  # Logger
  NebulaEngine/include/logger/log.h 

  # Window
  NebulaEngine/include/Window/Window.h

  # Core
  NebulaEngine/include/Core/Core.h NebulaEngine/include/Core/Application.h NebulaEngine/include/Core/EntryPoint.h
  
  # Events
  NebulaEngine/include/Events/Event.h NebulaEngine/include/Events/KeyEvent.h NebulaEngine/include/Events/MouseEvent.h NebulaEngine/include/Events/ApplicationEvent.h
  
  # Platforms - Linux
  NebulaEngine/include/Platforms/Linux/Linux.h
  
  # Platforms - Windows
  NebulaEngine/include/Platforms/Windows/WindowsWindow.h NebulaEngine/include/Platforms/Windows/WindowsInput.h
  
  # Platforms - OpenGL
  NebulaEngine/include/Platforms/OpenGL/Buffer/IndexBuffer/OpenGLIndexBuffer.h NebulaEngine/include/Platforms/OpenGL/Buffer/VertexBuffer/OpenGLVertexBuffer.h NebulaEngine/include/Platforms/OpenGL/Context/OpenGLContext.h NebulaEngine/include/Platforms/OpenGL/VertexArray/OpenGLVertexArray.h NebulaEngine/include/Platforms/OpenGL/Renderer/OpenGLRendererAPI.h
  
  # Renderer - Graphics
  NebulaEngine/include/Renderer/Graphics/GraphicsContext.h 
  
  # Renderer - Api
  NebulaEngine/include/Renderer/Api/RendererApi.h

  # Renderer - Command
  NebulaEngine/include/Renderer/Command/RendererCommand.h

  # Renderer - Render - Shader
  NebulaEngine/include/Renderer/Render/Shader/Shader.h

  # Renderer - Render - Texture
  NebulaEngine/include/Renderer/Render/Texture/Texture.h

  # Renderer - Render
  NebulaEngine/include/Renderer/Render/Render.h 

  # Renderer - Buffer - VertexBuffer
  NebulaEngine/include/Renderer/Buffer/VertexBuffer/VertexBuffer.h

  # Renderer - Buffer - InderBuffer
  NebulaEngine/include/Renderer/Buffer/IndexBuffer/IndexBuffer.h

  # Renderer - Buffer - Layout
  NebulaEngine/include/Renderer/Buffer/Layout/BufferLayout.h

  # Renderer - Buffer
  NebulaEngine/include/Renderer/Buffer/Buffer.h

  # Renderer - Shape - Rectangle
  NebulaEngine/include/Renderer/Shape/Rectangle/RectangleShape.h

  # Renderer - Shape - Triangle
  NebulaEngine/include/Renderer/Shape/Triangle/TriangleShape.h

  # Renderer - VertexArray
  NebulaEngine/include/Renderer/VertexArray/VertexArray.h

  # Renderer - Manager
  NebulaEngine/include/Renderer/Manager/RendererManager.h

  # Renderer - Camera
  NebulaEngine/Include/Renderer/Camera/OrthographicCamera.h

  # Inputs
  NebulaEngine/include/Inputs/InputManager.h

  # Layer
  NebulaEngine/include/Layer/Layer.h NebulaEngine/include/Layer/LayerStack.h

  # TimeStep
  NebulaEngine/include/TimeStep/TimeStep.h

  # ImGui
  NebulaEngine/include/ImGui/ImGuiLayer.h
)

# Add the Game executable
add_executable (Game "Game/Game.cpp") 

# Add the Tests executable
add_executable (NebulaTests "Tests/Units/RunTests.cpp")

# Add the source files
target_sources(Nebula
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS
  spdlog/include
)

# Link libraries
 target_link_libraries(Nebula
         PUBLIC
         glm::glm
         spdlog::spdlog
         glad::glad
         glfw
         GLEW::glew
         imgui::imgui
         fmt::fmt
         opengl32
         glu32
 )
target_link_libraries(Game PRIVATE Nebula)
target_link_libraries(NebulaTests PRIVATE Nebula fmt::fmt GTest::gtest_main)

# Add tests to CTest
 add_subdirectory(Tests)

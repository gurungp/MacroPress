cmake_minimum_required(VERSION 3.23)

project(keyboardSim)

# Specify the C++ standard (C++17 or C++20 for example)
set(CMAKE_CXX_STANDARD 20)  # You can set 20 for C++20 if needed
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)  # Optional: Ensures no compiler-specific extensions are used
set(CMAKE_BUILD_TYPE Release)

# Find and link the required Frameworks
find_library(SDL2_LIBRARY NAME SDL2)
find_library(COREFOUNDATION_LIBRARY CoreFoundation)
find_library(COREGRAPHICS_LIBRARY CoreGraphics)
find_library(CARBON_FRAMEWORK Carbon)
find_library(IOKIT_LIBRARY IOKIT)
find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)


#Variables storing SDL framework locations
set(SDL2 /Library/Frameworks/SDL2.framework)


add_executable(keyboardSim  ../src/main.cpp 
../src/AdvancedKeyboardSimulator.h 
../src/InputMonitor.h 
../src/Sequence.cpp 
../src/button_key_States.cpp
../src/Queue.h
../src/ArcWarden.cpp
../src/EarthSpirit.cpp
../src/LegionCommander.cpp
../src/Tusk.cpp
../src/Sniper.cpp
../src/LoneDruid.cpp
../src/QOP.cpp
../src/Invoker2.cpp
../src/Tinker.cpp
../src/ShadowFiend.cpp
../src/SkyWrath.cpp
../src/Clinkz.cpp
../src/Enigma.cpp
../src/Chen.cpp
../src/Meepo.cpp
../src/ArcWarden2.cpp
../src/BroodMother.cpp
../src/BrewMaster.cpp
../src/SSM.cpp
../src/Spell.cpp
../src/PlaySound.cpp
)

target_link_libraries(
  keyboardSim PRIVATE
  ${SDL2}/Versions/A/SDL2
  ${COREGRAPHICS_LIBRARY}
  ${COREFOUNDATION_LIBRARY}
  ${CARBON_FRAMEWORK}
  ${IOKIT_LIBRARY}
  ${APPLICATION_SERVICES_FRAMEWORK}
  ${AUDIOTOOLBOX_LIBRARY}

)

target_include_directories(
  keyboardSim PRIVATE
  ${SDL2}/Versions/A/Headers
  ${APPLICATION_SERVICES_FRAMEWORK}
)

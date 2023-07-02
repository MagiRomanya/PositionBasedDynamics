CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(pbd)

set(SOURCE_FILES
  src/main.cpp
  src/vec2.cpp
  src/simulation.cpp
  src/particle.cpp
  src/ParticleList.cpp
  src/SimpleIntegrator.cpp
  src/Renderer.cpp
  src/ParticleParticleCollisionConstraint.cpp
  src/ConstraintSolver.cpp
  src/WallConstraint.cpp
  src/CollisionAcceleration.cpp
  src/CollisionGrid.cpp
)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

find_package(Eigen3 REQUIRED)
find_package(raylib REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${Eigen_INCLUDE_DIRS}
  ${raylib_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  ${raylib_LIBRARIES}
  ${Eigen_LIBRARIES}
)

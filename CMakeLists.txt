cmake_minimum_required(VERSION 3.7...3.28)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(VickysRaytracer LANGUAGES CXX)

add_executable(raytracer
                source/main.cpp
                source/utils.h
                source/vec3.h
                source/colour.h
                source/ray.h
                source/hittable.h
                source/hittable_list.h
                source/sphere.h
                source/interval.h
                source/camera.h
                source/material.h)

target_compile_features(raytracer PUBLIC cxx_std_11)
set_target_properties(raytracer PROPERTIES CXX_EXTENSIONS OFF)
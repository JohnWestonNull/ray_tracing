cmake_minimum_required(VERSION 3.17)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(ray_tracing main.cpp hittable.h sphere.h hittable_list.h rtweekend.h)
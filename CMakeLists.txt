cmake_minimum_required(VERSION 3.15)

project(demoorb)
set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Wall")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
############### dependencies ######################
# Eigen
include_directories("/usr/include/eigen3")

# OpenCV
find_package(OpenCV 3.4.5 EXACT)
include_directories(${OpenCV_INCLUDE_DIRS})

# pangolin
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

# Sophus
find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

# G2O
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})

# glog
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

# gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# gflags
find_package(GFlags REQUIRED)
include_directories(${GFLAGS_INCLUDE_DIRS})

# csparse
find_package(CSparse REQUIRED)
include_directories(${CSPARSE_INCLUDE_DIR})

add_library(DEMO SHARED
    ${PROJECT_SOURCE_DIR}/src/frame.cc
    ${PROJECT_SOURCE_DIR}/src/camera.cc
    ${PROJECT_SOURCE_DIR}/src/mappoint.cc
    ${PROJECT_SOURCE_DIR}/src/map.cc
    ${PROJECT_SOURCE_DIR}/src/feature.cc
    ${PROJECT_SOURCE_DIR}/src/backend.cc
    ${PROJECT_SOURCE_DIR}/src/frontend.cc
    ${PROJECT_SOURCE_DIR}/src/config.cc
    ${PROJECT_SOURCE_DIR}/src/dataset.cc
    ${PROJECT_SOURCE_DIR}/src/VO.cc
    ${PROJECT_SOURCE_DIR}/src/viewer.cc
    )

target_link_libraries(
    DEMO
    ${OpenCV_LIBS}
    ${Sophus_LIBRARIES}
    ${Pangolin_LIBRARIES} GL GLU GLEW
    g2o_core g2o_stuff g2o_types_sba g2o_solver_csparse g2o_csparse_extension
    ${GTEST_BOTH_LIBRARIES}
    ${GLOG_LIBRARIES}
    ${GFLAGS_LIBRARIES}
    pthread
    ${CSPARSE_LIBRARY}
)

add_executable(runkitti ${PROJECT_SOURCE_DIR}/app/runkitti.cc)
target_link_libraries(runkitti DEMO)

add_subdirectory(test)


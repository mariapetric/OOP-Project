cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# external dependencies with FetchContent

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# din cauza SFML
set(WARNINGS_AS_ERRORS OFF)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:33
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.2
        # GIT_TAG        5383d2b3948f805af55c9f8a4587ac72ec5981d1 # 2.6.2
        # GIT_TAG        origin/master
        GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)

FetchContent_MakeAvailable(SFML)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        generated/src/Helper.cpp
        generated/src/Street.cpp
        generated/src/Intersection.cpp
        generated/src/Stoplight.cpp
        generated/src/Utils.cpp
        generated/src/Vehicle.cpp
        generated/src/Simulator.cpp
        generated/src/TrafficSimulationException.cpp
        generated/src/VehicleFactory.cpp
        generated/src/Car.cpp
        generated/src/Bus.cpp
        generated/src/PriorityVehicle.cpp
        generated/src/Behaviour.cpp
        generated/src/CarBehaviour.cpp
        generated/src/BusBehaviour.cpp
        generated/src/PriorityBehaviour.cpp
        generated/src/GraphicSimulator.cpp
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
# set_compiler_flags(TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${FOO} ${BAR})
# where ${FOO} and ${BAR} represent additional executables or libraries
# you want to compile with the set compiler flags

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system Threads::Threads)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# copy dependent DLLs to build dir
# see https://en.sfml-dev.org/forums/index.php?topic=28580.0
# remove this if not using audio or if using SFML 3
if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${MAIN_EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
            $<TARGET_FILE_DIR:${MAIN_EXECUTABLE_NAME}>
    )
endif()


copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

#cmake_minimum_required(VERSION 3.26)
#project(oop)
#
#set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
#
#include(cmake/Options.cmake)
#include(cmake/CompilerFlags.cmake)
#include(cmake/CopyHelper.cmake)
#
## If building on Windows and you installed SFML somewhere custom, only then set SFML_DIR.
#if(WIN32)
#    # Change this to wherever you keep SFML on your dev machine:
#    set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
#endif()
#
#find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
#
#add_executable(oop
#        main.cpp
#        generated/src/Helper.cpp
#        generated/src/Street.cpp
#        generated/src/Intersection.cpp
#        generated/src/Stoplight.cpp
#        generated/src/Utils.cpp
#        generated/src/Vehicle.cpp
#        generated/src/Simulator.cpp
#        generated/src/TrafficSimulationException.cpp
#        generated/src/VehicleFactory.cpp
#        generated/src/Car.cpp
#        generated/src/Bus.cpp
#        generated/src/PriorityVehicle.cpp
#        generated/src/Behaviour.cpp
#        generated/src/CarBehaviour.cpp
#        generated/src/BusBehaviour.cpp
#        generated/src/PriorityBehaviour.cpp
#        generated/src/GraphicSimulator.cpp
#)
#
#target_link_libraries(oop PRIVATE sfml-graphics sfml-window sfml-system)
#
#set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES oop)
#
#target_include_directories(oop SYSTEM PRIVATE generated/include)
#
#install(TARGETS oop DESTINATION ${DESTINATION_DIR})
#if(APPLE)
#    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
#endif()
#
#copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME oop)


#cmake_minimum_required(VERSION 3.26)
#
## NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
## for now, the project name is used as the executable name
#set(MAIN_PROJECT_NAME "oop")
#set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")
#
#project(${MAIN_PROJECT_NAME})
#
#set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
#
#include(cmake/Options.cmake)
#include(cmake/CompilerFlags.cmake)
#include(cmake/CopyHelper.cmake)
#
## Set SFML path if it is not installed globally
#set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
#
#find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
#
## External dependencies with FetchContent
## include(FetchContent)
##
## set(FETCHCONTENT_QUIET OFF)
## set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
##
## NOTE: Also update env vars used for caching in
##         - .github/actions/configure-cmake/action.yml
##         - .github/workflows/cmake.yml
## FetchContent_Declare(
##         SomeLib
##         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
##         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
##         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
## )
##
## FetchContent_MakeAvailable(SomeLib)
#
## External dependencies with find_package
#
## find_package(Threads REQUIRED)
#
## NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
#add_executable(${MAIN_EXECUTABLE_NAME}
#        main.cpp
#        generated/src/Helper.cpp
#        generated/src/Street.cpp
#        generated/src/Intersection.cpp
#        generated/src/Stoplight.cpp
#        generated/src/Utils.cpp
#        generated/src/Vehicle.cpp
#        generated/src/Simulator.cpp
#        generated/src/TrafficSimulationException.cpp
#        generated/src/VehicleFactory.cpp
#        generated/src/Car.cpp
#        generated/src/Bus.cpp
#        generated/src/PriorityVehicle.cpp
#        generated/src/Behaviour.cpp
#        generated/src/CarBehaviour.cpp
#        generated/src/BusBehaviour.cpp
#        generated/src/PriorityBehaviour.cpp
#        generated/src/GraphicSimulator.cpp
#)
#
## Link SFML libraries to the project
#target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
#
## Set compiler flags (e.g., enabling sanitizers)
#set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
#
## Use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
#target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)
## target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
## target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
## target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
## target_link_libraries(${MAIN_EXECUTABLE_NAME} <SomeLib>)
#
## Copy binaries to "bin" folder; these are uploaded as artifacts on each release
## DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
#install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
#if(APPLE)
#    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
#endif()
#
#copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
## copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
## copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
#

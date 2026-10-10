cmake_minimum_required(VERSION 3.16)
project(LR1_Protector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LR1_Protector main.cpp)

if(WIN32)
    target_link_libraries(LR1_Protector PRIVATE advapi32)

    get_filename_component(LR1_MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    find_file(LR1_LIBSTDCXX_DLL NAMES libstdc++-6.dll PATHS "${LR1_MINGW_BIN_DIR}" NO_DEFAULT_PATH)
    find_file(LR1_LIBGCC_DLL NAMES libgcc_s_seh-1.dll PATHS "${LR1_MINGW_BIN_DIR}" NO_DEFAULT_PATH)
    find_file(LR1_LIBWINPTHREAD_DLL NAMES libwinpthread-1.dll PATHS "${LR1_MINGW_BIN_DIR}" NO_DEFAULT_PATH)

    foreach(_dll IN ITEMS LR1_LIBSTDCXX_DLL LR1_LIBGCC_DLL LR1_LIBWINPTHREAD_DLL)
        if(${_dll})
            add_custom_command(TARGET LR1_Protector POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${${_dll}}" "$<TARGET_FILE_DIR:LR1_Protector>")
        endif()
    endforeach()
endif()

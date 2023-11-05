cmake_minimum_required(VERSION 3.10)
project(aed_schedule_project)

set(CMAKE_CXX_STANDARD 11)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
                    COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
                    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                    COMMENT "Generating API documentation with Doxygen"
                    VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

add_executable(aed_schedule_project main.cpp classes/allMenus.h classes/allMenus.cpp classes/CollegeClass.h classes/CollegeClass.cpp
    classes/Lesson.h classes/Lesson.cpp classes/Parser.h classes/Parser.cpp classes/Schedule.h 
    classes/Schedule.cpp classes/Student.h classes/Student.cpp classes/Dataset.cpp classes/Dataset.cpp classes/Request.h 
    classes/Request.cpp classes/menuFunctions.h classes/menuFunctions.cpp)
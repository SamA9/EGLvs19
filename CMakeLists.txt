# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

set( PROJECT_NAME EGL)

project (${PROJECT_NAME})

# Добавьте источник в исполняемый файл этого проекта.
if( ${CMAKE_BUILD_TYPE} MATCHES  "Debug" )
set( OUT_EXE EGL_debug)
else()
set( OUT_EXE EGL)
endif()

# файлы крмпилятии проекта EGL
set( FILE_MAIN_COMPIL
	# begin 
	src/main/EGL.cpp
	src/main/EGL.h
	# end 
	 "src/external/CPUID.h" "src/external/FINI/fini.cpp" "src/external/FINI/fini.h")

add_executable (${OUT_EXE} ${FILE_MAIN_COMPIL} )

# Добавьте источник в исполняемый файл этого проекта.
if( ${CMAKE_BUILD_TYPE} MATCHES  "Debug" )
# Путь выходда exe пири ghb приотладке  
set_target_properties( ${OUT_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
else()
# Путь выходда exe Relese 
set_target_properties( ${OUT_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
# Копирование exe в папку bin атуальный файл там 
add_custom_command( TARGET ${OUT_EXE} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy  $<TARGET_FILE_DIR:${OUT_EXE}>/${OUT_EXE}.exe ${CMAKE_SOURCE_DIR}/bin)
#
endif()


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
# компилируем GLFW
add_subdirectory(src/external/glfw)
# компилируем GLAD
add_subdirectory(src/external/glad)
#target_link_libraries(${OUT_EXE} PRIVATE glad)
# Линкуем к exe-нику
target_link_libraries(${OUT_EXE} glfw glad)
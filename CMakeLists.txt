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
	)

add_executable (${OUT_EXE} ${FILE_MAIN_COMPIL} )
# Путь выходда exe 
set_target_properties( ${OUT_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
# Копирование exe в папку бин
add_custom_command( TARGET ${OUT_EXE} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy  $<TARGET_FILE_DIR:${OUT_EXE}>/${OUT_EXE}.exe ${CMAKE_SOURCE_DIR}/bin)



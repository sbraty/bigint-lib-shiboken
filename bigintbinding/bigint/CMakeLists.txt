project(bigint)

cmake_minimum_required(VERSION 2.8)
 
set(bigint_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/bigint/bigint_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/bigint/bigint_wrapper.cpp
)
 
set(bigint_INCLUDE_DIRECTORIES
    ${SHIBOKEN_INCLUDE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${PYSIDE_INCLUDE_DIR}
    ${PYSIDE_INCLUDE_DIR}/QtCore
    ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${LIBBIGINT_DIR}
)
 
set(bigint_LINK_LIBRARIES
    ${QT_QTCORE_LIBRARY}
    ${SHIBOKEN_PYTHON_LIBRARIES}
    ${SHIBOKEN_LIBRARY}
    ${PYSIDE_LIBRARY}
    ${LIBBIGINT_DIR}/libbigint.so
)
 
include_directories(bigint ${bigint_INCLUDE_DIRECTORIES})
add_library(bigint MODULE ${bigint_SRC})
set_property(TARGET bigint PROPERTY PREFIX "")
target_link_libraries(bigint ${bigint_LINK_LIBRARIES})
 
add_custom_command(OUTPUT ${bigint_SRC}
                   COMMAND
                   shiboken --enable-parent-ctor-heuristic --enable-pyside-extensions --enable-return-value-heuristic
                   ${CMAKE_CURRENT_SOURCE_DIR}/global.h
                   --include-paths=${QT_INCLUDE_DIR}:${LIBBIGINT_DIR}
                   --typesystem-paths=${typesystem_path}:${PYSIDE_TYPESYSTEMS}
                   --output-directory=${CMAKE_CURRENT_BINARY_DIR}
                   ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_bigint.xml
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "Running Shiboken for libbigint..."
                  )

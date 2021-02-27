cmake_minimum_required (VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project (glui)
set(SOURCE_FILES
    src/algebra3.cpp
    src/arcball.cpp
    src/glui_add_controls.cpp
    src/glui_bitmaps.cpp
    src/glui_button.cpp
    src/glui_checkbox.cpp
    src/glui_column.cpp
    src/glui_commandline.cpp
    src/glui_control.cpp
    src/glui.cpp
    src/glui_edittext.cpp
    src/glui_filebrowser.cpp
    src/glui_listbox.cpp
    src/glui_list.cpp
    src/glui_mouse_iaction.cpp
    src/glui_node.cpp
    src/glui_panel.cpp
    src/glui_radio.cpp
    src/glui_rollout.cpp
    src/glui_rotation.cpp
    src/glui_scrollbar.cpp
    src/glui_separator.cpp
    src/glui_spinner.cpp
    src/glui_statictext.cpp
    src/glui_textbox.cpp
    src/glui_translation.cpp
    src/glui_tree.cpp
    src/glui_treepanel.cpp
    src/glui_window.cpp
    src/quaternion.cpp
    src/viewmodel.cpp
)

if (UNIX OR MINGW OR CYGWIN)
     add_compile_options(-O3)
     add_compile_options(-Wno-all)
     add_compile_options(-Wno-pedantic)
     add_compile_options(-Wno-unused-parameter)
elseif (MSVC)
endif ()

include_directories(${CMAKE_SOURCE_DIR}/lib/freeglut/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/glui/include)
add_library (${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} freeglut_static)



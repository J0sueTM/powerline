cmake_minimum_required(VERSION 3.26)

project(powerline)

set(CMAKE_C_STANDARD 99)

if (CMAKE_DEBUG)
  add_compile_options("-g")
endif ()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/sdl2)
include_directories(lib/sdl2)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(lib/glad)
set(GLAD_SRC
  lib/glad/glad.h
  lib/glad/khrplatform.h
  lib/glad/glad.c)
add_library(glad STATIC ${GLAD_SRC})
target_link_libraries(glad ${OPENGL_LIBRARIES})

include_directories(lib/nuklear lib/nuklear/src)
set(NUKLEAR_SRC
  lib/nuklear/nuklear.h
  lib/nuklear/src/stb_rect_pack.h
  lib/nuklear/src/stb_truetype.h
  lib/nuklear/src/nuklear_9slice.c
  lib/nuklear/src/nuklear_buffer.c
  lib/nuklear/src/nuklear_button.c
  lib/nuklear/src/nuklear_chart.c
  lib/nuklear/src/nuklear_color.c
  lib/nuklear/src/nuklear_color_picker.c
  lib/nuklear/src/nuklear_combo.c
  lib/nuklear/src/nuklear_context.c
  lib/nuklear/src/nuklear_contextual.c
  lib/nuklear/src/nuklear_draw.c
  lib/nuklear/src/nuklear_edit.c
  lib/nuklear/src/nuklear_font.c
  lib/nuklear/src/nuklear_group.c
  lib/nuklear/src/nuklear_image.c
  lib/nuklear/src/nuklear_input.c
  lib/nuklear/src/nuklear_internal.h
  lib/nuklear/src/nuklear_layout.c
  lib/nuklear/src/nuklear_list_view.c
  lib/nuklear/src/nuklear_math.c
  lib/nuklear/src/nuklear_menu.c
  lib/nuklear/src/nuklear_page_element.c
  lib/nuklear/src/nuklear_panel.c
  lib/nuklear/src/nuklear_pool.c
  lib/nuklear/src/nuklear_popup.c
  lib/nuklear/src/nuklear_progress.c
  lib/nuklear/src/nuklear_property.c
  lib/nuklear/src/nuklear_scrollbar.c
  lib/nuklear/src/nuklear_selectable.c
  lib/nuklear/src/nuklear_slider.c
  lib/nuklear/src/nuklear_string.c
  lib/nuklear/src/nuklear_style.c
  lib/nuklear/src/nuklear_table.c
  lib/nuklear/src/nuklear_text.c
  lib/nuklear/src/nuklear_text_editor.c
  lib/nuklear/src/nuklear_toggle.c
  lib/nuklear/src/nuklear_tooltip.c
  lib/nuklear/src/nuklear_tree.c
  lib/nuklear/src/nuklear_utf8.c
  lib/nuklear/src/nuklear_util.c
  lib/nuklear/src/nuklear_vertex.c
  lib/nuklear/src/nuklear_widget.c
  lib/nuklear/src/nuklear_window.c)
add_library(nuklear STATIC ${NUKLEAR_SRC})
target_link_libraries(nuklear SDL2-static ${OPENGL_LIBRARIES})

include_directories(lib/log.c/src)
set(LOG_C_SRC
  lib/log.c/src/log.h
  lib/log.c/src/log.c)
add_library(log.c STATIC ${LOG_C_SRC})
target_compile_definitions(log.c PRIVATE -DLOG_USE_COLOR)

set(SRC
  src/engine/window.h
  src/engine/window.c
  src/engine/engine.h
  src/engine/engine.c
  src/engine/renderer.h
  src/engine/renderer.c
  src/editor/ui.h
  src/editor/ui.c
  src/core.h
  src/main.c)
add_executable(powerline ${SRC})
target_link_libraries(powerline
  SDL2-static
  nuklear
  ${OPENGL_LIBRARIES}
  glad
  log.c)

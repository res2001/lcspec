# Файл для включения в проект на CMAKE.
# Перед включением необходимо определить переменные
#    LCSPEC_DIR   - путь к директории, где находится файлы lcspec (по умолчанию lib/lcspec)
#
# После включения будут добавлены в директории заголовков нужные для lcspec директории


if (NOT LCSPEC_DIR)
  set(LCSPEC_DIR lib/lcspec)
endif(NOT LCSPEC_DIR)

include_directories(${LCSPEC_DIR})

if(MSVC)
    include_directories(${LCSPEC_DIR}/msvc)
elseif(CMAKE_COMPILER_IS_GNUCC)
    include_directories(${LCSPEC_DIR}/gcc)
elseif(${CMAKE_C_COMPILER_ID} STREQUAL "Watcom")
    include_directories(${LCSPEC_DIR}/watcom)
elseif(${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    include_directories(${LCSPEC_DIR}/gcc)
endif()
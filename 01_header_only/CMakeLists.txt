# Указываем минимальную требуемую версию CMake (3.15 в данном случае).
# Это гарантирует совместимость с используемыми функциями CMake.
cmake_minimum_required(VERSION 3.15)

# Создаем исполняемый файл с именем "header_only".
# Исполняемый файл будет создан из исходного файла "main.cpp".
add_executable(header_only
        main.cpp)

# Добавляем директорию с заголовочными файлами для компиляции.
# Указываем путь к директории "json/include", где находятся заголовочные файлы.
# Ключевое слово PUBLIC означает, что этот путь будет доступен и для других целей,
# которые зависят от этого целевого объекта (например, другие библиотеки или исполняемые файлы).
target_include_directories(header_only
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json/include)

# Указываем, что для компиляции требуется стандарт C++17.
# Это гарантирует, что компилятор будет использовать стандарт C++17.
target_compile_features(header_only PUBLIC cxx_std_17)

# Устанавливаем свойство для целевого объекта "header_only",
# которое требует строгого соблюдения указанного стандарта C++ (C++17 в данном случае).
# Если компилятор не поддерживает этот стандарт, сборка завершится с ошибкой.
set_target_properties(header_only PROPERTIES CXX_STANDARD_REQUIRED ON)

# Проверяем, какой компилятор используется: Clang или GNU (GCC).
# В зависимости от компилятора задаются разные флаги компиляции.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Устанавливаем флаги компиляции для Clang или GCC:
  # -g — добавляет отладочную информацию.
  # -Wall — включает все стандартные предупреждения.
  # -Wextra — включает дополнительные предупреждения.
  # -Werror — трактует предупреждения как ошибки.
  # -pedantic — включает строгую проверку на соответствие стандарту.
  target_compile_options(header_only
          PRIVATE
          -g
          -Wall
          -Wextra
          -Werror
          -pedantic)
  # Проверяем, используется ли компилятор MSVC (Microsoft Visual C++).
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Устанавливаем флаги компиляции для MSVC:
  # /EHsc — включает обработку исключений C++.
  # /W4 — включает большинство предупреждений.
  # /WX — трактует предупреждения как ошибки.
  target_compile_options(header_only
          PRIVATE
          /EHsc
          /W4
          /WX)
endif()
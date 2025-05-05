# Указываем минимальную требуемую версию CMake (3.15 в данном случае).
# Это гарантирует, что CMake будет использовать функции, доступные в этой версии и выше.
cmake_minimum_required(VERSION 3.15)

# Создаем исполняемый файл с именем "linking".
# Исполняемый файл будет создан из исходного файла "main.cpp".
add_executable(linking
        main.cpp)

# Добавляем директорию с заголовочными файлами библиотеки Google Test.
# Указываем путь к директории "googletest/googletest/include", где находятся заголовочные файлы.
# Ключевое слово PUBLIC означает, что этот путь будет доступен и для других целей,
# которые зависят от этого целевого объекта (например, другие библиотеки или исполняемые файлы).
target_include_directories(linking
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)

# Добавляем директорию с бинарными файлами (библиотеками) Google Test.
# Указываем путь к директории "googletest/build/lib", где находятся скомпилированные библиотеки.
# Это необходимо, чтобы компоновщик знал, где искать библиотеки для линковки.
target_link_directories(linking
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/googletest/build/lib)

# Указываем, с какими библиотеками нужно линковать проект.
# В данном случае, линкуем с библиотеками Google Test: "gtest" и "gtest_main".
# Ключевое слово PUBLIC означает, что эти библиотеки будут доступны и для других целей,
# которые зависят от этого целевого объекта.
target_link_libraries(linking
        PUBLIC gtest gtest_main)

# Указываем, что для компиляции требуется стандарт C++17.
# Это гарантирует, что компилятор будет использовать стандарт C++17.
target_compile_features(linking PUBLIC cxx_std_17)

# Устанавливаем свойство для целевого объекта "linking",
# которое требует строгого соблюдения указанного стандарта C++ (C++17 в данном случае).
# Если компилятор не поддерживает этот стандарт, сборка завершится с ошибкой.
set_target_properties(linking PROPERTIES CXX_STANDARD_REQUIRED ON)

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
  target_compile_options(linking
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
  target_compile_options(linking
          PRIVATE
          /EHsc
          /W4
          /WX)
endif()

# Для сборки googletest из исходников перед линковкой
# git clone https://github.com/google/googletest.git
# cd googletest
# mkdir build
# cd build
# cmake ..
# make
# Устанавливаем минимальную требуемую версию CMake (достаточную для используемых функций)
cmake_minimum_required(VERSION 3.15)

# Создаем исполняемый файл с именем "find_package" из исходного файла main.cpp
# Имя цели (find_package) может не совпадать с итоговым именем бинарного файла
add_executable(find_package
        main.cpp)

# Ищем библиотеку nlohmann_json версии 3.10.4 (обязательную для сборки)
# CMake будет проверять пути из CMAKE_PREFIX_PATH и стандартные расположения
find_package(nlohmann_json 3.10.4 REQUIRED)

# Связываем наш исполняемый файл с библиотекой nlohmann_json
# PRIVATE означает, что зависимости нужны ТОЛЬКО для сборки этой цели
target_link_libraries(find_package
        PRIVATE nlohmann_json::nlohmann_json)

################################################################################

# Включаем поддержку C++17 для компилятора (PUBLIC распространяет флаг на связанные цели)
target_compile_features(find_package PUBLIC cxx_std_17)

# Запрещаем использование стандарта ниже указанного (гарантируем строгое соблюдение C++17)
set_target_properties(find_package PROPERTIES CXX_STANDARD_REQUIRED ON)

# Настраиваем флаги компиляции в зависимости от используемого компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Для Clang/GCC включаем:
  # -g - отладочная информация
  # -Wall - все стандартные предупреждения
  # -Wextra - дополнительные предупреждения
  # -Werror - трактовать предупреждения как ошибки
  # -pedantic - строгое соответствие стандарту
  target_compile_options(find_package
          PRIVATE
          -g
          -Wall
          -Wextra
          -Werror
          -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Для MSVC включаем:
  # /EHsc - обработка исключений
  # /W4 - уровень предупреждений (максимальный)
  # /WX - трактовать предупреждения как ошибки
  target_compile_options(find_package
          PRIVATE
          /EHsc
          /W4
          /WX)
endif()
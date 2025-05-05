# Указываем минимальную требуемую версию CMake (3.15)
# Гарантирует использование современных функций CMake
cmake_minimum_required(VERSION 3.15)

# Создаем исполняемый файл с именем "sha256_from_HelloWorld"
# Исполняемый файл собирается из исходного файла main.cpp
add_executable(sha256_from_HelloWorld
        main.cpp)

# Добавляем путь к заголовочным файлам OpenSSL
# Указываем директорию openssl/build/include как PUBLIC, чтобы зависимости тоже видели этот путь
target_include_directories(sha256_from_HelloWorld
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openssl/build/include)

# Добавляем путь к бинарным библиотекам OpenSSL
# Указываем директорию openssl/build/lib, где находятся файлы .so/.dll/.a
target_link_directories(sha256_from_HelloWorld
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openssl/build/lib)

# Линкуем исполняемый файл с библиотеками OpenSSL
# ssl и crypto - названия библиотек, которые нужно подключить
target_link_libraries(sha256_from_HelloWorld
        PUBLIC ssl crypto)

# Указываем стандарт C++17 для компиляции
# Гарантирует использование возможностей C++17
target_compile_features(sha256_from_HelloWorld PUBLIC cxx_std_17)

# Требуем строгого соблюдения стандарта C++17
# Сборка прервется, если компилятор не поддерживает C++17
set_target_properties(sha256_from_HelloWorld PROPERTIES CXX_STANDARD_REQUIRED ON)

# Настройка флагов компилятора для разных платформ
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Флаги для Clang/GCC:
  # -g - отладочная информация
  # -Wall - все стандартные предупреждения
  # -Wextra - дополнительные предупреждения
  # -Werror - трактовать предупреждения как ошибки
  # -pedantic - строгое соответствие стандарту
  target_compile_options(sha256_from_HelloWorld
          PRIVATE
          -g
          -Wall
          -Wextra
          -Werror
          -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Флаги для MSVC:
  # /EHsc - безопасная обработка исключений
  # /W4 - максимальный уровень предупреждений
  # /WX - трактовать предупреждения как ошибки
  target_compile_options(sha256_from_HelloWorld
          PRIVATE
          /EHsc
          /W4
          /WX)
endif()
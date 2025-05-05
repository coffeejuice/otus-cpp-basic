# Установка минимальной версии CMake для обеспечения совместимости функций
cmake_minimum_required(VERSION 3.15)

# Создание исполняемого файла с именем external_project из исходника main.cpp
add_executable(external_project
        main.cpp)

# Подключение модуля для работы с внешними проектами/зависимостями
include(ExternalProject)

# Настройка загрузки и сборки OpenSSL как внешней зависимости
ExternalProject_Add(openssl
        PREFIX openssl                 # Каталог для файлов сборки (${CMAKE_BINARY_DIR}/openssl)
        GIT_REPOSITORY https://github.com/openssl/openssl.git  # URL репозитория
        GIT_TAG openssl-3.0.5          # Используемая версия/тег
        GIT_SHALLOW 1                  # Поверхностное клонирование (только последний коммит)
        # Конфигурация сборки с указанием путей установки
        CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/06_ExternalProject/openssl/src/openssl/Configure
        --prefix=${CMAKE_BINARY_DIR}/06_ExternalProject/openssl/src/openssl-build  # Каталог установки
        --openssldir=${CMAKE_BINARY_DIR}/06_ExternalProject/openssl/src/openssl-build  # Каталог конфигов
        # Параллельная сборка с использованием 8 ядер
        BUILD_COMMAND make ${CMAKE_BINARY_DIR}/06_ExternalProject/openssl/src/openssl -j 8
        # Установка собранных библиотек и заголовков
        INSTALL_COMMAND make ${CMAKE_BINARY_DIR}/06_ExternalProject/openssl/src/openssl install)

# Указание зависимости сборки external_project от завершения сборки openssl
add_dependencies(external_project openssl)

# Добавление каталога с библиотеками OpenSSL для линковки
target_link_directories(external_project
        PUBLIC ${CMAKE_BINARY_DIR}/06_ExternalProject/openssl/src/openssl-build/include/lib64)

# Добавление каталога с заголовочными файлами OpenSSL
target_include_directories(external_project
        PUBLIC ${CMAKE_BINARY_DIR}/06_ExternalProject/openssl/src/openssl-build/include)

# Линковка с библиотеками OpenSSL (libssl.so/libssl.a и libcrypto.so/libcrypto.a)
target_link_libraries(external_project
        PUBLIC ssl crypto)

################################################################################

# Включение поддержки стандарта C++17 для целевого проекта
target_compile_features(external_project PUBLIC cxx_std_17)
# Требование строгого соблюдения стандарта (запрет fallback на старые версии)
set_target_properties(external_project PROPERTIES CXX_STANDARD_REQUIRED ON)

# Настройка флагов компиляции в зависимости от используемого компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Флаги для Clang/GCC:
  target_compile_options(external_project
          PRIVATE
          -g          # Включение отладочной информации
          -Wall       # Включение всех стандартных предупреждений
          -Wextra     # Дополнительные предупреждения
          -Werror     # Трактовать предупреждения как ошибки
          -pedantic)  # Строгое соответствие стандарту
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Флаги для MS Visual C++:
  target_compile_options(external_project
          PRIVATE
          /EHsc       # Включение обработки исключений
          /W4         # Уровень предупреждений (максимальный для MSVC)
          /WX)        # Трактовать предупреждения как ошибки
endif()
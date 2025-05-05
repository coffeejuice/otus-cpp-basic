# Устанавливаем минимальную требуемую версию CMake (3.15+ для полной поддержки FetchContent)
cmake_minimum_required(VERSION 3.15)

# Создаем исполняемый файл с именем "fetch_content" из исходника main.cpp
add_executable(fetch_content
        main.cpp)

# Включаем модуль CMake для работы с зависимостями через git/subversion и т.д.
include(FetchContent)

# Настраиваем загрузку библиотеки JSON:
# GIT_REPOSITORY - URL репозитория
# GIT_TAG - конкретная версия (тег v3.10.4)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.4)

# Проверяем статус загрузки пакета
FetchContent_GetProperties(json)
if(NOT json_POPULATED)  # Если пакет еще не загружен
  # Скачиваем и распаковываем исходники
  FetchContent_Populate(json)
  # Подключаем скачанную библиотеку как подпроект:
  # EXCLUDE_FROM_ALL - не собирать цели библиотеки по умолчанию
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Связываем наш исполняемый файл с импортированной библиотекой
target_link_libraries(fetch_content
        PRIVATE nlohmann_json::nlohmann_json)

################################################################################

# Включаем поддержку C++17 для компилятора
target_compile_features(fetch_content PUBLIC cxx_std_17)

# Запрещаем откат к более старым стандартам (строгое соблюдение C++17)
set_target_properties(fetch_content PROPERTIES CXX_STANDARD_REQUIRED ON)

# Настраиваем флаги компиляции в зависимости от компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Для Clang/GCC:
  # -g - отладочная информация
  # -Wall/Wextra - максимальный уровень предупреждений
  # -Werror - предупреждения как ошибки
  # -pedantic - строгий стандарт
  target_compile_options(fetch_content
          PRIVATE
          -g
          -Wall
          -Wextra
          -Werror
          -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Для MSVC:
  # /EHsc - безопасная модель исключений
  # /W4 - уровень предупреждений (4 = максимальный)
  # /WX - предупреждения как ошибки
  target_compile_options(fetch_content
          PRIVATE
          /EHsc
          /W4
          /WX)
endif()
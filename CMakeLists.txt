# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.24)
# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)

# Определяем имя проекта, версию и используемые языки
project(my-ostis-system VERSION 0.10.0 LANGUAGES C CXX)
# Устанавливаем политику CMake для обработки версий проекта
cmake_policy(SET CMP0048 NEW)

# Устанавливаем директории вывода для исполняемых файлов и библиотек
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(SC_EXTENSIONS_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/extensions)

# Ищем пакет sc-machine, он обязателен для проекта
find_package(sc-machine REQUIRED)

# Ищем пакет GTest для тестирования агентов
include(GoogleTest)
find_package(GTest REQUIRED)

# Добавляем поддиректорию problem-solver в процесс сборки
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/problem-solver)

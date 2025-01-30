# Находим все файлы с расширениями .cpp и .hpp в текущей директории и поддиректории agent.
file(GLOB SOURCES CONFIGURE_DEPENDS
    "*.cpp" "*.hpp"
    "agent/*.cpp" "agent/*.hpp"
    "keynodes/*.hpp"
)

# Создаём динамическую библиотеку set-agents.
add_library(set-agents SHARED ${SOURCES})
# Добавляем открытую зависимость от библиотеки sc-memory из пакета sc-machine.
target_link_libraries(set-agents LINK_PUBLIC sc-machine::sc-memory)
# Добавляем текущую директорию исходного кода в список путей для поиска заголовочных файлов.
target_include_directories(set-agents PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Устанавливаем свойства для цели set-agents
set_target_properties(set-agents
    # Указываем директорию для вывода скомпилированной библиотеки.
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SC_EXTENSIONS_DIRECTORY}
)

# CMakeLists.txt
# Собираем все файлы с расширением .cpp из директории tests.
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    "tests/*.cpp"
)

# Создаём исполняемый файл для тестов.
add_executable(set-agents-tests ${TEST_SOURCES})
# Связываем тесты с библиотекой модуля с агентом.
target_link_libraries(set-agents-tests
    LINK_PRIVATE GTest::gtest_main
    LINK_PRIVATE set-agents
)
# Добавляем директорию с исходниками в список путей для поиска заголовочных файлов.
target_include_directories(set-agents-tests 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Добавляем тесты в проект.
# TEST_LIST содержит список всех файлов с тестами.
# WORKING_DIRECTORY устанавливает рабочую директорию для запуска тестов.
gtest_discover_tests(set-agents-tests
    TEST_LIST ${TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

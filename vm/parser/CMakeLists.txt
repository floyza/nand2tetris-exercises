project (parser)

add_library (${PROJECT_NAME} src/lexer.cpp src/parser.cpp)

target_include_directories (${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

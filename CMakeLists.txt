cmake_minimum_required(VERSION 3.0)
project(ACEBFA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/execs)

set(SAFEDIR ${CMAKE_SOURCE_DIR}/SafeExec/)
set(PARSERDIR ${CMAKE_SOURCE_DIR}/src/Parser/)
set(EXECSDIR ${CMAKE_SOURCE_DIR}/execs/)


message("Checking os-detect first...")

execute_process(COMMAND mkdir -p ${EXECSDIR})

execute_process(
        COMMAND clang ${SAFEDIR}extra/os-detect.c -o ${EXECSDIR}os-detect -Wall -Wextra -ansi -pedantic
        OUTPUT_VARIABLE O_VAR
        ERROR_VARIABLE E_VAR
        RESULT_VARIABLE R_VAR
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

message("Compiled os-detect...${O_VAR} | Error Message: ${E_VAR} | Exit Code: ${R_VAR}")

execute_process(
        COMMAND ${EXECSDIR}os-detect
        OUTPUT_VARIABLE OSDETECT_FLAG
        ERROR_VARIABLE E_VAR
        RESULT_VARIABLE R_VAR
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

message("Result of os-detect is: ${OSDETECT_FLAG} | Error Message: ${E_VAR} | Exit Code: ${R_VAR}")

set(WARNING_FLAGS "-Wno-write-strings -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEFAULT_SOURCE ${OSDETECT_FLAG} ${WARNING_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_DEFAULT_SOURCE ${OSDETECT_FLAG} ${WARNING_FLAGS}")


file(GLOB MAIN_ANALYZE_Files src/Analyze/*.cpp ${SAFEDIR}*.h ${SAFEDIR}error.cpp ${SAFEDIR}safe.cpp ${SAFEDIR}safeexec.cpp)
file(GLOB FUNCTION_ANALYZE_Files src/Function/*.cpp src/Function/*.h)
file(GLOB SIMPLE_SAFEEXEC_Files ${SAFEDIR}*.cpp ${SAFEDIR}*.h)

file(GLOB parser_GGO ${PARSERDIR}*.ggo)

string(REPLACE ".ggo" ".c" parser_SRC ${parser_GGO})
string(REPLACE ".ggo" ".h" parser_HDR ${parser_GGO})

add_executable(MAIN_ANALYZE ${MAIN_ANALYZE_Files} ${parser_SRC} ${parser_HDR})
add_executable(FUNCTION_ANALYZE ${FUNCTION_ANALYZE_Files})
add_executable(SIMPLE_SAFEEXEC ${SIMPLE_SAFEEXEC_Files})

target_link_libraries(MAIN_ANALYZE pthread)
target_link_libraries(SIMPLE_SAFEEXEC pthread)

add_custom_command(
        OUTPUT ${parser_SRC} ${parser_HDR}
        COMMAND gengetopt --input=${parser_GGO} --include-getopt --output-dir=${PARSERDIR}
        DEPENDS ${parser_GGO}
        COMMENT "Running gengetopt..."
)

add_custom_target(
        GenGetOptGenerated
        DEPENDS ${parser_SRC} ${parser_HDR}
)

add_dependencies(MAIN_ANALYZE GenGetOptGenerated)


enable_testing()
add_test(NAME 25
        COMMAND ./sudo.sh ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/b_25.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME 75
        COMMAND ./sudo.sh ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/b_75.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME greedy
        COMMAND ./sudo.sh ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/b_greedy.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_test(NAME good
        COMMAND ./sudo.sh ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/good_solution_for_b.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

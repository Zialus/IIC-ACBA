cmake_minimum_required(VERSION 3.0)
project(ACEBFA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -D_DEFAULT_SOURCE -Wno-write-strings")

set(SAFEDIR ${PROJECT_SOURCE_DIR}/SafeExec/)
set(PARSERDIR ${PROJECT_SOURCE_DIR}/Parser/)

set(TheFiles analyzer.cpp ${SAFEDIR}error.cpp ${SAFEDIR}safe.cpp ${SAFEDIR}/safeexec.h ${SAFEDIR}/safeexec.cpp ${PARSERDIR}cmdline.c ${PARSERDIR}cmdline.h )
set(The_Other_Files doFunctions.cpp applyfunction.cpp applyfunction.h pearson.cpp pearson.h )


add_executable(ANALYZE ${TheFiles})
add_executable(FUNCTION_ANALYZE ${The_Other_Files})

target_link_libraries(ANALYZE pthread rt)


add_custom_command(
        OUTPUT ${PARSERDIR}cmdline.c ${PARSERDIR}cmdline.h
        COMMAND gengetopt --input=${PARSERDIR}cmdline.ggo --include-getopt --output-dir=${PARSERDIR}
        DEPENDS ${PARSERDIR}cmdline.ggo
        COMMENT "Running gengetopt..."
)

add_custom_target(
        GenGetOptGenerated
        DEPENDS ${PARSERDIR}cmdline.c ${PARSERDIR}cmdline.h
)

add_dependencies(ANALYZE GenGetOptGenerated)
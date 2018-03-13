add_executable(copy-elision-on copy-elision.cpp)

add_executable(copy-elision-off copy-elision.cpp)
target_compile_options(copy-elision-off PUBLIC -fno-elide-constructors)

add_executable(exception-elision-on exception.cpp)

add_executable(exception-elision-off exception.cpp)
target_compile_options(exception-elision-off PUBLIC -fno-elide-constructors)

add_executable(return-value-optimization-on return-value-optimization.cpp)

add_executable(return-value-optimization-off return-value-optimization.cpp)
target_compile_options(return-value-optimization-off PUBLIC -fno-elide-constructors)

add_executable(elision-support-on elision-support.cpp)

add_executable(elision-support-off elision-support.cpp)
target_compile_options(elision-support-off PUBLIC -fno-elide-constructors)

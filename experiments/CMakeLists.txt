set(EXPERIMENTS
main
)

foreach(experiment IN LISTS EXPERIMENTS)
    add_executable(${experiment} ${experiment}.cpp)
    target_include_directories(${experiment} PRIVATE $ENV{CADMIUM} "$ENV{CADMIUM}/../json/include")
    target_compile_options(${experiment} PUBLIC -std=gnu++2b)
endforeach()

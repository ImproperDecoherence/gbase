project('gbase', 'cpp', default_options: ['cpp_std=c++23'])

add_project_arguments('-fmax-errors=1', language: 'cpp')

gbase_includes = include_directories('src')
gbase_dep = declare_dependency(include_directories: gbase_includes)

###################################################################################################
# Submodules

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')

###################################################################################################
# TEST

test_includes = []

test_sources = [
    'test/g_algorithms_test.cpp',
    'test/g_circular_buffers_test.cpp',
    'test/g_enumerate_test.cpp',
    'test/g_dictionary_test.cpp',
    'test/g_geometry_test.cpp',    
    'test/g_ranges_test.cpp',
    'test/g_set_test.cpp',
    'test/g_vector_test.cpp',
    'test/g_zipper_test.cpp',
]

executable(
    'run_tests',
    'test/run_tests.cpp',
    test_sources,
    dependencies: [gtest_dep],
    include_directories: [test_includes, gbase_includes],
)
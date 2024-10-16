project('gbase', 'cpp', default_options: ['cpp_std=c++23'])

add_project_arguments('-std=c++23', '-fmax-errors=1', language: 'cpp')

gbase_includes = include_directories('src')
gbase_dep = declare_dependency(include_directories: gbase_includes)

###################################################################################################
# TEST

test_includes = ['gtest/src']

test_sources = [
    'test/galgorithmstest.cpp',
    'test/gdictionarytest.cpp',
    'test/gsettest.cpp',
    'test/gvectortest.cpp',
]

executable(
    'runtests',
    'test/runtests.cpp',
    'gtest/src/testframework.cpp',
    test_sources,
    include_directories: [test_includes, gbase_includes],
)
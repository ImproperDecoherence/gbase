project('gbase', 'cpp', default_options: ['cpp_std=c++23'])

add_project_arguments('-std=c++23', '-fmax-errors=1', language: 'cpp')

###################################################################################################
# TEST

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
    include_directories: ['gtest/src', 'src'],
)
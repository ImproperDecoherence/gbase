project('gbase', 'cpp', default_options: ['cpp_std=c++23'])

add_project_arguments('-std=c++23', '-fmax-errors=1', language: 'cpp')

if get_option('buildtype') == 'debug'
    add_project_arguments('-g', language: 'cpp')
endif

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
    'test/galgorithmstest.cpp',
    'test/genumeratetest.cpp',
    'test/gdictionarytest.cpp',
    'test/gsettest.cpp',
    'test/gvectortest.cpp',
]

executable(
    'runtests',
    'test/runtests.cpp',
    test_sources,
    dependencies: [gtest_dep],
    include_directories: [test_includes, gbase_includes],
)

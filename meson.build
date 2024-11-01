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
    'test/galgorithmstest.cpp',
    'test/genumeratetest.cpp',
    'test/gdictionarytest.cpp',
    'test/ggeometrytest.cpp',
    'test/gramptest.cpp',
    'test/gsettest.cpp',
    'test/gvectortest.cpp',
    'test/gzippertest.cpp',
]

executable(
    'runtests',
    'test/runtests.cpp',
    test_sources,
    dependencies: [gtest_dep],
    include_directories: [test_includes, gbase_includes],
)
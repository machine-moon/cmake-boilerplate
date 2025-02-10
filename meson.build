#  [plain, debug, debugoptimized, release, minsize, custom] 

project('sysc', 'cpp', version : '0.1.0', license : 'MIT', default_options: [
            'cpp_std=c++23',
            'warning_level=3',
            'buildtype=release'
        ])



# Dependencies
gtkdep = dependency('gtk+-3.0')
gtest_dep = dependency('gtest', required: true)
gtest_main_dep = dependency('gtest_main', required: true)

# Executables
executable('program', 'src/main.cpp', dependencies: gtkdep)
test_exe = executable('MyTest', 'tests/test.cpp', dependencies: [gtest_dep, gtest_main_dep])

# Tests
test('MyTest', test_exe)
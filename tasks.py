#!/usr/bin/env python3


'''
TODO: Document.
'''


# Library Imports:
from invoke import task


# Standard Imports:
from enum import StrEnum
import multiprocessing


# Globals:
# Different build configurations:
class BuildMode(StrEnum):
    BUILD = 'build'
    DEBUG = 'debug-build'
    RELEASEDEBUG = 'reldebug-build'
    TEST = 'test-build'

# List of differnt
# BUILD_MODES = [BUILD, DEBUG, RELEASEDEBUG, TEST]


# Functions:
def cmake_parallel_arg(t_parallel: bool) -> str:
    '''
    Get the cmake arguments for building with multiple threads.
    '''
    arg = ''
    if t_parallel:
        max_jobs = multiprocessing.cpu_count() // 3
        arg = f'--parallel {max_jobs}'
        pass

    return arg

def cmake_build_args(t_mode: str) -> str:
    '''
    Get the cmake arguments for a specific build m
    '''
    args = ''
    match t_mode:
        case BuildMode.BUILD:
            ''

        case BuildMode.DEBUG:
            args += '-DCMAKE_BUILD_TYPE=Debug'

        case BuildMode.RELEASEDEBUG:
            args += '-DCMAKE_BUILD_TYPE=RelWithDebInfo'

        case BuildMode.TEST:
            args += '-DBUILD_CROW_TESTS=TRUE'

        case _:
            raise Exception(f'Unknown build configuration {t_mode}')
    pass

def cmake(c, t_mode: str, t_parallel: bool):
    ''' TODO: Document. '''
    parallel_arg = cmake_parallel_arg(t_parallel)
    build_args = cmake_build_args(t_mode)

    c.run(f'cmake -S . -B {t_mode}/ {build_args}')
    c.run(f'cmake --build {t_mode}/ {parallel_arg}')
    pass


# Tasks:
@task
def all(ctx):
    print('TODO: Implement.')
    pass

@task
def install(ctx):
    print('TODO: Implement.')
    pass

@task
def build(ctx, mode='', parallel=True):
    '''
    Build the compiler.
    '''
    enum_values = [ item.value for item in BuildMode ]
    mode = mode if mode in enum_values else 'build'
    cmake(ctx, mode, parallel)
    pass

@task
def clean(ctx, objects=False):
    '''
    Cleans the build files.
    '''
    for directory in BuildMode:
        path = directory
        path += '/CMakeFiles' if objects else ''
        path += '/*'

        print(f'Removing: {path}')
        ctx.run(f'rm -rf {path}/*')
        pass
    pass

@task
def format(ctx):
    '''
    Clang-format all Ctx++ sources and headers.
    '''
    ctx.run('find src/ -iname "*.[ch]pp" -exec clang-format -i {} \;')
    pass

@task
def header_guard(ctx):
    '''
    Regenerate all heade guards to be unique.
    '''
    ctx.run('PROJECT_NAME=CROW find src/ -name "*.hpp" -exec ./tools/header_guard.awk {} \;')
    pass

@task
def docs(ctx, pdf=False):
    '''
    Generate Doxygen documentation.
    '''
    ctx.run(f'doxygen .doxyfile')

    # TODO: Figure out if this is a good idea as we now depend on make.
    if pdf:
        ctx.run('cd doxygen/latex && make')
        pass
    pass


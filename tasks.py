#!/usr/bin/env python3


'''
TODO: Document.
'''


# Library Imports:
from invoke import task

# Standard Imports:
import json
import multiprocessing
from enum import StrEnum


# Globals:
class BuildMode(StrEnum):
    '''
    Enumeration containing the different build configurations.
    '''
    BUILD = 'build'
    DEBUG = 'debug-build'
    RELEASEDEBUG = 'reldebug-build'
    TEST = 'test-build'


# Functions:
def json_report(*args, **kwargs):
    if args:
        kwargs.update({'args': args})

    return json.dumps(kwargs)

#def run(t_context, t_cmd: str, **kwargs: Any) -> Optional[invoke.Result]:
def run(t_context, t_cmd: str, **kwargs):
    '''
    Helper method for colored output as a default.
    '''
    return t_context.run(t_cmd, pty=True)

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

def cmake_mode_args(t_mode: str) -> str:
    '''
    Get the cmake arguments for a specific build m
    '''
    args = ''
    match t_mode:
        case BuildMode.BUILD:
            pass

        case BuildMode.DEBUG:
            args += '-DCMAKE_BUILD_TYPE=Debug '
            pass

        case BuildMode.RELEASEDEBUG:
            args += '-DCMAKE_BUILD_TYPE=RelWithDebInfo '
            pass

        case BuildMode.TEST:
            args += '-DCMAKE_BUILD_TYPE=Debug '
            args += '-DCROW_BUILD_TESTS=TRUE '
            pass

        case _:
            raise Exception(f'Unknown build configuration {t_mode}')
    return args


def cmake(t_ctx, t_mode: str, t_parallel: bool, t_lint=False):
    ''' TODO: Document. '''
    parallel_arg = cmake_parallel_arg(t_parallel)
    build_args = cmake_mode_args(t_mode)

    # Perform static analysis if specified.
    if t_lint:
        build_args += '-DCROW_CLANG_TIDY=TRUE'

    run(t_ctx, f'cmake -S . -B {t_mode}/ {build_args}')
    run(t_ctx, f'cmake --build {t_mode}/ {parallel_arg}')
    pass


# Tasks:
@task
def all(ctx, parallel=True, lint=False):
    print(f'@Invoke: Args: {report}')

    report=json_report(parallel=parallel, lint=lint)
    print(f'@Invoke: Args: {report}')

    for mode in BuildMode:
        print(f'@Invoke: Building \'{mode}\'')
        build(ctx, mode, parallel)
        pass
    pass

@task
def install(ctx, parallel=True):
    print('TODO: Implement.')

    ctx.run();
    mode = mode if mode in enum_values else 'build'
    cmake(ctx, mode, parallel)
    pass

# TODO: Shorten help string, possibly use a global?
@task(help={'mode': '', 'parallel': 'Flag indicating concurrent builds.', 'lint': 'Perform static analysis on source code using clang-tidy'})
def build(ctx, mode='', parallel=True, lint=False):
    '''
    Build the project.
    '''
    print(f'@Invoke: Building project.')

    report=json_report(mode=mode, parallel=parallel, lint=lint)
    print(f'@Invoke: Args: {report}')

    enum_values = [ item.value for item in BuildMode ]
    mode = mode if mode in enum_values else 'build'
    cmake(ctx, mode, parallel, lint)
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

        print(f'@Invoke: Removing: {path}')
        ctx.run(f'rm -rf {path}/*')
        pass
    pass

@task
def format(ctx):
    '''
    Clang-format all Ctx++ sources and headers.
    '''
    ctx.run('find src/ -iname "*.[ch]pp" -exec clang-format -i "{}" \;')
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

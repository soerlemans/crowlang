#!/usr/bin/env python3


'''
TODO: Document.
'''


# Library Imports:
from invoke import task

# Standard Imports:
import sys
import json
import multiprocessing
from enum import StrEnum


# Globals:
class BuildMode(StrEnum):
    'Enumeration containing the different build configurations.'
    BUILD = 'build'
    DEBUG = 'debug-build'
    RELEASEDEBUG = 'reldebug-build'
    TEST = 'test-build'
    pass


# Functions:
def log(*args):
    'Log function makes it clear what messages come from Invoke.'
    print('@Invoke ', *args)
    pass


def log_args(*args, **kwargs):
    'Log the arguments passed to a task.'
    if args:
        kwargs.update({'args': args})

    log(json.dumps(kwargs))
    pass


#def run(t_context, t_cmd: str, **kwargs: Any) -> Optional[invoke.Result]:
def run(t_context, t_cmd: str, **kwargs):
    'Helper method for colored output as a default.'
    return t_context.run(t_cmd, pty=True)


def cmake_parallel_arg(t_parallel: bool) -> str:
    'Get the cmake arguments for building with multiple threads.'
    arg = ''
    if t_parallel:
        max_jobs = multiprocessing.cpu_count() // 3
        arg = f'--parallel {max_jobs}'
        pass

    return arg


def cmake_mode_args(t_mode: str) -> str:
    'Get the cmake arguments for a specific build mode.'
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
    'TODO: Document.'
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
def help(ctx):
    'Show a help string.'
    help_str = f'''Usage inv
    '''
    pass


@task
def all(ctx, parallel=True, lint=False):
    log('Building all.')
    log_args(parallel=parallel, lint=lint)

    for mode in BuildMode:
        print(f'@Invoke: Building \'{mode}\'')
        build(ctx, mode, parallel)
        pass
    pass


@task
def install(ctx, mode='', parallel=True, lint=False):
    log('Building project.')
    log_args(mode=mode, parallel=parallel, lint=lint)

    enum_values = [ item.value for item in BuildMode ]
    mode = mode if mode in enum_values else 'build'
    cmake(ctx, mode, parallel, lint)

    # TODO: Check if the build made it or not.
    # TODO: Copy transpiler from Mode install location to /usr/local/bin/

    print(f'\nGive password for installing to /usr/local/:')
    # Install binary to /usr/local/bin/
    ctx.run(f'sudo cp -f ./{mode}/crow /usr/local/bin/crow')

    # Install lbicrow headers.
    # TODO: Automate this.
    stdlibcrow_path = '/usr/local/include/stdlibcrow'
    ctx.run(f'sudo mkdir -p {stdlibcrow_path}')
    ctx.run(f'sudo cp -f ./src/stdlibcrow/*.hpp {stdlibcrow_path}')

    ctx.run(f'sudo mkdir -p {stdlibcrow_path}/internal')
    ctx.run(f'sudo cp -f ./src/stdlibcrow/internal/*.hpp {stdlibcrow_path}/internal')

    # TODO: Have CMake generate stdlibcrow.a.
    # TODO: Install shared stdlibcrow.a. 
    # ctx.run(f'sudo mkdir -p /usr/local/lib/crow/')
    #ctx.run(f'sudo cp -f ./{mode}/stdlibcrowlib.a /usr/local/lib/crow/')
    pass


def uninstall(ctx):
    '''Uninstall crow from /usr/local/'''
    ctx.run('sudo rm -f /usr/local/bin/crow')
    ctx.run('sudo rm -rf /usr/local/include/stdlibcrow')
    pass


# TODO: Shorten help string, possibly use a global?
@task(help={'mode': '', 'parallel': 'Flag indicating concurrent builds.', 'lint': 'Perform static analysis on source code using clang-tidy'})
def build(ctx, mode='', parallel=True, lint=False):
    'Build the project.'
    log('Building project.')
    log_args(mode=mode, parallel=parallel, lint=lint)

    enum_values = [ item.value for item in BuildMode ]
    mode = mode if mode in enum_values else 'build'
    cmake(ctx, mode, parallel, lint)
    pass


@task
def clean(ctx, objects=False):
    'Cleans the build files.'
    for directory in BuildMode:
        path = directory
        path += '/CMakeFiles' if objects else ''
        path += '/*'

        print(f'@Invoke: Removing: {path}')
        ctx.run(f'rm -rf {path}/*')
        pass

    # Remove any generated binaries.
    ctx.run(f'rm -rf *.out')
    pass


@task
def format(ctx):
    'Clang-format all Ctx++ sources and headers.'
    ctx.run(r'find src/ -iname "*.[ch]pp" -exec clang-format -i "{}" \;')
    pass


@task
def header_guard(ctx):
    'Regenerate all heade guards to be unique.'
    ctx.run(r'PROJECT_NAME=CROW find src/ -name "*.hpp" -exec ./tools/header_guard.awk {} \;')
    pass


@task(help={ 'pdf':'Generate PDF Doxygen output or not (requires make).' })
def docs(ctx, pdf=False):
    'Generate Doxygen documentation.'
    ctx.run(f'doxygen .doxyfile')

    if pdf:
        ctx.run('cd doxygen/latex && make')
        pass
    pass

@task
def setup(ctx):
    'Setup dependencies.'
    match sys.platform:
        case 'linux':
            ctx.run('bash tools/setup/setup.sh')
            pass

        case 'win32':
            print('Currently the setup script does not support Windows.')
            pass

        case 'darwin':
            print('Currently the setup script does not support MacOS.')
            pass

        case _:
            print(f'Unsupported platform: {sys.platform}')
            pass
    pass

#!/usr/bin/env python3


from invoke import task
import multiprocessing


BUILD_CONFIGURATIONS = ['build', 'debug-build', 'reldebug-build', 'test-build']


def cmake(c, t_dir, t_parallel):
    max_jobs = 1
    if t_parallel:
        # Only use a third of the cores by default.
        max_jobs = multiprocessing.cpu_count() // 3
        pass

    c.run(f'cmake -S . -B {t_dir}/')
    c.run(f'cmake --build {t_dir}/ --parallel {max_jobs}')
    pass


@task
def clean(c):
    #c.run(f'rm -rf {}')
    pass

@task
def build(c, parallel=True, mode=''):
    #cmake(c,)
    pass

@task
def clean(c, objects=False):
    '''
    TODO: Document this.
    '''

    for directory in BUILD_CONFIGURATIONS:
        path = directory
        path += '/CMakeFiles' if objects else ''
        path += '/*'

        print(f'Removing: {path}')
        c.run(f'rm -rf {path}/*')
        pass
    pass

@task
def format(c):
    c.run('find src/ -iname "*.[ch]pp" -exec clang-format -i {} \;')
    pass

@task
def header_guard(c):
    c.run('PROJECT_NAME=CROW find src/ -name "*.hpp" -exec ./tools/header_guard.awk {} \;')
    pass

@task
def docs(c, pdf=False):
    c.run(f'doxygen .doxyfile')

    # TODO: Figure out if this is a good idea as we now depend on make.
    if pdf:
        c.run('cd doxygen/latex && make')
        pass
    pass


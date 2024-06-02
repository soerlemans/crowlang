#!/usr/bin/env python3


from invoke import task
import multiprocessing



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
def build(c, parallel=False, mode=''):
    cmake()
    pass


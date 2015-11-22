
from distutils.core import setup

setup(
    name='LightSky OpenGL Extension Loader',
    description='A script which scans OpenGL header files and generates ' \
                'custom OpenGL extension loaders.',
    author='Miles Lacey',
    author_email='mileslacey@gmail.com',
    url='https://github.com/hamsham/LightSky-GL-Loader',
    packages=['lsgl'],
    package_data={
        'lsgl': ['templates/lsgl_template.c',
                 'templates/lsgl_template.h']
    }
)

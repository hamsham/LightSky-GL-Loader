
@ECHO OFF

cd tests

@ECHO Generating OpenGL extension loader sources from %1...
REM python ../glloader.py -i %1 -o ./
python ../glloader.py -i C:\MinGW\mingw64\x86_64-w64-mingw32\include\GL\gl.h -o ./
@ECHO Done.

@ECHO Compiling loader source files...
gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O3 -I./ -c lsgl.c -o lsgl.o
@ECHO Done.

@ECHO Creating loader debug and release libraries...
ar rcs liblsgl_d.a lsgl_d.o
ar rcs liblsgl.a lsgl.o
@ECHO Done.

@ECHO Compiling the OpenGL extension loader test..
gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g lsgl_test.c -o lsgl_test -L./ -llsgl_d -lSDL2main -lSDL2 -lopengl32
@ECHO Done.

@ECHO Running OpenGL extension loader test.
lsgl_test

cd ../

PAUSE

:quit

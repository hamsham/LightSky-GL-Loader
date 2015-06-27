
python glloader.py -i C:\MinGW\mingw64\x86_64-w64-mingw32\include\GL\gl.h -o ./build

cd build

gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g -c lsgl.c -o lsgl_d.o
gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O3 -I./ -c lsgl.c -o lsgl.o

ar rcs liblsgl_d.a lsgl_d.o
ar rcs liblsgl.a lsgl.o

gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O2 -I./ -g lsgl_test.c -o lsgl_test -L./ -llsgl_d -lSDL2main -lSDL2 -lopengl32

lsgl_test

cd ../

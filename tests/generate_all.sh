
set +euxo

echo "Generating OpenGL extension loader sources"
#python3 ../glloader.py -i "$1" -o ./
cd .. && python3 -m lsgl -i ./GL/glcorearb.h -o ./
echo "Done."

echo "Compiling loader source files..."
gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -Og -I../ -I./ -g -c lsgl.c -o lsgl_d.o
gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -O3 -I../ -I./ -c lsgl.c -o lsgl.o
echo "Done."

echo "Creating loader debug and release libraries..."
ar rcs liblsgl_d.a lsgl_d.o
ar rcs liblsgl.a lsgl.o
echo "Done."

echo "Compiling the OpenGL extension loader test.."
gcc --std=c99 -pedantic -pedantic-errors -Wall -Werror -Wextra -Og -I../ -I./ -g lsgl_test.c -o lsgl_test -L./ -llsgl_d -lSDL2main -lSDL2 -lGL
echo "Done."

echo "Running OpenGL extension loader test."
./lsgl_test

read -p "Press [Enter] to continue..."

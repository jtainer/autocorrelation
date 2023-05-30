gcc -o basic_example basic_example.c ../autocor.c ../fft/fft.c -lm
gcc -o raylib_example raylib_example.c ../autocor.c ../fft/fft.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -O3

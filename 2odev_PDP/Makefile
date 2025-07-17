all: compile run

compile:
	gcc -I ./include/ -o ./lib/Gezegen.o -c ./src/gezegen.c
	gcc -I ./include/ -o ./lib/BuzDeviGezegen.o -c ./src/buz_devi_gezegen.c
	gcc -I ./include/ -o ./lib/KayacGezegen.o -c ./src/kayac_gezegen.c
	gcc -I ./include/ -o ./lib/CuceGezegen.o -c ./src/cuce_gezegen.c
	gcc -I ./include/ -o ./lib/GazDeviGezegen.o -c ./src/gaz_devi_gezegen.c
	gcc -I ./include/ -o ./lib/UzayAraci.o -c ./src/uzay_araci.c
	gcc -I ./include/ -o ./lib/Kisi.o -c ./src/kisi.c
	gcc -I ./include/ -o ./lib/DosyaOkuma.o -c ./src/dosya_okuma.c
	gcc -I ./include/ -o ./lib/Zaman.o -c ./src/zaman.c
	gcc -I ./include/ -o ./lib/Simulasyon.o -c ./src/simulasyon.c
	gcc -I ./include/ -o ./bin/Main ./lib/Gezegen.o ./lib/BuzDeviGezegen.o ./lib/KayacGezegen.o ./lib/CuceGezegen.o ./lib/GazDeviGezegen.o ./lib/UzayAraci.o ./lib/Kisi.o ./lib/DosyaOkuma.o ./lib/Zaman.o ./lib/Simulasyon.o Main.c

run:
	./bin/Main

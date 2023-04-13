
#############################
# Generator plikow makefile #
# Krzysztof Siminski, 2022  #
#############################

# STALE:
kompilator=g++
standard=-std=c++20

optRelease=-O3
optDebug=

errors=-pedantic-errors

release=
debug=-g

#rownoleglosc=-fopenmp
rownoleglosc=

release_folder=_release
debug_folder=_debug

#############################

dane=../Test_files

.PHONY : clean $(debug_folder) $(release_folder)

# opcje uruchomienia projektu:

release : $(release_folder) $(release_folder)/main
	./$(release_folder)/main
	./$(release_folder)/main  -i $(dane)/test1.txt -o $(dane)/test2.txt -w $(dane)/test3.txt -k $(dane)/test4.txt
	./$(release_folder)/main  -i $(dane)/rot13.txt -o $(dane)/odszyfrowany.txt -w $(dane)/test3.txt -k $(dane)/klucz.txt
#	./$(release_folder)/main -i wejscie -o wyjscie -w wzorzec -k klucz
# Vinegrea -i test1 -o test2 -w test3 -k test4
#	./$(release_folder)/main -o wyjscie -w wzorzec -k klucz -i wejscie
# Vinegrea -o test2 -w test3 -k test4 -i test1
#niepoprawne:
#	./$(release_folder)/main -q wejscie -o wyjscie -w wzorzec -k klucz
#	./$(release_folder)/main -i wejscie -o wyjscie -w wzorzec 
#	./$(release_folder)/main -i wejscie -o wyjscie -w wzorzec -k klucz -w cos_jeszcze
#	./$(release_folder)/main -i wejscie -o wyjscie -w wzorzec klucz -k 

debug : $(debug_folder) $(debug_folder)/main
	valgrind --leak-check=yes ./$(debug_folder)/main

	./$(debug_folder)/main  -i $(dane)/test1.txt -o $(dane)/test2.txt -w $(dane)/test3.txt -k $(dane)/test4.txt
	./$(debug_folder)/main  -i $(dane)/szyfr.txt -o $(dane)/odszyfrowany.txt -w $(dane)/test3.txt -k $(dane)/klucz.txt
# utworzenie folderow:

$(release_folder) : 
	mkdir -p $(release_folder)
$(debug_folder) : 
	mkdir -p $(debug_folder)

# kompilacja zrodel:

$(release_folder)/function.o : function.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/function.o : function.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/main.o : main.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/main.o : main.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^

# linkowanie:

$(release_folder)/main : $(release_folder)/function.o $(release_folder)/main.o 
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -o $@ $^

$(debug_folder)/main : $(debug_folder)/function.o $(debug_folder)/main.o 
	$(kompilator) $(standard) $(debug) $(optDebug) $(rownoleglosc) $(errors) -o $@ $^

# usuniecie plikow skompilowanych:

clean : 
	if [ -d $(debug_folder)      ] ; then rm -r $(debug_folder)   ; fi
	if [ -d $(release_folder)    ] ; then rm -r $(release_folder) ; fi;



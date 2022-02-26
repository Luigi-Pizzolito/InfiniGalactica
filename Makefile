PNAME=Space_Invaders
SRCD=$(PNAME)/src/**/*
ODIR=bin/Darwin-Release-x86

CC=g++
IDIR =Dependencies/include
LDIR =Dependencies/lib-darwin
LIBS=-l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath $(LDIR)
CFLAGS=-std=c++14 -I $(IDIR)

run: $(ODIR)/$(PNAME)
	@echo "\033[0;34mRunning Project..........................\033[0m\033[2m"
	./$(ODIR)/*
	@echo "\033[0m\033[1;34mFinished.\033[0m"

$(ODIR)/$(PNAME): $(SRCD)
	@echo "\033[0m\033[0;32mBuilding Project..........................\033[0m\033[2m"
	$(CC) $^ -o $(ODIR)/$(PNAME) $(CFLAGS) $(LIBS)
	@echo "\033[0m\033[1;32mProject Compiled Successfully.\033[0m"

.PHONY: clean

clean:
	@echo "\033[0;33mCleaning Project..........................\033[0m\033[2m"
	rm -vf $(ODIR)/*
	@echo "\033[0m\033[0;33mCleaned Project.\033[0m\033[2m"
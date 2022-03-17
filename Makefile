PNAME=Space_Invaders
SRCD=$(PNAME)/src/**/*.cpp $(PNAME)/src/*.cpp
ODIR=bin/Darwin-Release-x86
ODIRL=bin/Linux-Release-x86

CC=g++
IDIR =Dependencies/include
LDIR =Dependencies/lib-darwin
LDIRL=Dependencies/lib-linux
LIBS=-l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath $(LDIR)
LIBSL=-Wl,--copy-dt-needed-entries -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network -Wl,-rpath $(LLDIR)
CFLAGS=-std=c++14 -I $(IDIR) -I $(PNAME)/src/
# add -g to add debug symbols, add -c to statically link, omit -o to generate .o files i think

# 2> /dev/null  silences stderr for annyong UpdateRecents: messages
run: $(ODIR)/$(PNAME)
	@echo "\033[0;34mRunning Project..........................\033[0m\033[2m\033[39;2m"
	cd Space_Invaders; ../$(ODIR)/$(PNAME) 2> /dev/null 
	@echo "\033[0m\033[1;34mFinished.\033[0m"

$(ODIR)/$(PNAME): $(SRCD)
	@[ -d $(ODIR) ] || mkdir -p $(ODIR)
	@echo "\033[0m\033[0;32mBuilding Project..........................\033[0m\033[2m"
	$(CC) $^ -o $(ODIR)/$(PNAME) $(CFLAGS) $(LIBS)
	@echo "\033[0m\033[1;32mProject Compiled Successfully.\033[0m"

.PHONY: clean

clean:
	@echo "\033[0;33mCleaning Project..........................\033[0m\033[2m"
	rm -vf $(ODIR)/*
	@echo "\033[0m\033[0;33mCleaned Project.\033[0m\033[2m"

linux:$(SRCD)
	@[ -d $(ODIRL) ] || mkdir -p $(ODIRL)
	@echo "\033[0m\033[0;32mBuilding Project..........................\033[0m\033[2m"
	$(CC) $^ -o $(ODIRL)/$(PNAME) $(CFLAGS) $(LIBSL)
	@echo "\033[0m\033[1;32mProject Compiled Successfully.\033[0m"

linux-run:
	@echo "\033[0;34mRunning Project..........................\033[0m\033[2m\033[39;2m"
	cd Space_Invaders; ../$(ODIRL)/$(PNAME) 2> /dev/null 
	@echo "\033[0m\033[1;34mFinished.\033[0m"
	
# novel:
# 	@[ -d $(ODIR) ] || mkdir -p $(ODIR)
# 	@echo "\033[0m\033[0;32mBuilding Novel Project..........................\033[0m\033[2m"	
# 	$(CC) Space_Invaders/src/Scenes/BasicTest.cpp Space_Invaders/src/Application/Application.cpp Space_Invaders/src/SceneManager/TextPanel.cpp Space_Invaders/src/SceneManager/TextManager.cpp Space_Invaders/src/SceneManager/MusicPlayer.cpp Space_Invaders/src/Application/BasicNovel.cpp -o $(ODIR)/$(PNAME)_Novel $(CFLAGS) $(LIBS)
# 	@echo "\033[0m\033[1;32mProject Compiled Successfully.\033[0m"
# 	@echo "\033[0;34mRunning Novel Project..........................\033[0m\033[2m"
# 	cd Space_Invaders; ../$(ODIR)/Space_Invaders_Novel
# 	@echo "\033[0m\033[1;34mFinished.\033[0m"

# music:
# 	@[ -d $(ODIR) ] || mkdir -p $(ODIR)
# 	@echo "\033[0m\033[0;32mBuilding Music Project..........................\033[0m\033[2m"	
# 	$(CC) Space_Invaders/src/Scenes/MusicTest.cpp -o $(ODIR)/$(PNAME)_Music $(CFLAGS) $(LIBS)
# 	@echo "\033[0m\033[1;32mProject Compiled Successfully.\033[0m"
# 	@echo "\033[0;34mRunning Music Project..........................\033[0m\033[2m"
# 	cd Space_Invaders; ../$(ODIR)/Space_Invaders_Music
# 	@echo "\033[0m\033[1;34mFinished.\033[0m"
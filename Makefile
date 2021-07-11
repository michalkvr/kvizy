NAME=kovarm36
SRC=src/source
H=include
CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long -O2
OBJFILES=main.o app.o basic.o global.o multichoice.o open.o quiz.o sequential.o singlechoice.o storagectrl.o uictrl.o
NCURSES=-lncurses

# LIBXML=`xml2-config --libs` `xml2-config --cflags`

# vygeneruj obj soubory
%.o : $(SRC)/%.cpp 
	$(CC) $(CFLAGS) -c $<

all: compile doc

# zkompiluj
compile: $(NAME)

# po zmene vygeneruj nove zavislosti
dep:
	$(CC) -MM *.cpp >dep.list

#generate documentation
doc:
	doxygen Doxyfile

# precti dependencies
-include dep.list

clean:
	@rm -rf $(NAME) *.o doc/

# slinkuj
$(NAME): $(OBJFILES)
	@$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME) $(NCURSES)
objects = Create.o Drop.o main.o Tokenizer.o Parser.o input.o utils.o \
		  Schema.o Load.o
CPPFLAGS = -std=c++17 -lstdc++fs -g


mydb.out: $(objects)
	g++ $(objects) -o mydb.out $(CPPFLAGS)

main.o:  Parser.h Tokenizer.h

Schema.o: Schema.h FileWriteBuffer.h

Tokenizer.o: Tokenizer.h utils.h

utils.o:  utils.h

Parser.o: Parser.h  Tokenizer.o Commands/Command.o

input.o: input.h 

Command.o: Commands/Command.h

Create.o: Commands/Create.h Commands/Create.cpp Commands/Command.h filesys.h
	g++ $(CPPFLAGS) -c Commands/Create.cpp

Drop.o: Commands/Drop.h Commands/Drop.cpp Commands/Command.h filesys.h
	g++ $(CPPFLAGS) -c Commands/Drop.cpp

Load.o: Commands/Load.h Commands/Load.cpp
	g++ $(CPPFLAGS) -c Commands/Load.cpp

clean:
	rm *.o
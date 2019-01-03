objects = Create.o main.o Tokenizer.o Parser.o input.o utils.o
CPPFLAGS = -std=c++17 -lstdc++fs


mydb.out: $(objects)
	g++ $(objects) -o mydb.out $(CPPFLAGS)

main.o:  Parser.h Tokenizer.h

Tokenizer.o: Tokenizer.h utils.h

utils.o:  utils.h

Parser.o: Parser.h  Tokenizer.h Commands/Command.h

input.o: input.h 

Create.o: Commands/Create.h Commands/Create.cpp Commands/Command.h filesys.h
	g++ -lstdc++fs $(CPPFLAGS) -c Commands/Create.cpp


clean:
	rm *.o
objects = Create.o Drop.o main.o Tokenizer.o Parser.o input.o utils.o \
		  Schema.o Load.o Command.o
CC = g++-8
CPPFLAGS = -std=c++17 -g
LDFLAGS = -lstdc++fs

mydb.out: $(objects)
	$(CC) $(CPPFLAGS) $(objects) -o $@ $(LDFLAGS)

main.o:  main.cpp Parser.h Tokenizer.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

Schema.o:  Schema.cpp Schema.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

Tokenizer.o:  Tokenizer.cpp Tokenizer.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

Parser.o:  Parser.cpp Parser.h Tokenizer.o
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

input.o:  input.cpp input.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

Command.o:  Commands/Command.cpp Commands/Command.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

Create.o:  Commands/Create.cpp Commands/Create.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

Drop.o:  Commands/Drop.cpp Commands/Drop.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

Load.o:  Commands/Load.cpp Commands/Load.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

utils.o:  utils.cpp utils.h
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)


clean:
	rm *.o

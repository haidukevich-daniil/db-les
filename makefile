all:
	gcc db_builder.c builder.c index.c -o db_builder
	gcc db_shell.c index.c -o db_shell

clean:
	del /Q *.exe *.o
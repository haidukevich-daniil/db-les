db_builder: db_builder.c builder.c index.c
	gcc db_builder.c builder.c index.c -o db_builder

db_shell: db_shell.c index.c
	gcc db_shell.c index.c -o db_shell

all: db_builder db_shell

clean:
	rm -f *.exe
	rm -f db_builder db_shell

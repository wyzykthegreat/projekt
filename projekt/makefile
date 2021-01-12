DEPS = main_curl.o

main: $(DEPS)
	cc $(DEPS) -o $@ -lcurl ../cJSON/cjson.o

%.o:%.c
	cc -c $^ -o $@

move:
	./main move
info:
	./main info
rotate-right:
	./main right
rotate-left:
	./main left
explore:
	./main explore
reset:
	./main reset

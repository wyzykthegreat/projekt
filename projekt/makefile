DEPS = main_curl.o

main: $(DEPS)
	cc $(DEPS) -o $@ -lcurl ../cJSON/cjson.o

%.o:%.c
	cc -c $^ -o $@

move:
	./main qwerty_2 move
info:
	./main qwerty_2 info
rotate-right:
	./main qwerty_2 right
rotate-left:
	./main qwerty_2 left
explore:
	./main qwerty_2 explore
reset:
	./main qwerty_2 reset

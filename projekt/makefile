DEPS = main_curl.o

main: $(DEPS)
	cc $(DEPS) -o $@ -lcurl ../cJSON/cjson.o

%.o:%.c
	cc -c $^ -o $@

test-move:
	./main move
test-info:
	./main info
test-rotate-right:
	./main right
test-rotate-left:
	./main left
test-explore:
	./main explore
reset:
	./main reset

DEPS = main.o komunikacja.o mapa.o dzejson.o

rumba: $(DEPS)
	cc $(DEPS) -o $@ -lcurl ../cJSON/cjson.o

%.o:%.c
	cc -c $^ -o $@

move:
	./rumba qwerty_2 move
info:
	./rumba qwerty_2 info
right:
	./rumba qwerty_2 right
left:
	./rumba qwerty_2 left
explore:
	./rumba qwerty_2 explore
reset:
	./rumba qwerty_2 reset
clean:
	rm -f rumba
	rm -f *.o
	rm -f dzejson.json
DEPS = main.o komunikacja.o mapa.o odpowiedz.o bot.o

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
start:
	./rumba qwerty_2 start
reset:
	./rumba qwerty_2 reset
clean:
	rm -f rumba
	rm -f *.o
	rm -f response.json
	rm -f save.txt

bot:
	./rumba qwerty_2 bot

test:
	./rumba qwerty_2 explore move explore move explore move left  explore move explore move explore move explore move explore move explore move right  explore move explore move right  explore move explore move explore move explore move explore move explore move explore left  explore move explore left  explore move explore move left  explore move right  explore move explore move right  explore move explore left  explore move explore move explore move explore left  explore move explore right  explore move explore move explore right  explore move left explore left move explore left  explore move  explore move  explore move explore right  explore move explore move explore right  explore move explore move explore move explore left  explore move explore move explore move left  explore move  explore move explore move explore move explore move explore move explore move explore move explore move explore move
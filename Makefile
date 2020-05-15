first: main.cpp
	g++ main.cpp -o app

.PHONY: clean
clean:
	rm -f app
AlchemyTogether:
	chmod 777 linux-SFML-2.6.1/lib/*
	g++ -o AlchemyTogether *.cpp -I linux-SFML-2.6.1/include -L linux-SFML-2.6.1/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

run:
	LD_LIBRARY_PATH=linux-SFML-2.6.1/lib ./AlchemyTogether

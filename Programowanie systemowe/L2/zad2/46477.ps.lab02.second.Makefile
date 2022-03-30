zad2: 46477.ps.lab02.second.lib.o 46477.ps.lab02.second.main.o
	gcc -o zad2 46477.ps.lab02.second.lib.o 46477.ps.lab02.second.main.o
46477.ps.lab02.second.lib.o: 46477.ps.lab02.second.lib.c
	gcc -c 46477.ps.lab02.second.lib.c
46477.ps.lab02.second.main.o: 46477.ps.lab02.second.main.c
	gcc -c 46477.ps.lab02.second.main.c


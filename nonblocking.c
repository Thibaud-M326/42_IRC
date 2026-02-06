#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

//ce code tente de faire passer errno sur EAGAIN, mais O_NONBLOCK ne fonctionne pas
//sur des fichiers simple
//ici file.txt possede 10 character
//on pourrais s'attendre a ce que le troisieme read bloque, ou ici grace a NONBLOCK
//set errno a EAGAIN, mais read_return est simplement passe a -1
//nous ne somme pas dans un cas ou la lecture peut etre bloquante
int main(void)
{
	int 	fd = open("./file.txt", O_RDONLY | O_NONBLOCK);	

	char 	buf[5];
	int 	read_return = 0;

	read_return = read(fd, buf, 5);
	read_return = read(fd, buf, 5);
	read_return = read(fd, buf, 5);

	if (errno == EAGAIN || errno == EWOULDBLOCK)
		printf("EAGAIN set\n");

	printf("%s", buf);

	return (0);
}

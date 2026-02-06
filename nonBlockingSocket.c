#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

//ici on teste le nonblock avec un socket
//errno sera bien defini lors du deuxieme appel a read
//
//bloquer la lecture d'un fichier sur le disque n'a pas de sens
//car on attend pas l'arrivee des donne, elle sont deja sur le disque
//
//avec une socket, les donne arrivent progressivement depuis le socket client
//vers le kernel, puis vers notre socket serveur
//
//Il n'y a pas de EOF tant que la connexion est ouverte
//bloquer fait sens puisqu'on attend la suite des donnee
//
//dans IRC, on ne veut pas bloquer, puisque on veut traiter plusieurs client
//on veut donc utiliser epoll pour nous notifier quand des nouvelles donnee
//a lire sont arrivee
int main(void)
{
    int sv[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, sv);
    
    fcntl(sv[0], F_SETFL, O_NONBLOCK);
    
    write(sv[1], "Hello", 5);
    
    char buf[10];
    int n;
    
    n = read(sv[0], buf, 10);  // Lit "Hello"
    printf("1er read: %d octets\n", n);
    
    n = read(sv[0], buf, 10);  // Socket vide → EAGAIN
    
    if (n == -1 && errno == EAGAIN)
        printf("✅ EAGAIN!\n");
    
    return 0;
}

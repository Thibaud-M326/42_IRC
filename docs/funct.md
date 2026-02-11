# Documentation Function **ft_irc**

## SOCKET

```c
int socket(int domain, int type, int protocol);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```

### Description :
La fonction **```socket()```** crée un **endpoint** de communication et retourne un **descripteur** de fichier représentant une **socket**.

> **```domain```** : **famille d’adresses** (ex: AF_INET, AF_INET6, AF_UNIX)

> **```type```** : **type de communication** (ex: SOCK_STREAM, SOCK_DGRAM)

> **```protocol```** : **protocole spécifique** (souvent 0 pour choisir le protocole par défaut du couple domain/type)

La **socket** créée n’est pas **connectée** et n’a pas **d’adresse locale** tant que **bind()** n’est pas appelée (sauf cas implicites).

### Valeur de retour :

> **```Succès```** : **descripteur de fichier** (≥ 0)

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EACCES```** **(13)** : **permission refusée** pour le **type** ou **protocole** demandé

>>> **```EAFNOSUPPORT```** **(97)** : **famille d’adresses non supporté**e

>>> **```EINVAL```** **(22)** : combinaison **domain/type/protocol invalide**

>>> **```EMFILE```** **(24)** : **trop** de **descripteurs ouverts** pour le **processus**

>>> **```ENFILE```** **(23)** : **limite système** de **fichiers ouverts atteinte**

>>> **```ENOBUFS```** **(105)** / **```ENOMEM```** (12) : **pas assez de mémoire**

>>> **```EPROTONOSUPPORT```** **(93)** : **protocole non supporté**

## CLOSE

```c
int close(int fd);
```

```c
#include <unistd.h>
```

### Description :
La fonction **```close()```** **ferme** un **descripteur de fichier**.

Si **```fd```** est une **socket**, la **connexion** est **libérée**

Si **plusieurs descripteurs référencent** la **même ressource**, la **ressource** n’est **réellement libérée** que **lorsque** le **dernier fd** est **fermé**

Après **```close()```**, le **descripteur** devient **réutilisable**

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EBADF```** **(9)** : **fd n’est pas** un **descripteur valide**

>>> **```EINTR```** (4) : **fermeture interrompue** par un **signal avant complétion**

>>> **```EIO```** (5) : **erreur d’entrée/sortie bas niveau**

## SETSOCKOPT

```c
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```

### Description :
La fonction **```setsockopt()```** permet de **configurer** le **comportement d’une socket.**

> **```level```** : niveau de l’option (SOL_SOCKET, IPPROTO_TCP, etc.)

> **```optname```** : option à modifier (SO_REUSEADDR, SO_KEEPALIVE, etc.)

> **```optval```** : pointeur vers la valeur de l’option

> **```optlen```** : taille de la valeur

Les **options** doivent être **définies** avant certaines **opérations**.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EBADF``` (9)** : **sockfd invalide**

>>> **```EINVAL``` (22)** : **option invalide** ou **optlen incorrect**

>>> **```ENOPROTOOPT``` (92)** : **option non supportée** pour ce niveau

>>> **```EFAULT``` (14)** : **optval pointe** vers une **adresse invalide**

>>> **```ENOMEM``` (12)** : **mémoire insuffisante**

## GETSOCKNAME

```c
int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```

### Description :
La fonction **```getsockname()```** permet d’obtenir **l’adresse locale** **associée** à une **socket**.

> **Cas typiques** :

>> Connaître le port attribué automatiquement après ```bind()``` avec port 0

>> Vérifier l’adresse locale utilisée après ```connect()```

>> **addrlen** doit contenir la **taille** du **buffer** en entrée et sera **mis à jour** avec la **taille réelle**.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EBADF```** (9) : **sockfd invalide**

>>> **```ENOTSOCK```** (88) : **sockfd n’est pas** une **socket**

>>> **```EFAULT```** (14) : **pointeur invalide** (addr ou addrlen)

>>> **```EINVAL```** (22) : **socket non liée** ou **état invalide**

## GETPROTOBYNAME

```c
struct protoent *getprotobyname(const char *name);
```

```c
#include <netdb.h>
```


### Description :
La fonction **```getprotobyname()```** **recherche un protocole réseau** par son **nom** (ex: "tcp", "udp"), généralement **via /etc/protocols** ou un **service de nommage réseau**.

Elle retourne une structure **```protoent```** contenant :

> **```p_name```** : **nom officiel du protocole**

> **```p_proto```** : **numéro du protocole** (ex: TCP = 6)

> **```p_aliases```** : **alias** éventuels

### Valeur de retour :

> **```Succès```** : **pointeur vers struct ```protoent```**

> **```Échec```** : **NULL**

⚠️ Fonction obsolète (non thread-safe), remplacée par **```getaddrinfo()```**.

## GETHOSTBYNAME

```c
struct hostent *gethostbyname(const char *name);
```

```c
#include <netdb.h>
```

### Description :
La fonction **```gethostbyname()```** résout un **nom d’hôte** (ex: "localhost", "example.com") en **adresses IP**.

La structure retournée **```hostent```** contient :

> **```h_name```** : **nom officiel**

> **```h_addr_list```** : **liste d’adresses IP**

⚠️ Fonction obsolète, non thread-safe, ne supporte pas IPv6.
Remplacée par **```getaddrinfo()```**.

### Valeur de retour :

> **```Succès```** : **pointeur vers struct ```hostent```**

> **```Échec```** : **NULL**

## GETADDRINFO

```c
int getaddrinfo(const char *node, const char *service,
	const struct addrinfo *hints, struct addrinfo **res);
```


```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
```


### Description :
La fonction **```getaddrinfo()```** **résout** un **nom d’hôte** et/ou un **service** en une **liste** de **structures addrinfo**, **compatibles IPv4/IPv6**.

> **```node```** : **hostname** ou **IP**

> **```service```** : **port** ou **nom de service**

> **```hints```** : **critères de filtrage**

> **```res```** : **résultat alloué dynamiquement**

Remplace **```gethostbyname()```** et **```getprotobyname()```**.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **code d’erreur spécifique (EAI_*)**

>> **```EAI_AGAIN```**

>> **```EAI_FAIL```**

>> **```EAI_NONAME```**

>> **```EAI_MEMORY```**

>> **```EAI_FAMILY```**

## FREEADDRINFO

```c
void freeaddrinfo(struct addrinfo *res);
```

```c
#include <netdb.h>
```


### Description :
Libère la mémoire allouée par **```getaddrinfo()```**.

⚠️ Doit être **appelée** une **seule fois** sur la **tête de la liste**.

### Valeur de retour :

## BIND

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```


### Description :
**```bind()```** **associe** une **adresse locale** (IP + port) à une **socket**.

### Valeur de retour :

> **```Succès```** : 0

> **```Échec```** : -1

>> **```errno```** :

>>> **```EADDRINUSE``` (98)** : **adresse déjà utilisée**

>>> **```EACCES``` (13)** : **port privilégié sans droits**

>>> **```EINVAL``` (22)** : **socket déjà liée**

>>> **```EBADF``` (9)** : **socket invalide**

>>> **```ENOTSOCK``` (88)** : **fd non-socket**

## CONNECT

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```

### Description :

**```connect()```** **établit** une **connexion** vers une **adresse distante**.

> **En TCP** : **établit la connexion**

> **En UDP** : **fixe la destination par défaut**

Peut être **bloquante** ou **non bloquante**.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```ECONNREFUSED``` (111)** : **serveur indisponible**

>>> **```ETIMEDOUT``` (110)** : **délai dépassé**

>>> **```EINPROGRESS``` (115)** : **socket non bloquante**

>>> **```ENETUNREACH``` (101)**: **serveur injoignable**

>>> **```EISCONN``` (106)**: **connexion abandonnee**

## LISTEN

```c
int listen(int sockfd, int backlog);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```


### Description :
**```listen()```** marque une **socket** comme **passive**, **prête à accepter** des **connexions entrantes**.

> **```backlog```** : **taille maximale de la file d’attente des connexions**

**Utilisable** uniquement sur **sockets SOCK_STREAM**.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```**:

>>> **```EINVAL``` (22)** : **socket non liée** ou **backlog invalide**

>>> **```ENOTSOCK``` (88)**

>>> **```EOPNOTSUPP``` (95)**

## ACCEPT

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```


### Description :
**```accept()```** **accepte** une **connexion entrante** sur une **socket en écoute** et **retourne** une **nouvelle socket connectée**.

**La socket d’origine reste en écoute**.

Le **nouveau fd** est **dédié** à la **communication** avec le **client**.

### Valeur de retour :

> **```Succès```** : **nouveau fd**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EAGAIN``` (11)** / ```EWOULDBLOCK``` **(140)** : **aucune connexion disponible**

>>> **```EINTR``` (4)** : **interrompu** par un **signal**

>>> **```EBADF``` (9)**

>>> **```ENOTSOCK``` (88)**

>>> **```ECONNABORTED``` (103)**

## HTONS

```c
uint16_t htons(uint16_t hostshort);
```

```c
#include <arpa/inet.h>
```


### Description :
**```htons()```** **convertit** un **entier non signé 16 bits** de l’endianness hôte vers le **network byte order** (big-endian).

> **Utilisé principalement pour les numéros de port**.

### Valeur de retour :

> **Valeur convertie en ordre réseau**

## HTONL

```c
uint32_t htonl(uint32_t hostlong);
```

```c
#include <arpa/inet.h>
```

### Description :
**```htonl()```** **convertit** un **entier non signé 32 bits** de l’endianness hôte vers le **network byte order**.

> **Utilisé pour les adresses IPv4**.

### Valeur de retour :

> **Valeur convertie en ordre réseau**

## NTOHS

```c
uint16_t ntohs(uint16_t netshort);
```

```c
#include <arpa/inet.h>
```

### Description :
**```ntohs()```** **convertit** un **entier 16 bits du network byte order** vers **l’endianness hôte**.

### Valeur de retour :

> **Valeur convertie en ordre réseau**

## NTOHL

```c
uint32_t ntohl(uint32_t netlong);
```

```c
#include <arpa/inet.h>
```

### Description :
**```ntohl()```** **convertit** un **entier 32 bits du network byte order** vers **l’endianness hôte**.

### Valeur de retour :

> **Valeur convertie en ordre réseau**

## INET_ADDR

```c
in_addr_t inet_addr(const char *cp);
```

```c
#include <arpa/inet.h>
```

### Description :
**```inet_addr()```** **convertit** une **adresse IPv4** sous forme **texte** ("192.168.1.1") en **adresse binaire** (ordre réseau).

⚠️ **Obsolète — remplacée par ```inet_ntop()```**.

### Valeur de retour :

> **```Succès```** : **adresse IPv4 en ordre réseau**

> **```Échec```** : **INADDR_NONE**

⚠️ **```INADDR_NONE```** peut aussi correspondre à **"255.255.255.255"**.

## INET_NTOA

```c
char *inet_ntoa(struct in_addr in);
```

```c
#include <arpa/inet.h>
```

### Description :
**```inet_ntoa()```** **convertit une adresse IPv4 binaire** en **chaîne ASCII** ("x.x.x.x").

> ⚠️ **Utilise** un **buffer statique interne** :

>> **non thread-safe**

>> **le contenu est écrasé à chaque appel**

### Valeur de retour :

> **Pointeur vers une chaîne statique**

## INET_NTOP

```c
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
```

```c
#include <arpa/inet.h>
```

### Description :
**```inet_ntop()```** **convertit** une **adresse IP binaire** vers **texte**, **supportant IPv4 et IPv6**.

> **```af```** : **AF_INET** ou **AF_INET6** (famille d'adresse)

> **```dst```** : **buffer fourni par l’appelant**

> **```size```** : **taille du buffer**

Remplace **```inet_ntoa()```**.

### Valeur de retour :

> **```Succès```** : **dst**

> **```Échec```** : **NULL**

>> **```errno```** :

>>> **```EINVAL``` (22)** : **famille d’adresses invalide**

>>> **```ENOSPC``` (28)** : **buffer trop petit**

## SEND

```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```

### Description :
**```send()```** **envoie** des **données** sur une **socket connectée**.

> ⚠️ Peut envoyer **moins de données que demandé**

**En UDP** : **envoie un datagramme**

### Valeur de retour :

> **```Succès```** : **nombre d’octets envoyés**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EPIPE``` (32)** : **socket fermée** côté distant

>>> **```ECONNRESET``` (104)**

>>> **```EAGAIN``` (11)** / **```EWOULDBLOCK``` (140)**

>>> **```EINTR``` (4)**

>>> **```ENOTSOCK``` (88)**

## RECV

```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

```c
#include <sys/types.h>
#include <sys/socket.h>
```

### Description :

**```recv()```** **lit** des **données** depuis une **socket**.

> ⚠️ Peut lire **moins de données que demandé**

Retourne 0 si la connexion TCP est fermée proprement

### Valeur de retour :

> **```Succès```** : **nombre d’octets envoyés**

>> **```Fermeture distante```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EAGAIN``` (11)** / **```EWOULDBLOCK``` (140)**

>>> **```EINTR``` (4)**

>>> **```ECONNRESET``` (104)**

>>> **```ENOTCONN``` (107)**

## SIGNAL

```c
void (*signal(int signum, void (*handler)(int)))(int);
```

```c
#include <signal.h>
```

### Description :
**```signal()```** **associe** un **handler** à un **signal**.

> ⚠️ Comportement **non portable** selon les **systèmes**.

**Remplacée par **```sigaction()```**.

### Valeur de retour :

> **```Succès```** : **ancien handler**

> **```Échec```** : **SIG_ERR**

>> **```errno```** :

>>> **```EINVAL``` (22)** : **signal invalide**

## SIGACTION

```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

```c
#include <signal.h>
```

### Description :
**```sigaction()```** **permet** une **gestion fiable** et fine des **signaux**.

> **Masquage de signaux**

> **Flags** (SA_RESTART, SA_SIGINFO, etc.)

> **Gestion déterministe**

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EINVAL``` (22)** : **signal invalide**

>>> **```EFAULT``` (14)** : **pointeur invalide**

## SIGEMPTYSET

```c
int sigemptyset(sigset_t *set);
```

```c
#include <signal.h>
```

### Description :
**```sigemptyset()```** **initialise** un **ensemble de signaux** (sigset_t) en le vidant complètement (aucun signal bloqué).

> Utilisée avant **```sigaddset()```**.

### Valeur de retour :

> **```Succès```** : 0

> **```Échec```** : -1

> **```errno```** (rare) :

> **```EINVAL``` (22)** : pointeur invalide (dépend de l’implémentation)

## SIGFILLSET 

```c
int sigfillset(sigset_t *set);
```

```c
#include <signal.h>
```

### Description :
**```sigfillset()```** **initialise** un **ensemble de signaux** en y ajoutant **tous** les **signaux définis**.

> ⚠️ **SIGKILL** et **SIGSTOP** ne peuvent **jamais être bloqués**, même s’ils figurent dans l’ensemble.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EINVAL``` (22)** : **pointeur invalide** (implémentation dépendante)

## SIGADDSET

```c
int sigaddset(sigset_t *set, int signum);
```

```c
#include <signal.h>
```

### Description :
**```sigaddset()```** **ajoute** un **signal spécifique** (signum) à un **ensemble de signaux**.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EINVAL``` (22)** : **signum invalide**

## SIGDELSET

```c
int sigdelset(sigset_t *set, int signum);
```

```c
#include <signal.h>
```

### Description :
**```sigdelset()```** **supprime un signal** (signum) d’un **ensemble de signaux**.

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

>> **```errno```** :

>>> **```EINVAL``` (22)** : **signum invalide**

## SIGISMEMBER

```c
int sigismember(const sigset_t *set, int signum);
```

```c
#include <signal.h>
```

### Description :
**```sigismember()```** **teste** si un **signal donné** est **présent** dans un **ensemble de signaux**.

### Valeur de retour :

> **```1```** : **signal présent**

> **```0```** : **signal absent**

> **```-1```** : **erreur**

>> **```errno```** (si retour = -1) :

>>> **```EINVAL``` (22)** : **```signum``` invalide**

## LSEEK

```c
off_t lseek(int fd, off_t offset, int whence);
```

```c
#include <unistd.h>
#include <sys/types.h>
```

### Description :
**```lseek()```** **modifie** la **position du curseur** de **fichier associé** à **fd**.

> **```fd```** : **descripteur de fichier**

> **```offset```** : **nombre d’octets à déplacer**

> **```whence```** : **point de référence pour l’offset**

>> **```SEEK_SET```** : **depuis le début**

>> **```SEEK_CUR```** : **depuis la position courante**

>> **```SEEK_END```** : **depuis la fin**

> ⚠️ **Impossible sur sockets**.

### Valeur de retour :

> **```Succès```** : nouvelle position (offset ≥ 0)

> **```Échec```** : -1

>> **```errno```** :

>>> **```ESPIPE``` (29)** : **fd non repositionnable**

>>> **```EBADF``` (9)**

>>> **```EINVAL``` (22)**

## FSTAT

```c
int fstat(int fd, struct stat *statbuf);
```

```c
#include <sys/stat.h>
#include <unistd.h>
```

### Description :
**```fstat()```** **récupère** les **métadonnées** d’un **fichier ouvert via** son **descripteur**.

> **Remplit** une structure **```stat```** :

>> **type de fichier**

>> **permissions**

>> **taille**

>> **timestamps**

### Valeur de retour :

> **```Succès```** : **0**

> **```Échec```** : **-1**

> **```errno```** :

> **```EBADF``` (9)**

> **```EFAULT``` (14)**

> **```EIO``` (5)**

FCNTL

```c
int fcntl(int fd, int cmd, ... /* arg */ );
```

```c
#include <fcntl.h>
#include <unistd.h>
```

**```fcntl()```** **permet** de **manipuler** les **descripteurs de fichiers**.

> Selon cmd, elle peut :

>> Obtenir ou modifier les flags du descripteur

>> Dupliquer un descripteur

>> Contrôler le comportement des fichiers ou sockets

### Usage courant

> **```F_GETFL```** : **retourne** les **flags actuels** (**```O_RDONLY```**, **```O_WRONLY```**, **```O_RDWR```**, **```O_NONBLOCK```**, **```O_APPEND```**, etc.)

> **```F_SETFL```** : **modifie les flags** (**```O_NONBLOCK```** ou **```O_APPEND```**)

>> ⚠️ Seuls certains flags peuvent être changés avec F_SETFL. Flags O_CREAT, O_EXCL etc. ne peuvent pas être modifiés après open().

> **```F_DUPFD```** : **renvoie** un **nouveau descripteur**, **partageant le même fichier**

> **```F_DUPFD_CLOEXEC```** : **même chose**, mais le **nouveau fd** sera **fermé automatiquement** lors d’un **```execve()```**

### Valeur de retour

> **```Succès```** (dépend du **```cmd```**) :

>> Pour **```F_GETFL```**, **```F_GETFD```** : retourne les flags

>> Pour **```F_SETFL```**, **```F_SETFD```**, **```F_DUPFD```** : **0 pour succès** (ou **fd pour duplication**)

> **```Erreur```** : -1

>> **```errno```**:

>>> **```EBADF``` (9)**

>>> **```EINVAL``` (22)**

>>> **```EMFILE``` (24)** : **pas assez** de **descripteurs libres** pour **```F_DUPFD```**

>>> **```EFAULT``` (14)**

## POLL

```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

```c
#include <poll.h>
```

### Description :

**```poll()```** **surveille** plusieurs **descripteurs** pour détecter des événements **d’E/S**.

> **```fds```** : **tableau de struct pollfd**

> **```nfds```** : **nombre d’éléments**

> **```timeout```** :

>> **```-1```** : **attente infinie**

>> **```0```** : **non bloquant**

>> **```> 0```** : **millisecondes**

### Valeur de retour :

> **```>0```** : **nombre de fd avec événements**

> **```0```** : **timeout**

> **```-1```** : **erreur**

>> **```errno```** :

>>> **```EINTR``` (4)** : )**interrompu par un signal)**

>>> **```EINVAL``` (22))** : )**paramètres invalides)**

>>> **```ENOMEM``` (12))**

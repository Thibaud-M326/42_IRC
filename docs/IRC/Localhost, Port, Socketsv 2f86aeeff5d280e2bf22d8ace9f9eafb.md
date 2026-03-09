# Localhost, Port, Socketsv

Localhost, Port, Socket

Localhost :

Lorsque on travaille en client-server, une ou plusieurs machines envoient des des requetes a un serveur central, qui envoi les reponse appropriees, c’est par exemple le cas d’un serveur web ou d’un serveur de base de donnee.

Lors de la phase de developpement d’un programme impliquant des echanges reseaux, il n’est pas necessaire de disposer de plusieurs machine physique ou virtuelle.

La meme machine peut heberger le serveur et un ou plusieurs client, dans les memes conditions, en passant par des ports

Toute machine disposant d’une pile TCP/IP peut s addresser a localhost, meme si cette machine n’est relie a aucun reseaux physique ou virtuel.

Il faut que le serveur approprie (par exemple un serveur web, un serveur IRC, ou un serveur de base de donnee) soit demarre sur un port prealablement convenu.

pour lister les port actif de votre machine : netstat -lntu

on peut tester la pile TCP/IP d’une machine avec la commande ping et une adresse IP local ou externe.

exemple : 

- ping localhost            :: 127.0.0.1
- ping 127.0.0.1           :: localhost
- ping 142.124.235.12 :: une machine connecte au reseaux internet

Port :

Dans la suite des protocole internet, correspondant a la couche transport du modele OSI, la notion de port logiciel permet, sur un ordinateur donne, de distinguer different interlocuteurs.

Ces interlocuteur sont des programmes qui ecoutent ou emettent sur ces ports. On distingue un port par son numero.

Grace a cette abstraction on peut executer plusieurs logiciel serveurs sur une meme machine. Et meme simultanement des logiciel clients et serveurs. 

Sans port on devrais avoir une machine par programme qui ecoute les requete venant de l’exterieur.

IP → quel ordinateur

Ports → quel programme

L’adresse IP sert à localiser une machine sur le réseau.

Le port sert à identifier quel service ou programme, écoutant en arrière-plan sur cette machine, doit recevoir les données.

Le programme serveur décide ensuite d’accepter ou non la requête et d’y répondre selon le protocole utilisé.

le terme port est parfois utilise pour definir les sockets (interface de connexion). Un concept sensilblement different.

Le socket sert d’identifiant unique dans un reseaux donne resultant de la concatenation de l’addresse internet et du numero de port, le port sert localement a identifier le processus vise par une requette.

Une machine possede 65536 ports distincts. Ces ports sont classe en 3 categorie en fonction de leur numero : 

0 - 1023         :: ports connu (well know ports), utilise par les services reseaux les plus courants.

1024 - 49151   :: ports enregistre (registered ports), assignes par l’IANA

49152 - 65535 :: ports dynamique, utilisables pour tout type de requetes tcp ou udp autre 

Lorsque un logiciel client veut se connecter avec un logiciel serveur ( aussi appele service) il a besoin de connaitre le port ecoute par ce dernier. 

liste non exaustive des Well-know-Service : 

- 20/21, pour l'échange de fichiers via [FTP](https://fr.wikipedia.org/wiki/File_Transfer_Protocol)
- 25, pour l'envoi d'un [courrier électronique](https://fr.wikipedia.org/wiki/Courrier_%C3%A9lectronique) via un serveur dédié [SMTP](https://fr.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol)
- 53, pour la resolution de noms de domaine IP : DNS
- 80 pour la consultation d’un serveur HTTP
- 443, pour les connexions HTTP utilisant une surcouche de sécurité de type SSL : HTTPS
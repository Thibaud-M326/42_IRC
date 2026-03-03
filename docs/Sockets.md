# Les Sockets

> Les sockets sont utilisées pour la communication inter-processus (IPC).

Dans le cadre d’une **communication** **client–serveur**, les **```sockets```** servent de **point de terminaison** pour **l’échange de données**.

Ce sont des **descripteurs de fichiers** (file descriptors, fd) créés via **l’appel système** :

## ```socket()```

### Côté serveur

#### Le serveur :

- Crée une socket.

- La **bind** (associe) à une **adresse connue** (IP + port).

- **Attend** les **connexions** des **clients** sur cette **adresse**.

- Cela **permet** aux clients de **savoir** où se **connecter**.

#### Types de sockets

##### Stream (```SOCK_STREAM```)

- **Transmission fiable** des données.

- **Communication bidirectionnelle**.

- **Garantie** de :

	> **L’ordre des messages**.

	> **L’intégrité des données**.

	> **La non-duplication**.

	> Fonctionne de **manière similaire** à un **```pipe```**, mais via le **réseau**.

- Protocole associé : **```TCP```**

- Exemples d’usage :

	> **Messageries**

	> **```HTTP``` / ```HTTPS```**

	> **```SSH```**

	> **```FTP```**

##### Datagram (```SOCK_DGRAM```)

- Les limites des messages sont préservées.

- Transmission non fiable :

	> Perte de paquets possible.

	> Désordre possible.

	> Duplication possible.

	> Aucune garantie de livraison.

- Protocole associé : **```UDP```**

- Exemples d’usage :

> **Streaming** **audio**/**vidéo**

> **Jeux en ligne**

> **DNS**

> 👉 **Adapté** quand la **latence prime** sur la **fiabilité**.

# Analogie : le téléphone

## 1. Création de la socket

> L’appel système `socket()` est l’équivalent de l’installation d’un téléphone.

Pour que deux applications communiquent, chacune doit créer sa propre socket.

---

## 2. Établissement d’une connexion (Stream socket)

La communication via une socket **stream** est analogue à un appel téléphonique.

Avant de communiquer, une application doit se connecter à la socket de l’autre.

### a) Côté serveur

1. L’application appelle `bind()` pour associer la socket à une adresse connue.  
2. Puis appelle `listen()` pour indiquer au noyau qu’elle accepte des connexions entrantes.  

**Analogie :**
- Avoir un numéro de téléphone connu.  
- Laisser son téléphone allumé pour recevoir des appels.

---

### b) Côté client

L’application cliente appelle :

```c
connect()
```

en spécifiant l’adresse de la socket serveur.

**Analogie :**
- Composer le numéro de téléphone de quelqu’un.

---

### c) Acceptation de la connexion

Le serveur appelle :

```c
accept()
```

pour accepter la connexion entrante.

**Analogie :**
- Décrocher le téléphone quand il sonne.

Si `accept()` est appelé avant `connect()`, l’appel est **bloquant** :  
le serveur “attend près du téléphone”.

---

## 3. Communication des données

Une fois la connexion établie :

- Les données peuvent circuler **dans les deux sens**.  
- Comme une conversation téléphonique bidirectionnelle.

La communication se fait via :

```c
read()
write()
```

ou des appels spécifiques aux sockets :

```c
send()
recv()
```

Ces derniers offrent des fonctionnalités supplémentaires (flags, gestion fine des envois, etc.).

---

# Cycle classique d’une socket TCP

## Serveur

```text
socket()
bind()
listen()
accept()
read()/write()
close()
```

Two common designs for network servers using sockets are the following:

- Iterative: The server handles one client at a time, processing that client’s
request(s) completely, before proceeding to the next client.

- Concurrent: The server is designed to handle multiple clients simultaneously.

## Client

```text
socket()
connect()
read()/write()
close()
```

---

# Compléments utiles

### Familles d’adresses courantes

- `AF_INET` → IPv4  
- `AF_INET6` → IPv6  
- `AF_UNIX` → Communication locale (fichiers sockets)  

---

### Ports

- 0–1023 → Ports bien connus (HTTP 80, HTTPS 443…)  
- 1024–49151 → Ports enregistrés  
- 49152–65535 → Ports dynamiques / éphémères

---

### Points clés à retenir

- Une socket = point de communication réseau.  
- Identifiée par : **IP + Port + Protocole**.  
- TCP = fiable mais plus lent.  
- UDP = rapide mais non fiable.  
- Les sockets sont manipulées comme des fichiers (fd).  

![[Linux/Sockets/Assets/Screenshot from 2026-02-05 19-28-58.png]]


![[Screenshot from 2026-02-05 19-31-53.png]]

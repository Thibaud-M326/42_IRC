---
id: RFC 2812 notes
aliases: []
tags: []
---
# Serveur IRC (RFC 2812)

## Membres

### Server
- Nom maximal : 63 caractères.

### Clients
- Identifiant unique sur le réseau.

### Users
- Nickname de 9 caractères maximum.

### Operators
- Un opérateur est un user possédant davantage de droits sur un channel qu’un user standard.

### Channel
- Le nom d’un channel est une chaîne de caractères de 50 caractères maximum commençant obligatoirement par l’un des caractères suivants :
  - `'&'`
  - `'#'`
  - `'+'`
  - `'!'`

- La chaîne ne peut pas contenir les caractères suivants :
  - Espace (`' '`)
  - `'^G'` (Control‑G / BELL)
  - `','` (virgule)

---

## Protocole des messages

### Côté client

Cette section définit les messages que le client envoie au serveur.

---

#### Règles générales

- Un message ne peut pas dépasser **512 caractères**, CRLF inclus.
  - Si un client envoie un message (sans préfixe) proche de cette limite et que le serveur ajoute un préfixe dépassant 512 caractères, le message devient invalide et doit être rejeté.

- Les messages vides sont ignorés.

- Le caractère **NUL** n’est pas autorisé.

- `CRLF` (`\r\n`) indique la fin d’un message.

---

#### Parsing des messages

Les messages sont analysés en 3 composants :

1. **Prefix**  
   Fournit des informations sur l’expéditeur (serveur ou utilisateur).

2. **Command**  
   Indique l’action à exécuter.

3. **Parameters**  
   Maximum 15 paramètres :
   - 14 `middle`
   - 1 `trailing`

---

### Middle vs Trailing

#### Middle parameters
Paramètres “techniques” (ex : nom de channel, modes…).  
Ils ne peuvent pas contenir :

- NUL (`%x00`)
- CR (`%x0D` / `\r`)
- LF (`%x0A` / `\n`)
- Espace (`%x20`)
- `:` (`%x3A`)

#### Trailing parameter
Permet d’inclure des espaces dans le dernier paramètre.

Il est optionnel s’il n’y a pas d’espace.

##### Exemple avec trailing
```ruby
PRIVMSG #42 :Bonjour à tous\r\n
```

##### Exemple sans trailing
```ruby
PRIVMSG #42 Bonjour\r\n
```

---

## Préfixe côté client

Lors d’une communication **client → serveur** :

- Le client ne doit **pas** envoyer de préfixe.
- Si c’est le cas, le serveur doit :
  - Ignorer le message, ou
  - Renvoyer une erreur de non‑conformité au protocole.

---

## Exemples de messages

### Avec préfixe
```ruby
:nick!user@host PRIVMSG #42 :Bonjour à tous\r\n
```

| Partie  | Valeur |
|--------|--------|
| Prefix | nick!user@host |
| Command | PRIVMSG |
| Param 1 | #42 |
| Param 2 | (trailing) Bonjour à tous |

---

### Sans préfixe
```ruby
PRIVMSG #42 :Bonjour à tous\r\n
```

| Partie  | Valeur |
|--------|--------|
| Command | PRIVMSG |
| Param 1 | #42 |
| Param 2 | (trailing) Bonjour à tous |## Commande a implementer:


## Glossaire

### Décomposition d’un message

```ruby
message    =  [ ":" prefix SPACE ] command [ params ] crlf

prefix     =  servername / ( nickname [ [ "!" user ] "@" host ] )

command    =  1*letter / 3digit ; au moins une lettre ou 3 chiffres

params     =  *14( SPACE middle ) [ SPACE ":" trailing ]
           =/ 14( SPACE middle ) [ SPACE [ ":" ] trailing ]

nospcrlfcl =  %x01-09 / %x0B-0C / %x0E-1F / %x21-39 / %x3B-FF
               ; tout octet sauf NUL, CR, LF, " " et ":"

middle     =  nospcrlfcl *( ":" / nospcrlfcl )

trailing   =  *( ":" / " " / nospcrlfcl )

SPACE      =  %x20        ; espace

crlf       =  %x0D %x0A   ; carriage return + linefeed
```

---

### Liste des cibles

```ruby
target     =  nickname / server
msgtarget  =  msgto *( "," msgto )
msgto      =  channel / ( user [ "%" host ] "@" servername )
msgto      =/ ( user "%" host ) / targetmask
msgto      =/ nickname / ( nickname "!" user "@" host )

channel    =  ( "#" / "+" / ( "!" channelid ) / "&" ) chanstring
              [ ":" chanstring ]

servername =  hostname
host       =  hostname / hostaddr

hostname   =  shortname *( "." shortname )
shortname  =  ( letter / digit ) *( letter / digit / "-" )
              *( letter / digit )

hostaddr   =  ip4addr / ip6addr
ip4addr    =  1*3digit "." 1*3digit "." 1*3digit "." 1*3digit
ip6addr    =  1*hexdigit 7( ":" 1*hexdigit )
ip6addr    =/ "0:0:0:0:0:" ( "0" / "FFFF" ) ":" ip4addr

nickname   =  ( letter / special ) *8( letter / digit / special / "-" )

targetmask =  ( "$" / "#" ) mask

chanstring =  %x01-07 / %x08-09 / %x0B-0C / %x0E-1F / %x21-2B
chanstring =/ %x2D-39 / %x3B-FF

channelid  = 5( %x41-5A / digit )

user       =  1*( %x01-09 / %x0B-0C / %x0E-1F / %x21-3F / %x41-FF )

key        =  1*23( %x01-05 / %x07-08 / %x0C / %x0E-1F / %x21-7F )

letter     =  %x41-5A / %x61-7A
digit      =  %x30-39
hexdigit   =  digit / "A" / "B" / "C" / "D" / "E" / "F"
special    =  %x5B-60 / %x7B-7D
```

Pour la traduction complète des caractères hexadécimaux, voir : [ASCII table](https://www.ascii-code.com/fr)

---

## Commande

### Obligatoire

- PRIVMSG - Send private messages between users
   The \<msgtarget> parameter may also be a host mask (#\<mask>) or server
   mask (\$\<mask>).  In both cases the server will only send the PRIVMSG
   to those who have a server or host matching the mask.  The mask MUST
   have at least 1 (one) "." in it and no wildcards following the last
   ".".  This requirement exists to prevent people sending messages to
   "#*" or "$*", which would broadcast to all users.  Wildcards are the
   '*' and '?'  characters.  This extension to the PRIVMSG command is
   only available to operators.

```ruby
Parameters: <msgtarget> <text to be sent>

   Numeric Replies:

           ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
           ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
           ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
           ERR_NOSUCHNICK
           RPL_AWAY
```

---

- KICK - Eject a client from the channel
   For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, or as many
   channel parameters as there are user parameters.  If a "comment" is
   given, this will be sent instead of the default message, the nickname
   of the user issuing the KICK.
   The server MUST NOT send KICK messages with multiple channels or
   users to clients.  This is necessarily to maintain backward
   compatibility with old client software.

```ruby
Parameters: <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
```

Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
           ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL

---

- INVITE - Invite a client to a channel
   The INVITE command is used to invite a user to a channel.  The
   parameter \<nickname> is the nickname of the person to be invited to
   the target channel \<channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  However, if the channel exists, only members of the channel
   are allowed to invite other users.  When the channel has invite-only
   flag set, only channel operators may issue INVITE command.
   Only the user inviting and the user being invited will receive
   notification of the invitation.  Other channel members are not
   notified.  (This is unlike the MODE changes, and is occasionally the
   source of trouble for users.)

```ruby
Parameters: <nickname> <channel>
```

Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_USERONCHANNEL
           ERR_CHANOPRIVSNEEDED
		   RPL_INVITING                    RPL_AWAY

---

- TOPIC - Change or view the channel topic
	The TOPIC command is used to change or view the topic of a channel.
	The topic for channel \<channel> is returned if there is no \<topic>
	given.  If the \<topic> parameter is present, the topic for that
	channel will be changed, if this action is allowed for the user
   	requesting it.  If the \<topic> parameter is an empty string, the
   	topic for that channel will be removed.

```ruby
Parameters: <channel> [ <topic> ]
```

- Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
           RPL_NOTOPIC                     RPL_TOPIC
           ERR_CHANOPRIVSNEEDED            ERR_NOCHANMODES

---

#### Userside:
   
##### Mode a implementer:

- i: Set/remove Invite-only channel
- t: Set/remove the restrictions of the TOPIC command to channel operators
- k: Set/remove the channel key (password)
- o: Give/take channel operator privilege
- l: Set/remove the user limit to channel

---

- MODE - Change the user's mode:
	A user MODE command MUST only be accepted if both the sender of the
	message and the nickname given as a parameter are both the same.  If
	no other parameter is given, then the server will return the current
	settings for the nick.

```ruby
Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
```

- Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
           ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS

#### Channelside:

- MODE - Change the channel's mode:
	Users may query and change the characteristics of a channel.

```ruby
Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
```

- Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_KEYSET
           ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
           ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
           RPL_CHANNELMODEIS
           RPL_BANLIST                     RPL_ENDOFBANLIST
           RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
           RPL_INVITELIST                  RPL_ENDOFINVITELIST
           RPL_UNIQOPIS

---

- NICK - Give user a nickname or change the existing one.

```ruby
Parameters: <nickname>
```

- Numeric Replies:

          ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
          ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
          ERR_UNAVAILRESOURCE             ERR_RESTRICTED
---
- JOIN - Used by a user to request to start listening to the specific channel. Note that this message accepts a special argument ("0"), which is a special request to leave all channels the user is currently a member of.

```ruby
Parameters: ( \<channel> *( "," \<channel> ) [ \<key> *( "," \<key> ) ] )
               / "0"
```

- Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
           ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
		   RPL_TOPIC

### Optionnel:
- OPER - Obtain operator privileges.
   The combination of \<name> and \<password> are REQUIRED to gain
   Operator privileges.  Upon success, the user will receive a MODE
   message (see section 3.1.5) indicating the new user modes.

```ruby
Parameters: \<name> \<password>
```

- Numeric Replies:

           ERR_NEEDMOREPARAMS              RPL_YOUREOPER
           ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

---

- LIST - list channels and their topics. If the \<channel> parameter is used, only the status of that channel is displayed.

```ruby
Paramters: [ <channel> *( "," <channel> ) [ <target> ] ]
```

- Numeric Replies:

           ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
           RPL_LIST                        RPL_LISTEND


## Codes de réponses IRC (RFC 2812)

Cette section liste les principaux codes de réponses retournés par un serveur IRC, avec leur signification et leur contexte d’utilisation.

---

### 001 — RPL_WELCOME
`"Bienvenue sur le relais de causette Internet <pseudonyme>!<utilisateur>@<hôte>"`

---

### 301 — RPL_AWAY
`"<pseudonyme> :<message away>"`

---

### 341 — RPL_INVITING
`"<pseudonyme> <canal>"`

- Retourné par le serveur pour indiquer que le message `INVITE` tenté a réussi et est passé vers le client final.

---

### 331 — RPL_NOTOPIC
`"<canal> :Aucun sujet n’est établi"`

### 332 — RPL_TOPIC
`"<canal> :<sujet>"`

- Lors de l’envoi d’un message `TOPIC` pour déterminer le sujet d’un canal, une des deux réponses est envoyée.  
  - Si le sujet est établi → `RPL_TOPIC` est renvoyé.  
  - Sinon → `RPL_NOTOPIC`.

---

### 221 — RPL_UMODEIS
`"<chaîne de mode d’utilisateur>"`

- Pour répondre à une interrogation sur le mode du client, `RPL_UMODEIS` est renvoyé.

---

### 324 — RPL_CHANNELMODEIS
`"<canal> <mode> <mode params>"`

---

### 367 — RPL_BANLIST
`"<canal> <gabarit d’interdiction>"`

---

### 348 — RPL_EXCEPTLIST
`"<canal> <gabarit d’exception>"`

### 349 — RPL_ENDOFEXCEPTLIST
`"<canal> :Fin de liste d’exception de canal"`

- Lorsque le serveur liste les **gabarits d’exception** pour un canal :  
  - Il DOIT envoyer des messages `RPL_EXCEPTLIST` (un par gabarit actif).  
  - Puis un message `RPL_ENDOFEXCEPTLIST` DOIT être envoyé pour marquer la fin.

---

### 346 — RPL_INVITELIST
`"<canal> <gabarit d’invite>"`

### 347 — RPL_ENDOFINVITELIST
`"<canal> :Fin de liste d’invite de canal"`

- Lorsque le serveur liste les **gabarits d’invitation** pour un canal :  
  - Il DOIT envoyer des messages `RPL_INVITELIST` (un par gabarit actif).  
  - Après établissement de la liste (ou s’il n’y en a aucun),  
    `RPL_ENDOFINVITELIST` DOIT être envoyé.

---

### 325 — RPL_UNIQOPIS
`"<canal> <pseudonyme>"`

---

### 332 — RPL_TOPIC
`"<canal> :<sujet>"`

- Lors de l’envoi d’un message `TOPIC` pour déterminer le sujet d’un canal, une des deux réponses est envoyée :  
  - Si le sujet est établi → `RPL_TOPIC`.  
  - Sinon → `RPL_NOTOPIC`.

---

### 381 — RPL_YOUREOPER
`":Vous êtes maintenant un opérateur IRC"`

- Renvoyé à un client ayant réussi une commande `OPER` et obtenu le statut d’opérateur.

---

### 322 — RPL_LIST
`"<canal> <# visible> :<sujet>"`

### 323 — RPL_LISTEND
`":Fin de LIST"`

- Les réponses `RPL_LIST` et `RPL_LISTEND` constituent la réponse du serveur à une commande `LIST`.  
- S’il n’y a aucun canal à retourner, seule la fin de réponse DOIT être envoyée.


---

## Codes d’erreurs IRC (RFC 2812)

Cette section liste les principaux codes d’erreurs retournés par un serveur IRC, avec leur signification et leur contexte d’utilisation.

---

### Erreurs liées aux pseudonymes et canaux

#### 401 — ERR_NOSUCHNICK
`<pseudonyme> :Pas de tel pseudonyme/canal`

Utilisé pour indiquer que le pseudonyme fourni en paramètre d’une commande n’existe pas actuellement.

---

#### 403 — ERR_NOSUCHCHANNEL
`<nom de canal> :Pas de tel canal`

Indique que le nom de canal fourni est invalide ou inexistant.

---

#### 405 — ERR_TOOMANYCHANNELS
`<nom de canal> :Vous avez rejoint trop de canaux`

Envoyé lorsqu’un utilisateur a atteint le nombre maximum de canaux autorisés et tente d’en rejoindre un supplémentaire.

---

### Erreurs liées aux messages

#### 411 — ERR_NORECIPIENT
`:Pas de destinataire donné (<commande>)`

Indique qu’aucun destinataire n’a été spécifié pour la commande.

---

#### 412 — ERR_NOTEXTTOSEND
`:Pas de texte à envoyer`

Retourne cette erreur lorsqu’un message ne contient aucun texte.

---

### Erreurs de commande

#### 421 — ERR_UNKNOWNCOMMAND
`<commande> :Commande inconnue`

Retourné à un client enregistré lorsque la commande envoyée n’est pas reconnue par le serveur.

---

#### 461 — ERR_NEEDMOREPARAMS
`<commande> :Pas assez de paramètres`

Indique que la commande envoyée ne contient pas suffisamment de paramètres.

---

#### 462 — ERR_ALREADYREGISTERED
`:Commande non autorisée (déjà enregistré)`

Retourné lorsqu’un client tente de modifier des informations d’enregistrement après validation (ex : second message USER, mot de passe…).

---

#### 464 — ERR_PASSWDMISMATCH
`:Mot de passe incorrect`

Indique un échec d’authentification dû à un mot de passe absent ou invalide.

---

### Erreurs liées aux pseudonymes

#### 431 — ERR_NONICKNAMEGIVEN
`:Aucun pseudonyme donné`

Retourné lorsqu’un pseudonyme est attendu mais non fourni.

---

#### 432 — ERR_ERRONEUSNICKNAME
`<pseudonyme> :Pseudonyme erroné`

Retourné lorsqu’un message NICK contient des caractères invalides (voir RFC 2812 — section sur les pseudonymes valides).

---

#### 433 — ERR_NICKNAMEINUSE
`<pseudonyme> :Pseudonyme déjà utilisé`

Indique qu’un changement de pseudonyme échoue car celui-ci est déjà utilisé.

---

### Erreurs liées à la présence sur un canal

#### 441 — ERR_USERNOTINCHANNEL
`<pseudonyme> <canal> :Ils ne sont pas sur ce canal`

Indique que l’utilisateur ciblé n’est pas présent sur le canal spécifié.

---

#### 442 — ERR_NOTONCHANNEL
`<canal> :Vous n’êtes pas sur ce canal`

Retourné lorsqu’un client tente une action sur un canal dont il n’est pas membre.

---

#### 443 — ERR_USERONCHANNEL
`<utilisateur> <canal> :Est déjà sur le canal`

Envoyé lorsqu’un utilisateur est invité sur un canal où il est déjà présent.

---

### Erreurs liées aux modes et accès des canaux

#### 467 — ERR_KEYSET
`<canal> :Clé de canal déjà définie`

---

#### 471 — ERR_CHANNELISFULL
`<canal> :Le canal est plein (+l)`

---

#### 472 — ERR_UNKNOWNMODE
`<char> :Caractère de mode inconnu pour <canal>`

---

#### 473 — ERR_INVITEONLYCHAN
`<canal> :Le canal est sur invitation uniquement (+i)`

---

#### 474 — ERR_BANNEDFROMCHAN
`<canal> :Vous êtes banni de ce canal (+b)`

---

#### 475 — ERR_BADCHANNELKEY
`<canal> :Clé de canal incorrecte (+k)`

---

#### 476 — ERR_BADCHANMASK
`<canal> :Masque de canal invalide`

---

#### 477 — ERR_NOCHANMODES
`<canal> :Ce canal n’accepte pas ces modes`

---

#### 478 — ERR_BANLISTFULL
`<canal> <char> :La liste de bannissement est pleine`

---

### Erreurs de privilèges

#### 482 — ERR_CHANOPRIVSNEEDED
`<canal> :Vous n’êtes pas opérateur du canal`

Toute commande nécessitant les privilèges opérateur (ex : MODE) doit retourner cette erreur si l’utilisateur ne possède pas les droits requis.

---

### Erreurs de modes utilisateur

#### 501 — ERR_UMODEUNKNOWNFLAG
`:Fanion MODE inconnu`

Indique qu’un flag de mode utilisateur envoyé via la commande MODE n’est pas reconnu par le serveur.

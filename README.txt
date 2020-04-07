Ce logiciel a été dévellopé par Rémi Pérenne et est sous license GNU GENERAL PUBLIC LICENSE, vous en trouverez une copie dans ce dossier le nom du fichier est "COPYING.txt".

Vous devez installer les bibliothèques Irrlicht, Qt et cppconn pour compiler le projet. Si vous êtes sous Linux vous trouverez facilement les paquets correspondants dans votre gestionnaire de paquets.

Vous pouvez utiliser le fichier "CMakeLists.txt" pour générer un Makefile du projet. N'oubliez pas de remplir le fichier "CMakeCache.txt" avec vos informations (emplacement des bibliotèques, Release ou Debug, ...). Je suis désolé mais Qt crer pleins de fichiers "moc" a coté des sources lors de l'execution de CMake.

L'executable doit être placé a côté des dossiers "gui", "parametre" et "mesh" pour bien prendre en compte tous les fichiers du jeu. 

Si le programme plante après avoir tenter de vous connecter (Quand vous appuyer sur "jouer") vérifier bien les informations du fichier "parametre/parametre_connection_BDD.txt" en vous aidant du fichier "parametre/README.txt".

Une version compilé pour Linux ainsi qu'un paquet Debian est présente sur mon site (lien en dessous).

Pour plus de détails aller voire mon site : http://remi.perenne.free.fr/site_world_of_colonies/vue/jouer.php

Me contacter:
6 rue Bourdelle, Brest 29200
06 52 87 68 25
remi.perenne@free.fr
http://remi.perenne.free.fr

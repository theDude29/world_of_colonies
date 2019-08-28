Ce logiciel a été dévellopé par Rémi Pérenne et est sous license GNU GENERAL PUBLIC LICENSE, vous en trouverez une copie dans ce dossier le nom du fichier est "COPYING.txt".

Vous devez installer les bibliothèques Irrlicht, Qt et cppconn pour compiler le projet. Si vous êtes sous Linux vous trouverez facilement les paquets correspondants dans votre gestionnaire de paquets.

Vous pouvez utiliser le fichier "CMakeLists.txt" pour générer un Makefile du projet. N'oubliez pas de remplir le fichier "CMakeCache.txt" avec vos informations (emplacement des bibliotèques, Release ou Debug, ...). Je suis désolé mais Qt crer pleins de fichiers "moc" a coté des sources lors de l'execution de CMake.

L'executable doit être placé a côté des dossiers "gui", "parametre" et "mesh" pour bien prendre en compte tous les fichiers du jeu. 

Si le programme plante après avoir tenter de vous connecter (Quand vous appuyer sur "jouer") vérifier bien les informations du fichier "parametre/parametre_connection_BDD.txt" en vous aidant du fichier "parametre/README.txt".

Si vous avez la moindre questions n'ésitez pas à me contacter : remi.perenne@free.fr

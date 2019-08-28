Le fichier "pseudo.txt" sert à retenir le pseudo de l'utilisateur il ne sert à rien de le modifier cela pourrait même endommager le logiciel.

Le fichier "parametre_connection_BDD.txt" sert à donner les informations de connections à votre serveur de Base De Donnée : -La première ligne indique l'adresse de la BDD (ex : "localhost")
			    -La deuxième ligne indique vos droit de connection (ex : "root")
			    -La troisième ligne indique le mot de passe de connection*
		            -La quatrième ligne indique le nom de votre base (ex : "baseWOC")

* : Le mot de passe de votre BDD n'est pas conservé vous le constaterez en lisant les sources de ce logiciel. Si vous ne voulez quand même pas écrire votre mot de passe ici il vous faut recompiler les sources en deffinissant votre mot de passe ligne 34 du fichier "bdd.cpp".

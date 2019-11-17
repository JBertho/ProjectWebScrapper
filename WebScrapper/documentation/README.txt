Le fichier de configuration se situe dans le dossier resource.

Le fichier de configuration pourra contenir les éléments suivants :
#: Commentaire sur 1 ligne
=: Début de la définition d’une action
{key -> value}: Association d’informations en fonction de l’élément parent
+: Début de la définition des options d’une action
==: Début de la définition d’une tache (une tache est un ensemble d’action à réaliser en fonction de critère)

Les options possibles sont :
max-depth -> number : Cela permet de bloquer le maximum de profondeur du site.
versioning -> on | off : Cela permet de garder une trace des moments ou l'action à été effectué et quelles étaient ses options.
type -> (string1, string2, string3) : Permet de spécifier quelles sont les types de fichier qu'il faut enregistrer selon les content-type ( text/html, image/png).
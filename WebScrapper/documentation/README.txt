Le fichier de configuration se situe dans le dossier resource.

Le fichier de configuration pourra contenir les �l�ments suivants :
#: Commentaire sur 1 ligne
=: D�but de la d�finition d�une action
{key -> value}: Association d�informations en fonction de l��l�ment parent
+: D�but de la d�finition des options d�une action
==: D�but de la d�finition d�une tache (une tache est un ensemble d�action � r�aliser en fonction de crit�re)

Les options possibles sont :
max-depth -> number : Cela permet de bloquer le maximum de profondeur du site.
versioning -> on | off : Cela permet de garder une trace des moments ou l'action � �t� effectu� et quelles �taient ses options.
type -> (string1, string2, string3) : Permet de sp�cifier quelles sont les types de fichier qu'il faut enregistrer selon les content-type ( text/html, image/png).
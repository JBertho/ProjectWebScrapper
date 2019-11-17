Le fichier de configuration se situe dans le dossier resource.

Le fichier de configuration pourra contenir les elements suivants :
#: Commentaire sur 1 ligne
=: Debut de la definition d'une action
{key -> value}: Association d'informations en fonction de l'element parent
+: Debut de la definition des options d'une action
==: Debut de la definition d'une tache (une tache est un ensemble d'action a realiser en fonction de critere)

Les options possibles sont :
max-depth -> number : Cela permet de bloquer le maximum de profondeur du site.
versioning -> on | off : Cela permet de garder une trace des moments où l'action a été effectué et quelles etaient ses options.
type -> (string1, string2, string3) : Permet de spécifier quelles sont les types de fichier qu'il faut enregistrer selon les content-type ( text/html, image/png).
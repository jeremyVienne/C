Vienne Jérémy
Irakoze Franco Davy



fichier test fournis (make test) pour course et multif.


Observation exercice 8:
  Question 1:(voir observe.c)
    le programme crée N processus fils qui dans une boucle infinie ne termine jamais et indique leur pid sur la sortie standard pour dire qu'ils sont toujours vivant. Le processus père quant à lui va afficher la liste des processus en cours d'execution et attendre que ses processus fils se terminent.

  Question 2:
    Si l'on tue le processus père, les processus fils continuent leur execution et donc continuent d'afficher leur pid.

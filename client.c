/*
* Processus client:
*  - envoie deux nombres au serveur par la MSQ
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>


#include "msq_def.h"

/**********************************************************/
/* Programme principal                                    */
/**********************************************************/
int main()
{
    int msqid, nb1, nb2;
    ssize_t l;
    struct requete la_requete;
    struct reponse la_reponse;

    /* récupération du msgid */
    if((msqid=msgget((key_t)CLE, 0)) < 0)
    {
        perror("msgget");
        exit(1);
    }


    /* Préparation de la requête et envoi */

    printf ("Donnez moi deux nombres a additionner :");
    scanf ("%d %d", &nb1, &nb2);
    printf("DEBUG : On va envoyer %d %d\n", nb1, nb2);
    la_requete.letype = ADD;
    la_requete.nb1 = nb1;
    la_requete.nb2 = nb2;
    la_requete.pid = getpid();

    if(msgsnd(msqid, &la_requete, sizeof(struct requete) - sizeof(long), 0) == -1)
    {
        perror("msgsnd");
        exit(2);
    }

    printf("DEBUG : On a envoyé venant du pid %d, on attend la réponse\n", la_requete.pid);

    /* réception de la réponse */
    if((l=msgrcv(msqid, &la_reponse, sizeof(struct reponse) - sizeof(long), getpid(), 0)) == -1)
    {
        perror("msgrcv");
        exit(2);
    }

    printf ("Le résultat reçu est %d\n", la_reponse.res);
    exit(0);
}



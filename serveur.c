/*
* Processus serveur: 
*  - crée la MSQ 
*  - additionne 1es deux nombres envoyés par le client
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#include "msq_def.h"

/**********************************************************/
/* Programme principal                                    */
/**********************************************************/
int main()
{
int msqid;
ssize_t l;
struct requete la_requete;
struct reponse la_reponse;

/* allocation MSQ */
if((msqid=msgget((key_t)CLE, 0750|IPC_CREAT|IPC_EXCL)) == -1)
{
  perror("msgget");
  exit(1);
}

while (1) 
{
printf("DEBUG : on attend une requête\n");

/* lecture d'une requête */ ;
if((l=msgrcv(msqid, &la_requete, sizeof(struct requete) - sizeof(long), ADD, 0)) == -1)
{
  perror("msgrcv");
  exit(2);
}

la_reponse.res = la_requete.nb1 + la_requete.nb2;
la_reponse.letype = la_requete.pid; /* type associé au message: le pid du client */

printf("DEBUG : on envoie la réponse : %d à %d\n", la_reponse.res, la_reponse.letype);
if(msgsnd(msqid, &la_reponse, sizeof(struct reponse) - sizeof(long), 0) == -1)
{
  perror("msgsnd");
  exit(2);
}
}
exit(0);
}

/* Définition de
 * - constantes
 * - symboles
 * - types
*/


#define CLE 0x100
#define ADD 1 /* Type de message : 1 -> ADDITION */


/* Définition des structures des requêtes et des réponses */
struct requete {
  long letype;  /* type de message : un seul (ADD) dans notre cas */
  int nb1;      /* premier membre de 1'addition */ 
  int nb2;      /* second membre de 1'addition */ 
  pid_t pid;/*1e client indique ici son pid */
};

struct reponse {
  long letype;  /* prend 1a valeur du pid du c11ent */
  int res;      /* 1e résu1tat de l'addition */
};

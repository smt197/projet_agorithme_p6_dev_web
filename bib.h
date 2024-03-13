#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#define TAILLE_MAX 100
#define MAX_ETUDIANTS 100
#define MAX_CLASS_LENGTH 20
#define CODE_MAX_LENGTH 100
#define MAX_CODE_LENGTH 100

//premier livrable

//structure
 typedef struct
 {
    int id;
    char nom[50];
    char prenom[50];
 } APPRENANT;

 typedef struct {
    char nom[TAILLE_MAX];
    char prenom[TAILLE_MAX];
    int code;
    char classe[MAX_CLASS_LENGTH];
} Etudiant;

typedef struct {
    int code;
    char prenom[TAILLE_MAX];
    char nom[TAILLE_MAX];
    char classe[TAILLE_MAX]; 
    char date[TAILLE_MAX];
    char heure[TAILLE_MAX];
} Presence;



typedef struct {
    char date[TAILLE_MAX];
    char nom[TAILLE_MAX];
} Absence;

typedef struct{
    int id;
    char date_presence[30];
    char heure_presence[10];
    char code[30];
    char nom[30];
    char prenom[50];
    char classe[10];
    int nbMinutesRetard;
}Retard;

typedef struct {
    int code;
    char classe[MAX_CLASS_LENGTH];
    char message[TAILLE_MAX];
} Message;
typedef struct
{
    int j, m, a;
} Date;
typedef struct
{
    int h, m, s;
} Heure;

// typedef struct
// {
//     int id;
//     char contenue[200];
//     Etudiant dest;
//     Date date;
//     Heure heure;
//     int status;
// } Message;


int afficheMenuAdmin();
int afficheMenuApprenant();
int authentification();
int verifierLoginMdp(const char* Fichier, const char* loginSaisi, const char* mdpSaisi);
void marquerPresenceAdmin();
int verifierPresenceId(int id, const char *nomFichier);
void marquerPresenceApprenant();
void sousMenuApprenant(int c);
char continuer();
void genererFichierListePresenceOrganise();
void genererFichierPresences();
void listePresencesParDate();
int etudiantDansClasse(const char* nomFichier, const char* nomClasse, const char* nom, const char* prenom);
void obtenirNomClasse(const char* fichier, char* nomClasse);
int validerFormatDate(const char *date);
int sousMenuAdmin(); 
void gestionMenu();

void envoyerMessageApprenants(const char *auteur);
void lireMessageApprenants() ;
int sousMenuMessage();
Message saisirMessage() ;
void envoyerMessage(Message message);
void envoyerMessageAuxApprenants();
void fileOfMinutesOfRetardOfStudents();
int nbMinuteRetardOfConnectedUser(char *code);
void genererListeAbsences();
// void messageToAllStudents();
#endif 
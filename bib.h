#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#define TAILLE_MAX 100
#define MAX_ETUDIANTS 100
#define MAX_CLASS_LENGTH 20

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
} Etudiant;

typedef struct {
    int code;
    char prenom[TAILLE_MAX];
    char nom[TAILLE_MAX];
    char classe[TAILLE_MAX]; // Ajout du membre classe
    char date[TAILLE_MAX];
} Presence;

typedef struct {
    char classe[MAX_CLASS_LENGTH];
    char message[TAILLE_MAX];
} Message;



//prototype
int afficheMenuAdmin();
int afficheMenuApprenant();
int authentification();
int verifierLoginMdp(const char* Fichier, const char* loginSaisi, const char* mdpSaisi);
void marquerPresenceAdmin();
int verifierPresenceId(int id, const char *nomFichier);
void marquerPresenceApprenant();
//int sousMenuAdmin(int c);
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

#endif 
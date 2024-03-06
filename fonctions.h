#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PROFILE_LENGTH 50
#define MAX_LINE_LENGTH 100
#define MAX_ETUDIANTS 100
#define MAX_FILENAME_LENGTH 100

// Déclaration des prototypes des fonctions

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} Utilisateur;

typedef struct 
{
    int id;
    char nom[50];
    char prenom[50];
    char matricule[10];
}APPRENANT;

typedef struct 
{
    char libelle[20];
    APPRENANT ap;
}CLASSE;

typedef struct 
{
    CLASSE cl;
    APPRENANT ap;
    char jour[10];

}PRESENCE;





Utilisateur saisirIdentifiant();
bool verifierIdentifiants(Utilisateur *utilisateur);
void menuAdmin();
void menuUtilisateur();
void masquerMotDePasse(char *motDePasse);


#endif 


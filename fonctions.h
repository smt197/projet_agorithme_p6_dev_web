#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PROFILE_LENGTH 50
#define MAX_LINE_LENGTH 100
#define MAX_ETUDIANTS 100
#define MAX_FILENAME_LENGTH 100

#define MAX_STUDENTS 100
#define MAX_CODE_LENGTH 10
#define MAX_NAME_LENGTH 50
#define MAX_CLASS_LENGTH 20


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
    int present;
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
    char date[10];
    int statut;

}PRESENCE;

typedef struct {
    char code[MAX_CODE_LENGTH];
    char name[MAX_NAME_LENGTH];
    char class[MAX_CLASS_LENGTH];
    int present;
    time_t heure;
} Student;



Utilisateur saisirIdentifiant();
bool verifierIdentifiants(Utilisateur *utilisateur);
void menuAdmin();
void menuGestion();
void menuUtilisateur();
int isStudentPresent(Student students[], int numStudents, const char *code);
// void masquerMotDePasse(char *motDePasse);
void markAttendance(Student students[], int numStudents);
void saveAttendanceToFile(Student students[], int numStudents);
void traitement();


#endif 


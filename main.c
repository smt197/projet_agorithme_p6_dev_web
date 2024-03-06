#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "fonctions.h" 


#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_PROFILE_LENGTH 50
#define MAX_LINE_LENGTH 100
#define MAX_ETUDIANTS 100
#define MAX_FILENAME_LENGTH 100



// typedef struct {
//     char username[MAX_USERNAME_LENGTH];
//     char password[MAX_PASSWORD_LENGTH];
// } Utilisateur;

// typedef struct 
// {
//     int id;
//     char nom[50];
//     char prenom[50];
//     char matricule[10];
// }APPRENANT;

// typedef struct 
// {
//     char libelle[20];
//     APPRENANT ap;
// }CLASSE;

// typedef struct 
// {
//     CLASSE cl;
//     APPRENANT ap;
//     char jour[10];

// }PRESENCE;





// Utilisateur saisirIdentifiant();
// bool verifierIdentifiants(Utilisateur *utilisateur);
// void menuAdmin();
// void menuUtilisateur();
// void masquerMotDePasse(char *motDePasse);



int main() {
    Utilisateur utilisateur;
    saisirIdentifiant(utilisateur);
    return 0;
}

// Utilisateur saisirIdentifiant(){
//     Utilisateur utilisateur;

//     do {
//         printf("Entrer votre username : ");
//         scanf("%s", utilisateur.username);
//         getchar();
//         if (strlen(utilisateur.username) == 0) {
//             printf("Le nom d'utilisateur ne peut pas être vide.\n");
//         }
//     } while (strlen(utilisateur.username) == 0);

//     do {

//      masquerMotDePasse(utilisateur.password);

//         if (strlen(utilisateur.password) == 0) {
//             printf("Le mot de passe ne peut pas être vide.\n");
//         }
//     } while (strlen(utilisateur.password) == 0);    

//     if (verifierIdentifiants(&utilisateur)) {
//         printf("Identifiants valides. Connexion réussie.\n");

//         if (strcmp(utilisateur.username, "admin") == 0)
//         {
//             menuAdmin();
//         }
//         else{menuUtilisateur();
//         }
        
//     } else {
//         printf("Identifiants invalides. Connexion échouée!!.\n");
//     }
//     return utilisateur;
// }

// void masquerMotDePasse(char *motDePasse) {
//     printf("Entrer votre mot de passe : ");
    
//     // Désactiver l'affichage en écho des caractères saisis
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);
//     term.c_lflag &= ~ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);

//     // Lire le mot de passe
//     fgets(motDePasse, 50, stdin);
    
//     // Supprimer le caractère de nouvelle ligne
//     motDePasse[strcspn(motDePasse, "\n")] = '\0';

//     // Restaurer l'affichage en écho
//     term.c_lflag |= ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// bool verifierIdentifiants(Utilisateur *utilisateur) {
//     FILE *fichier = fopen("fichier_connexion.txt", "r");
//     if (fichier == NULL) {
//         perror("Erreur lors de l'ouverture du fichier");
//         return false;
//     }

//     char ligne[MAX_LINE_LENGTH];
//     Utilisateur utilisateurEnregistre;
//     bool identifiantsTrouves = false;

//     while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
//         if (sscanf(ligne, "%s %s", utilisateurEnregistre.username, utilisateurEnregistre.password) == 2) {
//             if (strcmp(utilisateur->username, utilisateurEnregistre.username) == 0 && 
//                 strcmp(utilisateur->password, utilisateurEnregistre.password) == 0) {
//                 identifiantsTrouves = true;
//                 break;
//             }
//         }
//     }

//     fclose(fichier);

//     return identifiantsTrouves;
// }


// void menuAdmin(){
// int choix;
// do
// {
//     int choix;   printf("Voici le menu Admin :\n");
//     printf("1. GESTION DES ÉTUDIANTS\n");
//     printf("2. GÉNÉRATION DE FICHIERS\n");
//     printf("3. MARQUER LES PRÉSENCES\n");
//     printf("4. ENVOYER UN MESSAGE\n");
//     printf("5. QUITTER\n");
//     printf("Faites votre choix:\n");
//     scanf("%d",&choix);

//     if (choix == 5)
//     {
//        break;
//     }
    
    
// } while (choix != 5);
// }




// void menuUtilisateur() {
//     printf("Voici le menu Utilisateur :\n");
//     printf("1. MARQUER MA PRÉSENCE\n");
//     printf("2. NOMBRE DE MINUTES D’ABSENCE\n");
//     printf("3. MES MESSAGES (0)\n");
//     printf("4. QUITTER\n");
// }













































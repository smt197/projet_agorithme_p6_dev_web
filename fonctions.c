#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "fonctions.h" 


Utilisateur saisirIdentifiant() {
    Utilisateur utilisateur;

    do {
        printf("Entrer votre username : ");
        scanf("%s", utilisateur.username);
        getchar();
        if (strlen(utilisateur.username) == 0) {
            printf("Le nom d'utilisateur ne peut pas être vide.\n");
        }
    } while (strlen(utilisateur.username) == 0);

    do {
        masquerMotDePasse(utilisateur.password);

        if (strlen(utilisateur.password) == 0) {
            printf("Le mot de passe ne peut pas être vide.\n");
        }
    } while (strlen(utilisateur.password) == 0);

    while (!verifierIdentifiants(&utilisateur)) {
        printf("Identifiants invalides. Connexion échouée!!.\n");
        printf("Re-entrer vos identifiants pour vous reconnecter.\n");
        printf("\n");
        
        do {
            printf("Entrer votre username : ");
            scanf("%s", utilisateur.username);
            getchar();
            if (strlen(utilisateur.username) == 0) {
                printf("Le nom d'utilisateur ne peut pas être vide.\n");
            }
        } while (strlen(utilisateur.username) == 0);

        do {
            masquerMotDePasse(utilisateur.password);
    
            if (strlen(utilisateur.password) == 0) {
                printf("Le mot de passe ne peut pas être vide.\n");
            }
        } while (strlen(utilisateur.password) == 0);
    }

    if (strcmp(utilisateur.username, "admin") == 0) {
        menuAdmin();
    } else {
        menuUtilisateur();
    }
    
    return utilisateur;
}

void masquerMotDePasse(char *motDePasse) {
    printf("Entrer votre mot de passe : ");
    
    // Désactiver l'affichage en écho des caractères saisis
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    // Lire le mot de passe
    fgets(motDePasse, 50, stdin);
    
    // Supprimer le caractère de nouvelle ligne
    motDePasse[strcspn(motDePasse, "\n")] = '\0';

    // Restaurer l'affichage en écho
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}



bool verifierIdentifiants(Utilisateur *utilisateur) {
    FILE *fichier = fopen("fichier_connexion.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return false;
    }

    char ligne[MAX_LINE_LENGTH];
    Utilisateur utilisateurEnregistre;
    bool identifiantsTrouves = false;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (sscanf(ligne, "%s %s", utilisateurEnregistre.username, utilisateurEnregistre.password) == 2) {
            if (strcmp(utilisateur->username, utilisateurEnregistre.username) == 0 && 
                strcmp(utilisateur->password, utilisateurEnregistre.password) == 0) {
                identifiantsTrouves = true;
                break;
            }
        }
    }

    fclose(fichier);

    return identifiantsTrouves;
}


void menuAdmin(){
int choix;
bool quitter = false;
do
{
    int choix;   printf("Voici le menu Admin :\n");
    printf("1. GESTION DES ÉTUDIANTS\n");
    printf("2. GÉNÉRATION DE FICHIERS\n");
    printf("3. MARQUER LES PRÉSENCES\n");
    printf("4. ENVOYER UN MESSAGE\n");
    printf("5. QUITTER\n");
    printf("Faites votre choix:\n");
    scanf("%d",&choix);

    if (choix == 5)
    {
       quitter = true;
      
    }
    
    
} while (!quitter);
}




void menuUtilisateur() {
    int choix;
    do
    {
        printf("Voici le menu Utilisateur :\n");
        printf("1. MARQUER MA PRÉSENCE\n");
        printf("2. NOMBRE DE MINUTES D’ABSENCE\n");
        printf("3. MES MESSAGES (0)\n");
        printf("4. QUITTER\n");
        printf("Faites votre choix:\n");
        scanf("%d",&choix);

        if (choix == 5)
        {
           break;
        }    
    } while (choix != 4);
    
}



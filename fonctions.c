#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include "fonctions.h" 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

char getch() {
#ifdef _WIN32
    return _getch();
#else
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
#endif
}

void getHiddenInput(char *password, int maxLength) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\n' || ch == '\r') {
            password[i] = '\0';
            break;
        } else if (ch == 127 && i > 0) {  
            printf("\b \b");
            i--;
        } else if (isprint(ch) && i < maxLength - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
}



Utilisateur saisirIdentifiant() {
    Utilisateur utilisateur;

    do {
        printf("Entrer votre username : ");
        scanf("%s", utilisateur.username);
        if (strlen(utilisateur.username) == 0) {
            printf("Le nom d'utilisateur ne peut pas être vide!!.\n");
        }
    } while (strlen(utilisateur.username) == 0);

    do {
        printf("Entrer votre mot de passe : \n");
       getHiddenInput(utilisateur.password, sizeof(utilisateur.password));

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
            printf("Entrer votre mot de passe :\n ");
            getHiddenInput(utilisateur.password, sizeof(utilisateur.password));    
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


// Fonction pour vérifier si le fichier existe
FILE *openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", filename);
        return NULL;
    }
    return file;
}

// Fonction pour vérifier si un étudiant a déjà été marqué présent
int isStudentPresent(Student students[], int numStudents, const char *code) {
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].code, code) == 0) {
            return students[i].present;
        }
    }
    return -1; // Code d'étudiant non trouvé
}

// Fonction pour marquer les présences des Apprenants
void markAttendance(Student students[], int numStudents) {
    char code[MAX_CODE_LENGTH];
    printf("Entrez le code ['q' pour terminer] :\n");
    scanf("%s", code);
    
    while (strcmp(code, "q") != 0) {
        int presence = isStudentPresent(students, numStudents, code);
        if (presence == 1) {
            printf("L'Apprenant est déjà marqué présent.\n");
        } else if (presence == 0 || presence == -1) {
            int found = 0;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].code, code) == 0) {
                printf("L'Apprenant %s de la classe %s est présent ? (1 pour oui) : ", students[i].name, students[i].class);
                scanf("%d", &students[i].present);
                found = 1;
                if (students[i].present == 1)
                {
                    students[i].heure = time(NULL) ;
                }
                found = 1;
                
                break;
            }
        }
        if (!found) {
            printf("Code invalide\n Appuyer sur une touche pour continuer\n"); 
        }
        }
        printf("Entrez le code ['q' pour terminer] : ");
        scanf("%s", code);
    }
        menu:;
        char password[50];
        printf("mot de passe  : ");
        scanf("%s", password);
        if (strcmp(password, "admin1234") != 0) {
            printf("Mot de passe incorrect!!\n");
            // markAttendance(students, numStudents);
            goto menu;
        } else {
            printf("Mot de passe correct. Quitter.\n");
    }
}

// Fonction pour enregistrer la liste des présences dans un fichier
void saveAttendanceToFile(Student students[], int numStudents) {
    FILE *outputFile = fopen("liste_presence.txt", "a");
    if (outputFile == NULL) {
        printf("Impossible de créer le fichier de sortie.\n");
        return;
    }

    fprintf(outputFile, "Liste des présences :\n\n");
    for (int i = 0; i < numStudents; i++) {
        if (students[i].present == 1) {
            char* time_str = ctime(&students[i].heure);
            time_str[strlen(time_str) - 1] = '\0';
            fprintf(outputFile, "%s - %s (%s) - %s\n", students[i].code, students[i].name, students[i].class, time_str);
        }
    }

    fclose(outputFile);
    printf("les apprenants ont ete bien ajoutees avec succes!!.\n");
}

void traitement(){
    Student students[MAX_STUDENTS];
    int numStudents = 0;
    FILE *inputFile;
    char filename[100];

    inputFile = openFile("liste_apprenant.txt", "r");
    if (inputFile == NULL) {
        // return 1; 
    }

    while (fscanf(inputFile, "%s %s %s", students[numStudents].code, students[numStudents].name, students[numStudents].class) == 3 && numStudents < MAX_STUDENTS) {
        students[numStudents].present = 0;
        numStudents++;
    }

    fclose(inputFile);

    markAttendance(students, numStudents);

    saveAttendanceToFile(students, numStudents);
}


void menuAdmin(){
int choix;
bool quitter = false;
do
{
    int choix;
    printf("\n----------------------------------:\n");
    printf("-----> MARQUER LES PRESENCES <-----:\n");
    printf("----------------------------------:\n");
    printf("1. Marquer presence\n");

    printf("Faites votre choix:\n");
    scanf("%d",&choix);

    switch (choix)
    {
    case 1:
        traitement();
        break;
    
    default:
        break;
    }

    if (choix == 5)
    {
       quitter = true;
      
    }
    
    
} while (!quitter);
}

void menuGestion(){
int choix;
bool quitter = false;
do
{
    printf("Liste des classes :\n");
    printf("1. devweb\n");
    printf("2. devdata\n");
    printf("3. refdig\n");
    printf("4. Quitter\n");
    printf("Faites votre choix:\n");
    scanf("%d",&choix);

    switch (choix)
    {
    case 1:
        /* code */
        break;
    
    default: 
        break;
    }
    if (choix == 4)
    {
        break;
    }    
} while (choix != 4);

    
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



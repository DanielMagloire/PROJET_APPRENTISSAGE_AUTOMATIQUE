//**********************************************//
//                                              //
//              TP2 - APPRENTISSAGE             //
//                                              //
//       Implementation Perceptron Simple       //
//                                              //
//        Prepare par :                         //
//          ELIODOR Ednalson Guy Mirlin - P21   //
//          MEDOU Daniel Magloire - P21         //
//                                              //
//**********************************************//

#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>

//Definition des parametres pour la base leukimia
#define nombredeLigne_train_leukimia 38
#define nombredeLigne_test_leukimia 34
#define nombredeColonne_base_Leukimia 7130

//Definition des parametres pour la base Spam
#define nombreDeligne_Train_SPAM 3068
#define nombredeColonne_Train_SPAM 59
#define nombredeLigne_test_SPAM 1533
#define nombredeColonne_test_SPAM 59

//Definition des parametres pour la base Ovarian
#define nombredeLigne_train_Ovarian 169
#define nombredeColonne_train_Ovarian 15156
#define nombredeLigne_test_Ovarian 84
#define nombredeColonne_test_Ovarian 15156

using namespace std;

//Declaration et initialisation des variables globales du programme
//Fichier Train
int nombreColonne_trn = 0;
int nombreLigne_trn = 0;
//Fichier Test
int nombreColonne_tst = 0;
int nombreLigne_tst = 0;
//Nombre de classe
int nombreDeClasse = 0;

//Lecture des donnees depuis les fichiers sauvegardes sur le PC
double **read_data(string file, string type) {
    int nombreLigne = 0, nombreColonne = 0;
    double **data;
    ifstream file_reader(file.c_str(), ios::in);
    //Test d'ouverture du fichier
    if (file_reader)
    {   //Definition des nombres de lignes et de colonnes
        if (file.compare("data/spam/spam.trn") != 0 && file.compare("data/ovarian/ovarian.trn") != 0
                && type.compare("trn") == 0) {
		if(file.compare("data/leukemia/ALLAML.trn")==0){
                nombreLigne_trn=nombredeLigne_train_leukimia;
                nombreColonne_trn=nombredeColonne_base_Leukimia;
            }

            nombreColonne_trn++;
            nombreLigne = nombreLigne_trn;
            nombreColonne = nombreColonne_trn;
        }

        if (file.compare("data/spam/spam.tst") != 0 && file.compare("data/ovarian/ovarian.tst") != 0
                && type.compare("tst") == 0) {
            if(file.compare("data/leukemia/ALLAML.tst")==0){
		file.erase(file.begin()+13, file.end());
                nombreLigne_tst=nombredeLigne_test_leukimia;
                nombreColonne_tst=nombredeColonne_base_Leukimia;
            }

            nombreColonne_tst++;
            nombreLigne = nombreLigne_tst;
            nombreColonne = nombreColonne_tst;
        }

        if (file.compare("data/spam/spam.trn") == 0) {
            nombreLigne_trn = nombreDeligne_Train_SPAM;
            nombreColonne_trn = nombredeColonne_Train_SPAM;
            nombreLigne = nombreLigne_trn;
            nombreColonne = nombreColonne_trn;
        }

        if (file.compare("data/spam/spam.tst") == 0) {
            nombreLigne_tst = nombredeLigne_test_SPAM;
            nombreColonne_tst = nombredeColonne_test_SPAM;
            nombreLigne = nombreLigne_tst;
            nombreColonne = nombreColonne_tst;
	    file.erase(file.begin()+9, file.end());

        }

        if (file.compare("data/ovarian/ovarian.trn") == 0) {
            nombreLigne_trn = nombredeLigne_train_Ovarian;
            nombreColonne_trn = nombredeColonne_train_Ovarian;
            nombreLigne = nombreLigne_trn;
            nombreColonne = nombreColonne_trn;
        }

        if (file.compare("data/ovarian/ovarian.tst") == 0) {
            nombreLigne_tst = nombredeLigne_test_Ovarian;
            nombreColonne_tst = nombredeColonne_test_Ovarian;
            nombreLigne = nombreLigne_tst;
            nombreColonne = nombreColonne_tst;
	    file.erase(file.begin()+12, file.end());

        }

        // Creation de la matrice pour le sauvegarde des donnees
        data = new double* [nombreLigne];
        for (int i = 0; i < nombreLigne; i++) {
            data[i] = new double[nombreColonne];
        }


        //Fixation de la premiere colonne a 1 - biais

        for (int i = 0; i < nombreLigne; i++) {
            data[i][0] = 1;
        }

        //Stockage des donnees
        for (int k = 0; k < nombreLigne; k++) {
            for (int l = 1; l < nombreColonne; l++) {
                file_reader >> data[k][l];
            }

        }
        file_reader.close(); // Fermeture
    } else {
        cerr << "ERROR - Impossible d'ouvrir le fichier - ERROR !" << endl;
    }


    return data;
}

//COMPARAISON

bool comparaisonLigne(double* rowA, double* rowB) {
    return (rowA[1] < rowB[1]);
}

//Gestion de normalisation du jeu de donnees

double ** normalisation(double** data, int nombreLigne, int nombreColonne) {

    double* col;
    col = new double[nombreLigne];

    for (int i = 1; i < nombreColonne - 1; i++) {
        for (int j = 0; j < nombreLigne; j++) {

            col[j] = data[j][i];

        }
        std::sort(col, col + nombreLigne);
        for (int j = 0; j < nombreLigne; j++) {

            data[j][i] = (data[j][i] - col[0]) / (col[nombreLigne - 1] - col[0]);

        }
    }

    return data;
}

//Prediction of class from weight and inputs

int predictionClasse(double * poids, double *line) {

    int predicted_class = 1;
    double sortie = 0;

    for (int i = 0; i < nombreColonne_trn - 1; i++) {
        sortie += poids[i] * line[i];
    }

    if (sortie < 0) {
        predicted_class = -1;
    }

    return predicted_class;
}

//computing of weigth that fit to the training set

double* perceptron(double** trainning, double pasApprentissage, int maximumInteration) {

    double *poids;
    //bool good = false;
    int count = 0;
    poids = new double[nombreColonne_trn - 1];
    int classePredite;

    //assigning random values to weight at their initialisation
    for (int i = 0; i < nombreColonne_trn - 1; i++) {

        poids[i] = rand() / double(RAND_MAX);

    }

    //Perceptron algorithm
    for (int j = 0; j < maximumInteration; j++) {
        for (int k = 0; k < nombreLigne_trn; k++) {

            classePredite = predictionClasse(poids, trainning[k]);

            if (classePredite != trainning[k][nombreColonne_trn - 1]) {
                count++;

                for (int i = 0; i < nombreColonne_trn - 1; i++) {

                    poids[i] += pasApprentissage * (trainning[k][nombreColonne_trn - 1] - classePredite) * trainning[k][i];

                }

            }
        }
    }

    return poids;
}

//computing of the classification performance

double tauxBonClassement(int **matriceDeConfusion) {
    double taux = 0;
    double SommeDiagonale = 0;
    double sommeTotale = 0;

    for (int i = 0; i < nombreDeClasse; i++) {
        for (int j = 0; j < nombreDeClasse; j++) {
            if (i == j) {
                SommeDiagonale += matriceDeConfusion[i][j];
            }
            sommeTotale += matriceDeConfusion[i][j];
        }
    }
    taux = SommeDiagonale / sommeTotale;
    return taux;

}

//Operation Hold Out sur les fichiers

void holdOut_Fonction(string file) {

    if (file.compare("data/spam/spam.trn") == 0) {
        system("sort -R data/spam/spam.data > data/spam/spam.txt");
        system("head -n3068 data/spam/spam.txt > data/spam/spam.trn");
        system("tail -n1533 data/spam/spam.txt > data/spam/spam.tst");

    } else {

        system("sort -R data/ovarian/ovarian.data > data/ovarian/ovarian.txt");
        system("head -n169 data/ovarian/ovarian.txt > data/ovarian/ovarian.trn");
        system("tail -n84 data/ovarian/ovarian.txt > data/ovarian/ovarian.tst");
    }

}

int main(int argc, char** argv) {

    //lecture et sauvegarde des parametres du programme
    char *trn = argv[1];
    char *tst = argv[2];
    char fichierApprentissage[50] = "";
    strcat(fichierApprentissage, trn);

    char fichierDeTest[50] = "";
    strcat(fichierDeTest, tst);

    double pasApprentissage;
    pasApprentissage = atof(argv[3]);
    int maximumInteration;
    maximumInteration = atoi(argv[4]);


    double** training;
    double** test;


    //lecture des donnees dans la base specifique
    string holdOut_Fonction_file(fichierApprentissage);
    if (holdOut_Fonction_file.compare("data/ovarian/ovarian.trn") == 0 ||
            holdOut_Fonction_file.compare("data/spam/spam.trn") == 0) {
        holdOut_Fonction(fichierApprentissage);
    }
    training = read_data(fichierApprentissage, "trn");
    test = read_data(fichierDeTest, "tst");

    //Normalisation des donnees de la base spam et leukemia
    if (holdOut_Fonction_file.compare("data/leukemia/ALLAML.trn") == 0 ||
            holdOut_Fonction_file.compare("data/spam/spam.trn") == 0) {

        training = normalisation(training, nombreLigne_trn, nombreColonne_trn);
        test = normalisation(test, nombreLigne_tst, nombreColonne_tst);
    }

    //Sauvegarde de la classe attendue
    int classeSuposee [nombreLigne_tst];
    for (int i = 0; i < nombreLigne_tst; i++) {
        classeSuposee[i] = test[i][nombreColonne_tst - 1];
    }

    //Determination des classes attendues
    std::sort(classeSuposee, classeSuposee + nombreLigne_tst);
    int compteur = 0;
    std::vector<int> classes;
    for (int i = 0; i < nombreLigne_tst; i++) {

        compteur = std::count(classeSuposee, classeSuposee +
                nombreLigne_tst, classeSuposee[i]);
        classes.push_back(classeSuposee[i]);
        i = i + compteur - 1;
        nombreDeClasse++;

    }

    //creation de la matrice de confusion
    int **matConfusion;
    matConfusion = new int*[nombreDeClasse];
    for (int j = 0; j < nombreDeClasse; j++) {
        matConfusion[j] = new int [nombreDeClasse];
        for (int n = 0; n < nombreDeClasse; n++) {
            matConfusion[j][n] = 0;
        }
    }

    //calcul sur les classes attendues
    double* poids;
    poids = new double[nombreColonne_trn - 1];
    poids = perceptron(training, pasApprentissage, maximumInteration);

    int *prediction;
    prediction = new int[nombreLigne_tst];
    for (int i = 0; i < nombreLigne_tst; i++) {
        prediction[i] = predictionClasse(poids, test[i]);
    }

    //calcul de la matrice de confusion
    for (int m = 0; m < nombreLigne_tst; m++) {

        int pos1 = std::find(classes.begin(), classes.end(), (int) test[m][nombreColonne_tst - 1]) - classes.begin();
        int pos2 = std::find(classes.begin(), classes.end(), (int) prediction[m]) - classes.begin();
        matConfusion[pos1][pos2]++;
    }
    cout << "\n Nombre de classes trouve : " << nombreDeClasse << endl;
    cout << "\n Matrice de confusion"<< endl;


    for (int a = 0; a < nombreDeClasse; a++) {
        for (int b = 0; b < nombreDeClasse; b++) {
            cout << matConfusion[a][b] << " ";
        }
        cout << endl;
    }

    cout << "\n le taux de bon classement est :" << tauxBonClassement(matConfusion)*100 << "%" << endl;

    return 0;

}

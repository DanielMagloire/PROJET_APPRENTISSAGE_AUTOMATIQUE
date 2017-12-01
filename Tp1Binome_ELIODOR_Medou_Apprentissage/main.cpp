
//**********************************************//
//                                              //
//              TP1 - APPRENTISSAGE             //
//                                              //
//       Classification avec K-NN               //
//                                              //
//        Prepare par :                         //
//          ELIODOR Ednalson Guy Mirlin - P21   //
//          MEDOU Daniel Magloire - P21         //
//                                              //
//**********************************************//

#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <vector>

//Definition des parametres pour la base FP
#define FP_LINE_TRN 320
#define FP_COL_TRN 2001
#define FP_LINE_TEST 160
#define FP_COL_TEST 2001
using namespace std;

//Les Variables Globales
int nombreColonneTrain = 0;
int nombreLigneTrain = 0;
int nombreColonneTest = 0;
int nombreLigneTest = 0;
int nombreDeClasse = 0;

int nombreLigneTrainIris = 0;
int nombreColonneTrainIris = 0;
int nombreLigneTrainLetter = 0;
int nombreColonneTrainLetter = 0;
int nombreLigneTrainOptics = 0;
int nombreColonneTrainOptics = 0;

int nombreLigneTestIris = 0;
int nombreColonneTestIris = 0;
int nombreLigneTestLetter = 0;
int nombreColonneTestLetter = 0;
int nombreLigneTestOptics = 0;
int nombreColonneTestOptics = 0;


//Lecture des donnees a partir des fichiers

float **read_data(string file, string type) {
    int nombreLigne = 0, nombreColonne = 0;
    float **matriceDonnees; //matrice pour stocker les donnees
    ifstream file_reader(file.c_str(), ios::in);
    if (file_reader) // Test d'ouverture de fichier
    {

        //Recuperation des nombres de lignes et colonnes pour chaque fichier
        if (file.compare("data/fp/fp.trn") != 0
                && type.compare("trn") == 0) {
            if(file.compare("data/iris/iris.trn")==0){
                cout<<"\n\n Ouvrir le fichier des.txt du repertoire ayant les fichiers .trn et .tst c'est donc la description de l'ensemble (base d'apprentissage et base de test), cela vous permet de remplir les questions ci-dessous."<<endl;
                cout<<"*************************"<<endl;
                cout<<"\n\n Entrer le nombre d'observation (Nombre de ligne)- base d'apprentissage:"<<endl;
                cout<<"$ ";
                cin>>nombreLigneTrainIris;

                nombreLigneTrain = nombreLigneTrainIris;
                cout<<"Entrer le nombre d'attribut du jeu de donnees (Nombre de colonne):"<<endl;
                cout<<"$ ";
                cin>>nombreColonneTrainIris;
                nombreColonneTrain = nombreColonneTrainIris + 1;


            }else if (file.compare("data/letter/let.trn")==0){
                cout<<"\n\n Ouvrir le fichier des.txt du repertoire ayant les fichiers .trn et .tst c'est donc la description de l'ensemble (base d'apprentissage et base de test), cela vous permet de remplir les questions ci-dessous."<<endl;
                cout<<"*************************"<<endl;
                cout<<"\n\n Entrer le nombre d'observation - base d'apprentissage:"<<endl;
                cout<<"$ ";
                cin>>nombreLigneTrainLetter;
                nombreLigneTrain = nombreLigneTrainLetter;
                cout<<"Entrer le nombre d'attribut - base d'apprentissage :"<<endl;
                cout<<"$ ";
                cin>>nombreColonneTrainLetter;
                nombreColonneTrain = nombreColonneTrainLetter + 1;



            }else if(file.compare("data/optics/opt.trn")==0){
                cout<<"\n\n Ouvrir le fichier des.txt du repertoire ayant les fichiers .trn et .tst c'est donc la description de l'ensemble (base d'apprentissage et base de test) , cela vous permet de remplir les questions ci-dessous."<<endl;
                cout<<"*************************"<<endl;
                cout<<"\n\n Entrer le nombre d'observation - base d'apprentissage:"<<endl;
                cout<<"$ ";
                cin>>nombreLigneTrainOptics;
                nombreLigneTrain = nombreLigneTrainOptics;
                cout<<"Entrer le nombre d'attribut- base d'apprentissage :"<<endl;
                cout<<"$ ";
                cin>>nombreColonneTrainOptics;
                nombreColonneTrain = nombreColonneTrainOptics + 1;

            }

            nombreLigne = nombreLigneTrain;
            nombreColonne = nombreColonneTrain;
        }

        if (file.compare("data/fp/fp.tst") != 0
                && type.compare("tst") == 0) {
            if(file.compare("data/iris/iris.tst")==0){
                cout<<"Entrer le nombre d'observation - base de test:"<<endl;
                cout<<"$ ";
                cin>>nombreLigneTestIris;
                nombreLigneTest = nombreLigneTestIris;
                nombreColonneTest = nombreColonneTrainIris + 1;
                cout<<"************************* \n\n"<<endl;

            }else if (file.compare("data/letter/let.tst")==0){
                cout<<"Entrer le nombre d'observation - base de test:"<<endl;
                cout<<"$ ";
                cin>>nombreLigneTestLetter;
                nombreLigneTest = nombreLigneTestLetter;
                nombreColonneTest = nombreColonneTrainLetter + 1;
                cout<<"*************************\n\n"<<endl;

            }else if(file.compare("data/optics/opt.tst")==0){
                cout<<"Entrer le nombre d'observation - base de test:"<<endl;
                cout<<"$ ";
                cin>>nombreLigneTestOptics;
                nombreLigneTest = nombreLigneTestOptics;
                nombreColonneTest = nombreColonneTrainOptics + 1;
                cout<<"*************************\n\n"<<endl;
            }


            nombreLigne = nombreLigneTest;
            nombreColonne = nombreColonneTest;
        }

        if (file.compare("data/fp/fp.trn") == 0) {
            nombreLigneTrain = FP_LINE_TRN;
            nombreColonneTrain = FP_COL_TRN;
            nombreLigne = nombreLigneTrain;
            nombreColonne = nombreColonneTrain;
        }

        if (file.compare("data/fp/fp.tst") == 0) {
            nombreLigneTest = FP_LINE_TEST;
            nombreColonneTest = FP_COL_TEST;
            nombreLigne = nombreLigneTest;
            nombreColonne = nombreColonneTest;

        }

        // Creation de matrice pour stocker les donnees
        matriceDonnees = new float* [nombreLigne];
        for (int i = 0; i < nombreLigne; i++) {
            matriceDonnees[i] = new float[nombreColonne];
        }

        //Stockage des donnees dans la matrice
        for (int k = 0; k < nombreLigne; k++) {
            for (int l = 0; l < nombreColonne; l++) {
                file_reader >> matriceDonnees[k][l];
            }

        }


        file_reader.close(); // Fermeture du fichier
    } else {
        cerr << "Il y a une erreur dans l'ouverture du fichier !" << endl; //en cas d'echec d'ouverture
    }

    return matriceDonnees;
}

// Distance Euclidienne

float calculDistance(float vector1[], float vector2[]) {

    float dist = 0;
    for (int i = 0; i < nombreColonneTrain - 1; i++) {
        dist += (vector1[i] - vector2[i])*(vector1[i] - vector2[i]);
    }
    dist = sqrt(dist);
    return dist;
}

//distance de Manhattan

float calculDistance_man(float vector1[], float vector2[]) {

    float dist = 0;
    for (int i = 0; i < nombreColonneTrain - 1; i++) {
        dist += fabs((vector1[i] - vector2[i]));
    }
    return dist;
}

//Distance from a vector to all the vectors of a matrix

float** dist_vec_to_set(float** set, float vector[]) {

    float** dist;
    dist = new float*[nombreLigneTrain];
    for (int i = 0; i < nombreLigneTrain; i++) {
        dist[i] = new float[2];
    }

    for (int i = 0; i < nombreLigneTrain; i++) {
        dist[i][0] = i;
        dist[i][1] = calculDistance(set[i], vector);
    }
    return dist;
}

//Comparing two rows

bool compareTwoRows(float* rowA, float* rowB) {
    return (rowA[1] < rowB[1]);
}

//Class prediction by k-means algorithm

float k_means(float** set, float vector[], int k) {

    //distance from a test vector to the trainig set of vector
    float ** tab = dist_vec_to_set(set, vector);

    //sorting of the distance array obtained
    std::sort(tab, tab + nombreLigneTrain, &compareTwoRows);

    //storage of k first results classes
    float* knn;
    knn = new float[k];

    for (int i = 0; i < k; i++) {
        knn[i] = set[(int) tab[i][0]][nombreColonneTrain - 1];
    }
    std::sort(knn, knn + k);

    //Determination of the number of classes
    int * compteur;
    compteur = new int[k];
    for (int i = 0; i < k; i++) {
        compteur[i] = 0;
    }

    for (int i = 0; i < k; i++) {

        compteur[i] = std::count(knn, knn + k, knn[i]);
        i = i + compteur[i] - 1;
    }

    //Determination of the class with the biggest occurence
    int max_index = 0;
    for (int m = 1; m < k; m++) {
        if (compteur[max_index] < compteur[m]) {
            max_index = m;
        }
    }
    float classe = knn[max_index];

    return classe;
}

//computing of the classification performance

float bon_taux(int **conf_mat) {
    float taux = 0;
    float somme_diag = 0;
    float somme_tot = 0;

    //sum of diagonal elements is divided by sum of
    //all the matrix elements
    for (int i = 0; i < nombreDeClasse; i++) {
        for (int j = 0; j < nombreDeClasse; j++) {
            if (i == j) {
                somme_diag += conf_mat[i][j];
            }
            somme_tot += conf_mat[i][j];
        }
    }
    taux = somme_diag / somme_tot;
    return taux;

}

//Hold-out operation

void hold_out() {
    system("sort -R data/fp/fp.data > data/fp/fp.txt");
    system("head -n320 data/fp/fp.txt > data/fp/fp.trn");
    system("tail -n160 data/fp/fp.txt > data/fp/fp.tst");
}

int main(int argc, char** argv) {

    //reading and storage of program's parameters
    char *trn = argv[1];
    char *tst = argv[2];
    char train_file[50] = "";
    strcat(train_file, trn);

    char test_file[50] = "";
    strcat(test_file, tst);
    int k;
    k = atoi(argv[3]);


    float** training;
    float** test;


    //Reading of data from specific base
    string hold_out_file(train_file);
    if (hold_out_file.compare("data/fp/fp.trn") == 0) {
        hold_out();
    }
    training = read_data(train_file, "trn");
    test = read_data(test_file, "tst");

    //Storage of expected classes
    int supposed_classes [nombreLigneTest];
    for (int i = 0; i < nombreLigneTest; i++) {
        supposed_classes[i] = test[i][nombreColonneTest - 1];
    }

    //Determination of number of expected classes
    std::sort(supposed_classes, supposed_classes + nombreLigneTest);
    int compt = 0;
    std::vector<int> classes;
    for (int i = 0; i < nombreLigneTest; i++) {

        compt = std::count(supposed_classes, supposed_classes +
                nombreLigneTest, supposed_classes[i]);
        classes.push_back(supposed_classes[i]);
        i = i + compt - 1;
        nombreDeClasse++;

    }



    //creation of the confusion matrix
    int **confusion_matrix;
    confusion_matrix = new int*[nombreDeClasse];
    for (int j = 0; j < nombreDeClasse; j++) {
        confusion_matrix[j] = new int [nombreDeClasse];
        for (int n = 0; n < nombreDeClasse; n++) {
            confusion_matrix[j][n] = 0;
        }
    }

    //computing of predited classes
    int *prediction;
    prediction = new int[nombreLigneTest];
    for (int i = 0; i < nombreLigneTest; i++) {
        prediction[i] = (int) k_means(training, test[i], k);
    }

    //construction of the confusion matrix
    for (int m = 0; m < nombreLigneTest; m++) {
        int pos1 = std::find(classes.begin(), classes.end(), (int) test[m][nombreColonneTest - 1]) - classes.begin();
        int pos2 = std::find(classes.begin(), classes.end(), (int) prediction[m]) - classes.begin();
        confusion_matrix[pos1][pos2]++;
    }

    //Printing of number of classes, confusion matrix and performance
    cout << "nombre de classes : " << nombreDeClasse << endl;

    for (int a = 0; a < nombreDeClasse; a++) {
        for (int b = 0; b < nombreDeClasse; b++) {

            cout << confusion_matrix[a][b] << " ";
        }
        cout << endl;

    }

    cout << "le taux de précision est :" << bon_taux(confusion_matrix)*100 << "%" << endl;

    return 0;

}

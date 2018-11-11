#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openfile.h"

//conta colunas e linhas para carregar os arquivos de dados
void textSize(FILE *arquivo, int *colunas, int *linhas){
    char *texto;
    texto = (char *)malloc(sizeof(char));
    int c = 0, l = 0;

    for(int i = 0; !feof(arquivo); i++){
        fscanf(arquivo, "%c", &texto[i]);
        if(l==0){
            if(texto[i] == ','){
                c++;
            }
        }
        if(texto[i] == '\n'){
            l++;
        }
        texto = realloc(texto, (i+2)*sizeof(char));
    }
    free(texto);
    rewind(arquivo);

    *colunas = c;
    *linhas = l;
}

//debug apenas. mostra os vetores dos arquivos de dados
void printaMatriz(float **matriz, float *iD, int nColunas, int nLinhas){
    for(int i = 0;  i < nLinhas; i++){
        for(int j = 0; j < nColunas; j++){
            printf("%.2f ", matriz[i][j]); 
        }
        printf("%.0f\n", iD[i]);
    }
}

//pega os dados dos datasets e passa para vetores no programa
void transcribe(FILE *arquivo, float **matrizAmostra, float *rotuloVet, int colunas, int linhas){
    for(int i = 0; !feof(arquivo); i++){
        for(int j = 0; j < colunas; j++){ 
            fscanf(arquivo, "%f,", &matrizAmostra[i][j]);
            if(j==(colunas-1)){
                fscanf(arquivo, "%f", &rotuloVet[i]);
            }
        }
    }
    rewind(arquivo);
}

int countLinhas(FILE *arquivo){
    int charAtual = 0, nLinhas = 1;

    while((charAtual = fgetc(arquivo)) != EOF)
        if(charAtual == 10) nLinhas++;

    rewind(arquivo);
    nLinhas--;  //pois o arquivo quebra linha mais uma vez antes do EOF
    return nLinhas;
}

//conta chars de uma linha especifica
int countChars(FILE *arquivo, int linha){
    int nLinhas = 1, nChars = 0, charAtual = 0;

    rewind(arquivo);

    while((charAtual = fgetc(arquivo)) != EOF){
        if(nLinhas == linha){
            nChars++;
            do{
                nChars++;
            }while((charAtual = getc(arquivo)) != 10);        //10 é \n em int
        }
        if(charAtual == 10) nLinhas++;
    }
    rewind(arquivo);
    return nChars;
}

//remove os \n que a função fgets pega nos vetores de PATH
void tiraQuebra(char *string){
    int tamanho = strlen(string);
    for(int i = 0; i < tamanho; i++){
        if(string[i] == '\n')
            string[i] = '\0';
            
    }
}

//pega os PATHs do config para vetores do programa
Tpaths* setupPaths(FILE *config){
    int sizeTreino = countChars(config, 1) + 1;
    int sizeTeste = countChars(config, 2) + 1;
    int sizePerdicao = countChars(config, 3) + 1;
    //+1 para ter espaço para o \n e \0 da string a ser inserida
    
<<<<<<< HEAD
    char treinoTemp[sizeTreino], testeTemp[sizeTeste], predicaoTemp[sizePerdicao];
=======
    char *treinoTemp = (char*) malloc(sizeTreino * sizeof(char));
    char *testeTemp = (char*) malloc(sizeTeste * sizeof(char));
    char *predicaoTemp = (char*) malloc(sizePerdicao * sizeof(char));
>>>>>>> 9e49fbf4aec3b61927efc018242660c9a10e48d5

    fgets(treinoTemp, sizeTreino, config);
    fgets(testeTemp, sizeTeste, config);
    fgets(predicaoTemp, sizePerdicao, config);

<<<<<<< HEAD
    // tiraQuebra(treinoTemp);
    // tiraQuebra(testeTemp);
    // tiraQuebra(predicaoTemp);

=======
>>>>>>> 9e49fbf4aec3b61927efc018242660c9a10e48d5
    strtok(treinoTemp, "\n");
    strtok(testeTemp, "\n");
    strtok(predicaoTemp, "\n");

    Tpaths *t = (Tpaths*) malloc(sizeof(Tpaths));

    t->pathTreino = (char*) malloc(strlen(treinoTemp) + sizeof(char));
    t->pathTeste = (char*) malloc(strlen(testeTemp) + sizeof(char));
    t->pathPredicao = (char*) malloc(strlen(predicaoTemp) + sizeof(char));

    strcpy(t->pathTreino, treinoTemp);
    strcpy(t->pathTeste, testeTemp);
    strcpy(t->pathPredicao, predicaoTemp);

    return t;
}
    //o ponteiro de STREAM está apontando para o início dos vetores de dados.
    //Final da leitura de PATHs
    //início da leitura dos vetores
<<<<<<< HEAD
=======
void setupAmostra(FILE *config, int nLinhasVetores, Tamostra **amostra){
    int k;
    char tipoDistancia;
    float coefMinkowski;
>>>>>>> 9e49fbf4aec3b61927efc018242660c9a10e48d5

Tamostra* setupAmostras(FILE *config, int linhasVetores){
    
    Tamostra *amostras = (Tamostra*) calloc(linhasVetores, sizeof(Tamostra));

<<<<<<< HEAD
    for(int i = 0; i < linhasVetores; i++){
        fscanf(config, "%d, %c", &(amostras[i]).k, &(amostras[i]).tipoDistancia);
        if((amostras[i]).tipoDistancia == 'M'){
            fscanf(config, ", %f\n", &(amostras[i]).coefMinkowski);
=======
    for(int i = 0; i < nLinhasVetores; i++){
        fscanf(config, "%d, %c", &k, &tipoDistancia);
        if(tipoDistancia == 'M'){
            fscanf(config, ", %f\n", &coefMinkowski);
>>>>>>> 9e49fbf4aec3b61927efc018242660c9a10e48d5
        }else{
            coefMinkowski = 0;
            fgetc(config);
        }

<<<<<<< HEAD
=======
        amostra[i] = novaAmostra(k, tipoDistancia, coefMinkowski);
    }
>>>>>>> 9e49fbf4aec3b61927efc018242660c9a10e48d5

    fclose(config);
    return amostras;
}

// MAIN PARA TESTES E DEBUG
/*void main(){
    FILE *config = fopen("vowels/config.txt", "r");
    int nLinhas = countLinhas(config), nLinhasVetores = nLinhas - 3; //pois as 3 primeiras são paths
    //setupPaths deve ser usado antes de setupAmostras por conta de posição do ponteiro da STREAM
    Tpaths *paths = setupPaths(config);
    Tamostra **amostra = (Tamostra**) malloc(nLinhasVetores * sizeof(Tamostra*));

    setupAmostra(config, nLinhasVetores, amostra);

    printf("\tPATHS\nPath Treino = %s\nPath Testes = %s\nPath Perdicao = %s\n", paths->pathTreino, paths->pathTeste, paths->pathPredicao);

    printf("\n\tVETORES\n");
    for(int i = 0; i < nLinhas - 3; i++){
        printf("K[%i] = %i\t distancia[%i] = %c\t maicozosque[%i] = %f\n", i, amostra[i]->k, i, amostra[i]->tipoDistancia, i, amostra[i]->coefMinkowski);
    }

    free(paths->pathTreino);
    free(paths->pathTeste);
    free(paths->pathPredicao);
    free(paths);
    for(int index = 0; index < nLinhasVetores; index++)
        free(amostra[index]);
    free(amostra);
}
*/
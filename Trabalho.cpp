#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


void merge(int *vetor, int inicio, int meio,int fim){
    int aux[fim-inicio];
    int i = inicio;//inicio
    int j = meio;//meio
    int k = 0;
    while (i < meio && j < fim){
        if(vetor[i] <= vetor[j]) aux[k++] = vetor[i++];
        else aux[k++] = vetor[j++];
            
    }

    while(i < meio) aux[k++] = vetor[i++]; 
    while(j < fim) aux[k++] = vetor[j++]; 

    for (int i = inicio; i < fim; i += 1){
        vetor[i] = aux[i-inicio];
        
    } 
}


void mergeSort(int *vetor, int inicio, int fim){
    if(fim - inicio < 2){ return;}
    int meio = inicio + (fim-inicio)/2;
    mergeSort(vetor, inicio, meio);
    mergeSort(vetor, meio, fim);
    merge(vetor, inicio, meio, fim);
}



int main (int argc, char const* argv[]){

  remove("temp.txt");

  string line; 
  string auxArquivoInicial = "dadosTeste.txt";
  const char* arquivoInicial = auxArquivoInicial.c_str();
	ifstream inFile(arquivoInicial);
  ofstream outFile("temp.txt");

  int vetorOpera[1000];
  int quantAtualVetor = 0;
  int numLinhas = 0;

  // Primeira leva
  while(getline(inFile, line)){
    if(quantAtualVetor < 1000){
      vetorOpera[quantAtualVetor] = stoi(line);
      quantAtualVetor++;
    }else{
      quantAtualVetor = 0;
      mergeSort(vetorOpera, 0, 1000);
      for (int i = 0; i < 1000; ++i){
        outFile << to_string(vetorOpera[i]) << endl;
      }
      vetorOpera[quantAtualVetor] = stoi(line);
      quantAtualVetor++;
    }
    numLinhas++;
  }

  mergeSort(vetorOpera, 0, quantAtualVetor);
  for (int i = 0; i < quantAtualVetor; ++i){
    outFile << to_string(vetorOpera[i]) << endl;
  }
  quantAtualVetor = 0;
  // fim da primeira leva

  //fechando file de condição inicial
  inFile.close();
  outFile.close();
  remove(arquivoInicial);
  rename("temp.txt", arquivoInicial);


  //Calculando o número de vezes que o vetor vai passar
  float calc = (float)(numLinhas / 1000.0);
  int numRuns;
  for (numRuns = 0; calc > 1; numRuns++){
    calc /= 2;
  }

  // Setando variaveis para segunda parte
  int particaoAtual = 1000;
  int estado = 0;
  int countLinhas = 0;
  int restante = 0;
  int aux;
  int quantDeAgrupamentosRestantes;
  int count = 0;
  int primeiraParticao = 1;
  streampos posicaoRetorno;
  streampos posicaoRetornoMedio;
  streampos posicaoRetornoTemp;
  numRuns = 1;
  while(numRuns > 0){
    quantDeAgrupamentosRestantes = particaoAtual / 1000;
    //Abrindo file de condição temporária
    ifstream inFile(arquivoInicial);
    ofstream outFile("temp.txt");
    while(getline(inFile, line)){
      if(estado == 0){
        estado = 1;
      }


      if(quantAtualVetor < 1000){
        if(particaoAtual == 1000 && quantAtualVetor == 999){
          posicaoRetornoMedio = inFile.tellg();
        }
        vetorOpera[quantAtualVetor] = stoi(line);
        quantAtualVetor++;

      }else{

        countLinhas++;
        if(countLinhas == particaoAtual - 1000 && particaoAtual != 1000){
          posicaoRetornoMedio = inFile.tellg();
        }

        int tempLine = stoi(line);
        if(estado == 1 && countLinhas > particaoAtual - 1000){
          if(vetorOpera[quantAtualVetor-1-restante] > tempLine){
            restante += 1;
            if(inFile.peek() == EOF){
              inFile.seekg(posicaoRetornoMedio);
              estado = 2;
              aux = restante;  
              countLinhas = 0;          
            }
          }else{
            inFile.seekg(posicaoRetornoMedio);
            estado = 2;
            aux = restante;  
            countLinhas = 0;
          }
        }else if(estado == 2){
          if(restante == 0){
            mergeSort(vetorOpera, 0, 1000);
            for (int i = 0; i < 1000; ++i){
              outFile << to_string(vetorOpera[i]) << endl;
            }
            estado = 3;
            if(primeiraParticao){
              inFile.seekg(0, ios::beg);
            }else{
              inFile.seekg(posicaoRetorno);
            }
          }else{
            vetorOpera[1000-restante] = tempLine;
            restante--;
          }
          
        }else{
          if((count >= (1000 - aux) && count < 1000) || 
             (count >= (1000 + aux) )){
            if(count < 1000){
              vetorOpera[count - (1000 - aux)] = tempLine;
            }else{
              vetorOpera[count - 1000] = tempLine;
            }

          }
          count++;
          
          if(inFile.peek() == EOF || count == 2000-1){
            mergeSort(vetorOpera, 0, (count - 999));
            for (int i = 0; i < (count - 999); ++i){
              outFile << to_string(vetorOpera[i]) << endl;
            }
            estado = 0;
            quantAtualVetor = 0;
            count = 0;
            aux = 0;
            countLinhas = 0;
            quantDeAgrupamentosRestantes--;
            if(quantDeAgrupamentosRestantes > 0){
              inFile.seekg(posicaoRetornoMedio);
              posicaoRetorno = inFile.tellg();
            }else{
              quantDeAgrupamentosRestantes = particaoAtual / 1000;
            }
            if(primeiraParticao){
              primeiraParticao = 0;
            }
          }

        }

      }
    }



    //fechando file de condição temporária
    inFile.close();
    outFile.close();
    remove(arquivoInicial);
    rename("temp.txt", arquivoInicial);
    particaoAtual *= 2;
    numRuns--;
  }

  
  return 0;
}

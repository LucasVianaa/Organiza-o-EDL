#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


void insertionSort(int *vetor, int tamanho){
    int  troca;
    for (unsigned int i = 1; i < tamanho; i += 1){
        for (int j = i-1; j >= 0;){
            if(vetor[j] > vetor[j+1]){ 
                troca = vetor[j+1];
                vetor[j+1] = vetor[j];
                vetor[j] = troca;
                j--;
            }else{
                break;            
            }
            
        }
    }
}

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

	//ofstream outFile("dados3.txt");
  	fstream readFile("dados3.txt");
	int count = 0;
	int vetor[100];
	//strtol(p, &end, 10)
	string readout;
	string search;
	string replace;
	while(getline(readFile,readout)){
		if(count < 10){
			vetor[count] = atoi(readout.c_str());
			count += 1;
		}
		readFile << readout;
		//outFile << readout;
	}
	for (unsigned int i = 0; i < 10; i += 1)
	{
		printf("%d\n", vetor[i]);
	}
	return 0;
}

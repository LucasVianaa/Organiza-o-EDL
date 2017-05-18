#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<string>
#include <array>

using namespace std;

class Quadrado{
    private:
        int id, lado, area;
    public:
        Quadrado(){
        }
        Quadrado(int id, int lado){
            setId(id);
            setLado(lado);
        }
        void setId(int id){
            this->id = id;        
        }
        void setLado(int lado){
            this->lado = lado;        
            calculaArea();        
        }
        void calculaArea(){
            this->area = this->lado*this->lado;        
        }
        int getId(){
            return this->id;        
        }
        int getLado(){
            return this->lado;        
        }
        void mostraQuadrado(){
            printf("Quadrado #%d\n", this->getId());
            for (unsigned int i = 0; i < this->lado; i += 1){
                for (unsigned int j = 0; j < this->lado; j += 1){
                    printf("* ");
                }
                printf("\n");
            }    
            printf("\n");    
        }
};


void bubbleSort(Quadrado **vetQuad, int tamanho, int* count){
    Quadrado *troca;
    int trocou = 0;
    for (unsigned int i = 0; i < tamanho; i += 1){
        for (unsigned int j = 0; j < tamanho-1; j += 1){
            if(vetQuad[j]->getLado() > vetQuad[j+1]->getLado()){
                troca = vetQuad[j];
                vetQuad[j] = vetQuad[j+1];
                vetQuad[j+1] = troca;
                trocou = 1;            
            }
            *count += 1;
        }
        if(trocou != 0){
            i = 0;
        }
        trocou = 0;
    }
}

void insertionSort(Quadrado **vetQuad, int tamanho, int* count){
    Quadrado *troca;
    for (unsigned int i = 1; i < tamanho; i += 1){
        for (int j = i-1; j >= 0;){
            if(vetQuad[j]->getLado() > vetQuad[j+1]->getLado()){ 
                troca = vetQuad[j+1];
                vetQuad[j+1] = vetQuad[j];
                vetQuad[j] = troca;
                j--;
            }else{
                break;            
            }
            *count += 1;
        }
    }

}

void selectionSort(Quadrado **vetQuad, int tamanho, int* count){
    Quadrado *troca;
    int menorId;
    for (unsigned int i = 0; i < tamanho; i += 1){
        menorId = i;
        for (unsigned int j = i+1; j < tamanho; j += 1){
            if(vetQuad[j]->getLado() <= vetQuad[menorId]->getLado()){ 
                menorId = j;
            }
            *count += 1;
        }
        troca = vetQuad[i];
        vetQuad[i] = vetQuad[menorId];
        vetQuad[menorId] = troca;
    }
}

void merge(Quadrado **vetQuad, int inicio, int meio,int fim, int* count){
    Quadrado *aux[fim-inicio];
    int i = inicio;//inicio
    int j = meio;//meio
    int k = 0;
    while (i < meio && j < fim){
        if(vetQuad[i]->getLado() <= vetQuad[j]->getLado()) aux[k++] = vetQuad[i++];
        else aux[k++] = vetQuad[j++];
        *count += 1;    
    }

    while(i < meio) aux[k++] = vetQuad[i++]; *count += 1;
    while(j < fim) aux[k++] = vetQuad[j++]; *count += 1;

    for (int i = inicio; i < fim; i += 1){
        vetQuad[i] = aux[i-inicio];
        *count += 1;
    } 
}


void mergeSort(Quadrado **vetQuad, int inicio, int fim, int* count){
    if(fim - inicio < 2){ return;}
    int meio = inicio + (fim-inicio)/2;
    mergeSort(vetQuad, inicio, meio, count);
    mergeSort(vetQuad, meio, fim, count);
    merge(vetQuad, inicio, meio, fim, count);
}


void quickSort(Quadrado **vetQuad, int fim, int* count){
	if(fim < 2){ return;}
	int pivot = fim/2;
	Quadrado** menor = (Quadrado**)malloc(sizeof(Quadrado)*fim);
	Quadrado** igual = (Quadrado**)malloc(sizeof(Quadrado)*fim);
	Quadrado** maior = (Quadrado**)malloc(sizeof(Quadrado)*fim);
	int l = 0, m = 0, n = 0;
	
	for (unsigned int i = 0; i < fim; i += 1){
		if(vetQuad[i]->getLado() < vetQuad[pivot]->getLado()){
			menor[l] = vetQuad[i];
			l++;
		}else if(vetQuad[i]->getLado() > vetQuad[pivot]->getLado()){
			maior[n] = vetQuad[i];
			n++;
		}else{
			igual[m] = vetQuad[i];
			m++;
		}
        *count += 1;
	}
	
	if(m == fim){return;}
	
	quickSort(menor, l, count);
	quickSort(maior, n, count);
	
	for (unsigned int i = 0; i < l; i += 1){
		vetQuad[i] = menor[i];
        *count += 1;
	}
	
	for (unsigned int i = 0; i < m; i += 1){
		vetQuad[i+l] = igual[i];
        *count += 1;
	}
	
	for (unsigned int i = 0; i < n; i += 1){
		vetQuad[i+l+m] = maior[i];
        *count += 1;
	}
	
	
}

int binarySearch(Quadrado **vetQuad, int inicio,int fim, Quadrado* quad){
    
    
    int meio = inicio + (fim-inicio)/2;
    if(vetQuad[meio]->getLado() == quad->getLado()){
        return meio;
    }
    if(inicio >= fim){
        return -1;
    }else{
        if(vetQuad[meio]->getLado() < quad->getLado()){
            return binarySearch(vetQuad, meio+1, fim, quad);
        }else{
            return binarySearch(vetQuad, inicio, meio-1, quad);
        }    
    }
}

void copyQuadArrays(Quadrado **vetQuad, Quadrado **clone, int tamanho){
    for (unsigned int i = 0; i < tamanho; i += 1){
        clone[i] = new Quadrado();
        clone[i] = vetQuad[i];
    }
}
int main (int argc, char const* argv[]){
	
	return 0;
}
/*
int main (int argc, char const* argv[]){
    //Declarações    
    int number = 10;
    // Abrindo file
    string titulo = "Analise melhor caso.csv";
    string firstLine = "Merge;Quick;Bubble;Select;Insert";
    ofstream outputFile;
    outputFile.open(titulo);
    outputFile << firstLine << endl;
    
    do{
        int count = 0;
        string line = "";
        srand (time(NULL));
        Quadrado *vetQuad[number];
        Quadrado *clone[number];
        clock_t t;                    
        
        //Instanciando a array
        for (unsigned int i = 0; i < number; i += 1){
            vetQuad[i] = new Quadrado(i, i);
        }
        
        copyQuadArrays(vetQuad, clone, number);
        
        //Executando os metodos e pegando os dados    
        //Merge
        t = clock(); 
        mergeSort(clone, 0, number, &count);
        t = clock() - t;
        line += to_string(count) + " / " + to_string(((float)t)/CLOCKS_PER_SEC) + ";";
        count = 0;
        copyQuadArrays(vetQuad, clone, number);
        
        //Quick
        t = clock(); 
        quickSort(clone, number, &count);
        t = clock() - t;
        line += to_string(count) + " / " + to_string(((float)t)/CLOCKS_PER_SEC) + ";";
        count = 0;
        copyQuadArrays(vetQuad, clone, number);
        
        //Bubble
        t = clock(); 
        bubbleSort(clone, number, &count);
        t = clock() - t;
        line += to_string(count) + " / " + to_string(((float)t)/CLOCKS_PER_SEC) + ";";
        count = 0;
        copyQuadArrays(vetQuad, clone, number);
        
        //Selection
        t = clock(); 
        selectionSort(clone, number, &count);
        t = clock() - t;
        line += to_string(count) + " / " + to_string(((float)t)/CLOCKS_PER_SEC) + ";";
        count = 0;
        copyQuadArrays(vetQuad, clone, number);
        
        //Insert
        t = clock(); 
        insertionSort(clone, number, &count);
        t = clock() - t;
        line += to_string(count) + " / " + to_string(((float)t)/CLOCKS_PER_SEC) + ";";
        count = 0;
        


        //Escrevendo no arquivo
        outputFile << line << endl;
        
        number++;
    }while(number < 1000);
    
    outputFile.close();

    return 0;
}*/

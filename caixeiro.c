#include <stdio.h>
#include <stdlib.h>

//verifica se a cidade está na lista de visitados
int verifica(int a,int v[], int m){
    int i;
    for (i = 0; i < m; i++)
    {
        if (v[i] == a)
        {
            //printf("existe %d \n", a);
            return 1;
        }
        
    }
    //printf("não existe %d \n", a);
    return 0;

}
//adiciona a cidade a lista de visitados
void adiciona(int a,int v[], int m){
    int i;
    for (i = 0; i < m; i++)
    {
        if (v[i] == -1)
        {
            v[i] = a;
            // printf("adicionado %d \n", a);
            break;
        }
        
    }
}


int main(int argc, char const *argv[])
{
    FILE *fp;
    int max, i, b, j, **m, atual = 0, total = 0, menor, prox, *vet, ver = 0, k = 0;
    fp = fopen("grafo.tsp", "r");
    //le o tamanho da matrix do arquivo tsp
    fscanf(fp, "%d", &max);
    // printf("%d\n", max);
    //aloca a memoria da matriz e do vetor de visitados
    //-------------------------------
    m = malloc(max * sizeof (int*));
    vet = malloc(max * sizeof (int*));
    for ( i = 0; i < max; i++)
    {
        m[i] = malloc(max * sizeof (int));
    }
    //-------------------------------
    //adiciona a primeira cidade na lista de visitados
    vet[0] = 0;
    //preenche a lista de visitados com -1 simbolizando que estão vazias
    //-------------------------------
    for ( i = 1; i < max; i++)
    {
        vet[i] = -1;
    }
    //-------------------------------
    //recolhe as informações da matriz do arquivo tsp
    //-------------------------------
    for ( i = 0; i < max; i++)
    {
        for ( j = 0; j < max; j++)
        {
            fscanf(fp, "%d", &b);
            //printf("%3d ", b);
            m[i][j] = b;
            
        }
        //printf("\n");
    }
    //-------------------------------
    //o for ira até o caixeiro chegar na ultima cidade antes de retornar até a inicial
    for (j = 0; j < max-1; j++)
    {
        //exibe lista de visitados
        //-------------------------------
        printf("(");
        for ( k = 0; k < max; k++)
        {
            printf("%d ", vet[k]);
        }
        printf(")\n");
        //-------------------------------
        //inicializa com um numero grande como sendo menor para que seja escolhido em seguida um valor da matriz
        menor = 1000;
        printf("atual: %d\n", atual);
        for ( i = 0; i < max; i++)
        {
            //printf("if (%d< %d && %d != %d)\n", m[atual][i], menor, i, atual);
            //verifica se a distacia a cidade até o vizinho seja menor que o menor determinado anteriormente
            if (m[atual][i] < menor && i != atual)
            {
                //verifica se ja foi visitado
                if (verifica(i, vet, max) == 0)
                {
                    //determina qual o menor, que sera o proximo destino
                    menor = m[atual][i];
                    prox = i;
                }
                
                
            }
            
        }
        //o menor é adicionado na lista de visitador e sera o proximo destino
        adiciona(prox, vet, max);
        //adiciona a distancia no total percorrido
        total += menor;
        atual = prox;
        printf("proximo: %d\n", atual);
        
    }
    //adiciona a distancia da ultima cidade visitada até a cidade inicial
    total+=m[atual][0];
    //exibe total percorrido
    printf("total: %d\n", total);
    //libera memoria alocada
    //-------------------------------
    for ( i = 0; i < max; i++)
    {
        free(m[i]);
    }
    free(m);
    free(vet);
    //-------------------------------

    return 0;
}

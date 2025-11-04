#include <stdio.h>
#include <stdlib.h> 


//DEFINIR CONSTANTES

// Define o tamanho do tabuleiro principal
#define tamanhoTabuleiro 10
// Define o tamanho fixo dos navios
#define tamanhoNavio 3
// Define o tamanho das matrizes de habilidade
#define tamanhoHabilidade 5

// Define os valores para representar cada elemento no tabuleiro
#define agua 0
#define navio 3
#define efeitoHabilidade 5

//FUNÇÕES AUXILIARES

void inicializarTabuleiro(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro]);
void exibirTabuleiro(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro]);
int posicionarNavio(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro], int linha, int coluna, int tamanho, char orientacao);
void gerarMatrizHabilidade(int matriz[tamanhoHabilidade][tamanhoHabilidade], char tipo);
void aplicarHabilidade(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro], int hab_matriz[tamanhoHabilidade][tamanhoHabilidade], int origem_linha, int origem_coluna);

//FUNÇÃO PRINCIPAL                       
int main() {
    int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro];

    inicializarTabuleiro(tabuleiro);

    // =========================================================================
    // ETAPA 1 e 2: POSICIONANDO NAVIOS (NÍVEIS NOVATO E INTERMEDIÁRIO)
    // =========================================================================
    printf("===POSICIONANDO NAVIOS NO TABULEIRO===\n");
    printf("Posicionando 4 navios de tamanho %d...\n\n", tamanhoNavio);

    // Posiciona 4 navios com validação: 1 horizontal, 1 vertical, 2 diagonais
    posicionarNavio(tabuleiro, 1, 1, tamanhoNavio, 'H');
    posicionarNavio(tabuleiro, 3, 8, tamanhoNavio, 'V');
    posicionarNavio(tabuleiro, 5, 1, tamanhoNavio, 'D'); 
    posicionarNavio(tabuleiro, 1, 8, tamanhoNavio, 'S'); 

    printf("===Tabuleiro com Navios Posicionados===\n");
    exibirTabuleiro(tabuleiro);
    printf("\n");

    // =========================================================================
    // ETAPA 3: HABILIDADES ESPECIAIS E ÁREAS DE EFEITO (NÍVEL AVANÇADO)
    // =========================================================================
    printf("===APLICANDO HABILIDADES ESPECIAIS===\n\n");

    // Declara as matrizes para cada habilidade
    int matrizCone[tamanhoHabilidade][tamanhoHabilidade];
    int matrizCruz[tamanhoHabilidade][tamanhoHabilidade];
    int matrizOctaedro[tamanhoHabilidade][tamanhoHabilidade];

    // Gera as formas das habilidades usando loops e condicionais
    gerarMatrizHabilidade(matrizCone, 'N');    
    gerarMatrizHabilidade(matrizCruz, 'C');     
    gerarMatrizHabilidade(matrizOctaedro, 'O'); 

    // Define pontos de origem no tabuleiro principal para cada habilidade
    // e aplica o efeito no tabuleiro.
    aplicarHabilidade(tabuleiro, matrizCone, 3, 3);
    aplicarHabilidade(tabuleiro, matrizCruz, 7, 6);
    aplicarHabilidade(tabuleiro, matrizOctaedro, 0, 6);

    printf("===Tabuleiro Final com Habilidades Aplicadas===\n\n");
    printf("Legenda: %d = Agua | %d = Navio | %d = Area de Efeito\n", agua, navio, efeitoHabilidade);
    exibirTabuleiro(tabuleiro);

    return 0;
}

//FUNÇÕES AUXILIARES

void inicializarTabuleiro(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro]) {
    for (int i = 0; i < tamanhoTabuleiro; i++) {
        for (int j = 0; j < tamanhoTabuleiro; j++) {
            tabuleiro[i][j] = agua;
        }
    }
}

void exibirTabuleiro(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro]) {
    for (int i = 0; i < tamanhoTabuleiro; i++) {
        for (int j = 0; j < tamanhoTabuleiro; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicionarNavio(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro], int linha, int coluna, int tamanho, char orientacao) {
    //Etapa 1: Validação
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'S') { l += i; c -= i; }

        //Verifica se está fora dos limites do tabuleiro
        if (l < 0 || l >= tamanhoTabuleiro || c < 0 || c >= tamanhoTabuleiro) {
            printf("Erro: Navio na orientacao '%c' saindo do tabuleiro em (%d, %d).\n", orientacao, linha, coluna);
            return 0;
        }
        //Verifica se a posição já está ocupada (sobreposição)
        if (tabuleiro[l][c] != agua) {
            printf("Erro: Sobreposicao de navio em (%d, %d).\n", l, c);
            return 0;
        }
    }

    //Etapa 2: Posicionamento
    //Se passou na validação, posiciona o navio
    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') tabuleiro[linha][coluna + i] = navio;
        else if (orientacao == 'V') tabuleiro[linha + i][coluna] = navio;
        else if (orientacao == 'D') tabuleiro[linha + i][coluna + i] = navio;
        else if (orientacao == 'S') tabuleiro[linha + i][coluna - i] = navio;
    }
    return 1;
}


void gerarMatrizHabilidade(int matriz[tamanhoHabilidade][tamanhoHabilidade], char tipo) {
    int centro = tamanhoHabilidade / 2;

    for (int i = 0; i < tamanhoHabilidade; i++) {
        for (int j = 0; j < tamanhoHabilidade; j++) {
            matriz[i][j] = 0; 
            switch (tipo) {
                case 'C': 
                    if (i == centro || j == centro) matriz[i][j] = 1;
                    break;
                case 'O': 
                    if (abs(i - centro) + abs(j - centro) <= centro) matriz[i][j] = 1;
                    break;
                case 'N': 
                    if (i >= centro && abs(j - centro) <= (i - centro)) matriz[i][j] = 1;
                    break;
            }
        }
    }
}


void aplicarHabilidade(int tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro], int hab_matriz[tamanhoHabilidade][tamanhoHabilidade], int origem_linha, int origem_coluna) {
    int centro = tamanhoHabilidade / 2;

    for (int i = 0; i < tamanhoHabilidade; i++) {
        for (int j = 0; j < tamanhoHabilidade; j++) {
            if (hab_matriz[i][j] == 1) {
                // Calcula a coordenada correspondente no tabuleiro principal
                int linha_alvo = origem_linha - centro + i;
                int coluna_alvo = origem_coluna - centro + j;

                // Valida se a coordenada alvo está dentro dos limites do tabuleiro
                if (linha_alvo >= 0 && linha_alvo < tamanhoTabuleiro &&
                    coluna_alvo >= 0 && coluna_alvo < tamanhoTabuleiro) {
                    
                    // Aplica o efeito apenas se a posição for água
                    if (tabuleiro[linha_alvo][coluna_alvo] == agua) {
                        tabuleiro[linha_alvo][coluna_alvo] = efeitoHabilidade;
                    }
                }
            }
        }
    }
}
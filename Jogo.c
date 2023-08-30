#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void exibirForca(int erros) {   //DESENHA A FORCA E O BONECO PALITO DE ACORDO COM OS ERROS
    printf("  ____\n");
    printf("  |  |\n");
    printf("  |  %s\n", erros >= 1 ? "O" : "");
    printf("  | %s%s%s\n", erros >= 3 ? "/" : "", erros >= 2 ? "|" : "", erros >= 4 ? "\\" : "");
    printf("  | %s %s\n", erros >= 5 ? "/" : "", erros >= 6 ? "\\" : "");
    printf("__|_____\n");
}

void salvarPalavrasEmArquivo(char *palavras[], int numPalavras) {
    FILE *arquivo = fopen("palavras.txt", "w"); //FOPEN ABRE UM ARQUIVO E W CRIA UM ARQUIVO VAZIO
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < numPalavras; i++) {
        fprintf(arquivo, "%s\n", palavras[i]);
    }

    fclose(arquivo); //FECHA O ARQUIVO
}

int main() {
    char *palavras[100];
    int numPalavras = 0;

    FILE *arquivo = fopen("palavras.txt", "r"); //FOPEN R ABRE O ARQUIVO SOMENTE PRA LEITURA
    if (arquivo != NULL) {
        char buffer[100];
        while (fgets(buffer, sizeof(buffer), arquivo) != NULL) { //FGETS OBTEM UMA STRING DO ARQUIVO E SIZEOF OBTEM O TAMANHO
            buffer[strlen(buffer) - 1] = '\0'; // REMOVE O CARACTER DA NOVA LINHA
            palavras[numPalavras] = malloc(strlen(buffer) + 1); //MALLOC DEFINE O TAMANHO
            strcpy(palavras[numPalavras], buffer); //
            numPalavras++;
        }
        fclose(arquivo);
    }

    int jogarNovamente = 1;

    while (jogarNovamente) {
        srand(time(NULL)); // GERA NUMEROS ALEATORIOS PRA SELECIONAR UMA PALAVRA
        int indicePalavra = rand() % numPalavras;
        char *palavra = palavras[indicePalavra];
        int tamanho = strlen(palavra);
        char palpite;
        int erros = 0; //DEFINI OS ERROS PARA 0

        int letrasDescobertas[tamanho];
        for (int i = 0; i < tamanho; i++) {
            letrasDescobertas[i] = 0;
        }

        while (erros < 6) {
            printf("\nPalavra: ");
            for (int i = 0; i < tamanho; i++) {
                if (letrasDescobertas[i]) {
                    printf("%c ", palavra[i]);
                } else {
                    printf("_ ");
                }
            }

            printf("\n");
            exibirForca(erros);

            printf("Digite uma letra maiúscula: ");
            scanf(" %c", &palpite);

            if (!isupper(palpite)) {
                printf("Por favor, insira apenas letras maiúsculas.\n");
                continue;
            }

            int letraEncontrada = 0;
            for (int i = 0; i < tamanho; i++) {
                if (palavra[i] == palpite && !letrasDescobertas[i]) {
                    letrasDescobertas[i] = 1;
                    letraEncontrada = 1;
                }
            }

            if (!letraEncontrada) {
                erros++;
            }

            int acertos = 0;
            for (int i = 0; i < tamanho; i++) {
                if (letrasDescobertas[i]) {
                    acertos++;
                }
            }

            if (acertos == tamanho) {
                printf("\nParabéns! Você adivinhou a palavra: %s\n", palavra);
                break;
            }
        }

        if (erros == 6) { //SE OS ERROS FOREM IGUAIS A 6, MENSAGEM DE DERROTA
            printf("\nSuas chances acabaram. A palavra era: %s\n", palavra);
        }

        printf("Deseja jogar novamente? (1 para Sim, 0 para Não): "); //PERGUNTAR SE QUER JOGAR NOVAMENTE
        scanf("%d", &jogarNovamente);

        system("clear || cls"); //LIMPA A TELA EM LINUX E WINDOWS
    }

    printf("Deseja inserir novas palavras? (1 para Sim, 0 para Não): "); //INSERIR NOVA PALAVRA
    int inserirNovasPalavras;
    scanf("%d", &inserirNovasPalavras);

    if (inserirNovasPalavras) {
        printf("Quantas palavras você deseja adicionar? "); //DEFINE QUANTAS PALAVRAS QUER ADICIONAR
        int numNovasPalavras;
        scanf("%d", &numNovasPalavras);

        for (int i = 0; i < numNovasPalavras; i++) {
            printf("Digite a nova palavra %d: ", i + 1);
            char novaPalavra[100];
            scanf("%s", novaPalavra);

            palavras[numPalavras] = malloc(strlen(novaPalavra) + 1);
            strcpy(palavras[numPalavras], novaPalavra);
            numPalavras++;
        }

        salvarPalavrasEmArquivo(palavras, numPalavras);
        printf("Palavras inseridas com sucesso!\n");
    }

    for (int i = 0; i < numPalavras; i++) {
        free(palavras[i]);
    }

    printf("Obrigado por jogar!\n");

    return 0;
}

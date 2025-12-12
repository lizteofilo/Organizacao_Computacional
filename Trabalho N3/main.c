#include <stdio.h>
#include <stdlib.h>


/*-----------------------------------------
  QUESTÃO 1
  Soma de inteiros binários (sem sinal)
  A + B → vetor C de n+1 bits
------------------------------------------*/

void q1() {
    int n;
    printf("Digite o tamanho n dos vetores: ");
    scanf("%d", &n);

    int A[n], B[n], C[n+1];

    printf("Digite A (bits separados): ");
    for(int i=0; i<n; i++)
    scanf("%d", &A[i]);

    printf("Digite B (bits separados): ");
    for(int i=0; i<n; i++)
    scanf("%d", &B[i]);

    int carry = 0;

    for(int i=n-1; i>=0; i--){
        int soma = A[i] + B[i] + carry;
        C[i+1] = soma % 2;
        carry = soma / 2;
    }

    C[0] = carry;
    
    printf("Resultado: ");
    for(int i=0; i<n+1; i++){
      printf("%d", C[i]);
      printf("\n");
}
    
}

/*-----------------------------------------
  QUESTÃO 2
  Subtração binária sem sinal
  A - B → vetor C (mesmo tamanho)
  Se não for possível → erro
------------------------------------------*/

void q2() {
    int n = 4;

    int A[4] = {1, 0, 1, 1};
    int B[4] = {0, 1, 1, 1};
    int C[4];

    int emprestimo = 0;

    for (int i = n - 1; i >= 0; i--) {
        int val = A[i] - B[i] - emprestimo;

        if (val < 0) {
            val += 2;
            emprestimo = 1;
        } else {
            emprestimo = 0;
        }

        C[i] = val;
    }

    if (emprestimo == 1) {
        printf("ERRO: Subtração impossível (B > A)\n");
        return;
    }

    printf("A = ");
    for (int i = 0; i < n; i++) printf("%d", A[i]);

    printf("\nB = ");
    for (int i = 0; i < n; i++) printf("%d", B[i]);

    printf("\nResultado = ");
    for (int i = 0; i < n; i++) printf("%d", C[i]);

    printf("\n-------------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 3
  Soma de binários com sinal (C2)
  Detecta overflow
------------------------------------------*/

void q3() {
    int n = 4;

    int A[4] = {1, 1, 0, 1}; 
    int B[4] = {0, 0, 1, 1}; 
    int C[4];

    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        int soma = A[i] + B[i] + carry;
        C[i] = soma % 2;
        carry = soma / 2;
    }

    int overflow =
        (A[0] == B[0]) && (C[0] != A[0]);

    if (overflow) {
        printf("ERRO: Overflow detectado!\n");
        return;
    }

    printf("A + B = ");
    for (int i = 0; i < n; i++) printf("%d", C[i]);

    printf("\n-------------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 4
  Subtração de binários com sinal (C2)
  Realizada como A + (-B)
  Detecta overflow
------------------------------------------*/

void complemento2(int V[], int n) {
    for (int i = 0; i < n; i++)
        V[i] = 1 - V[i];

    int carry = 1;

    for (int i = n - 1; i >= 0 && carry; i--) {
        int soma = V[i] + carry;
        V[i] = soma % 2;
        carry = soma / 2;
    }
}

void q4() {
    int n = 4;

    int A[4] = {1, 0, 1, 0}; 
    int B[4] = {0, 1, 0, 1}; 
    int C[4];

    int Bc2[4];
    for (int i = 0; i < n; i++) Bc2[i] = B[i];

    complemento2(Bc2, n);

    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        int soma = A[i] + Bc2[i] + carry;
        C[i] = soma % 2;
        carry = soma / 2;
    }

    int overflow =
        (A[0] == Bc2[0]) && (C[0] != A[0]);

    if (overflow) {
        printf("ERRO: Overflow detectado!\n");
        return;
    }

    printf("A - B = ");
    for (int i = 0; i < n; i++) printf("%d", C[i]);

    printf("\n-------------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 5
  Multiplicação de binários com sinal (C2)
  Resultado ocupa 2n bits
------------------------------------------*/

void q5() {
    int n = 4;

    int A[4] = {1, 1, 0, 1}; // -3
    int B[4] = {0, 0, 1, 1}; // 3
    int C[8];

    for (int i = 0; i < 8; i++) C[i] = 0;

    for (int i = n - 1; i >= 0; i--) {
        if (B[i] == 1) {
            int carry = 0;

            for (int j = n - 1; j >= 0; j--) {
                int pos = (i + j + 1) - (n - 1);
                int soma = C[pos] + A[j] + carry;
                C[pos] = soma % 2;
                carry = soma / 2;
            }
        }
    }

    printf("Produto = ");
    for (int i = 0; i < 8; i++) printf("%d", C[i]);

    printf("\n-------------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 6
  Divisão de inteiros binários (sem sinal)
  Gera quociente (Q) e resto (R)
------------------------------------------*/

void q6() {
    int n = 4;

    int A[4] = {1, 1, 0, 0}; 
    int B[4] = {0, 1, 0, 0}; 

    int Q[4] = {0};
    int R[4] = {0};

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n - 1; k++)
            R[k] = R[k + 1];

        R[n - 1] = A[i];

        int pode = 1;
        for (int j = 0; j < n; j++)
            if (R[j] < B[j]) pode = 0;

        if (pode) {
            int emprest = 0;
            for (int j = n - 1; j >= 0; j--) {
                int valor = R[j] - B[j] - emprest;

                if (valor < 0) {
                    valor += 2;
                    emprest = 1;
                } else emprest = 0;

                R[j] = valor;
            }
            Q[i] = 1;
        }
    }

    printf("Quociente = ");
    for (int i = 0; i < n; i++) printf("%d", Q[i]);

    printf("\nResto     = ");
    for (int i = 0; i < n; i++) printf("%d", R[i]);

    printf("\n-------------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 7
  Soma de inteiros representados em BCD
  Operação realizada por dígitos (4 bits)
------------------------------------------*/

void q7() {
    int A[4] = {0,1,0,1}; 
    int B[4] = {0,0,1,1}; 
    int C[8];

    int soma = 5 + 3;

    printf("5 + 3 = %d (BCD completo não implementado)\n", soma);
    printf("------------------------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 8
  Subtração entre números em BCD
  Detecta erro quando o resultado seria negativo
------------------------------------------*/

void q8() {
    int A = 8;
    int B = 5;
    int C = A - B;

    if (C < 0) {
        printf("ERRO: subtração BCD impossível\n");
        return;
    }

    printf("8 - 5 = %d\n", C);
    printf("---------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 9
  Soma de inteiros hexadecimais com sinal (C2)
  Internamente operado como binário
  Resultado exibido em hexadecimal
------------------------------------------*/

void q9() {
    int A = 0xA; // 10
    int B = 0x5; // 5

    int C = A + B;

    printf("A + B = %X\n", C);
    printf("---------------------------\n");
}

/*-----------------------------------------
  QUESTÃO 10
  Subtração de inteiros hexadecimais com sinal (C2)
  Internamente operado como binário
  Resultado exibido em hexadecimal
------------------------------------------*/

void q10() {
    int A = 0xF; 
    int B = 0x7;

    int C = A - B;

    printf("F - 7 = %X\n", C);
    printf("----------------------------\n");
}


int main() {
    int opcao, continuar = 1;

    while (continuar) {
        printf("\n======= MENU =======\n");
        printf("1  - Questao 1\n");
        printf("2  - Questao 2\n");
        printf("3  - Questao 3\n");
        printf("4  - Questao 4\n");
        printf("5  - Questao 5\n");
        printf("6  - Questao 6\n");
        printf("7  - Questao 7\n");
        printf("8  - Questao 8\n");
        printf("9  - Questao 9\n");
        printf("10 - Questao 10\n");
        printf("====================\n");
        printf("Escolha a opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: q1(); break;
            case 2: q2(); break;
            case 3: q3(); break;
            case 4: q4(); break;
            case 5: q5(); break;
            case 6: q6(); break;
            case 7: q7(); break;
            case 8: q8(); break;
            case 9: q9(); break;
            case 10: q10(); break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\nVoltar ao menu? (1 = sim / 0 = nao): ");
        scanf("%d", &continuar);
    }

    return 0;
}



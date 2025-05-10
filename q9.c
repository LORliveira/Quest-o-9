#include <stdio.h>

// Calcula o MDC usando o algoritmo de Euclides
int mdc(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

// Verifica se dois números são coprimos
int coprimos(int a, int b) {
    return mdc(a, b) == 1;
}

// Retorna o inverso modular
int inverso_modular(int g, int n, int *inverso) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = g;
    while (novo_r != 0) {
        int quociente = r / novo_r;
        int aux = novo_t;
        novo_t = t - quociente * novo_t;
        t = aux;

        aux = novo_r;
        novo_r = r - quociente * novo_r;
        r = aux;
    }
    if (r > 1) return 0;
    if (t < 0) t += n;
    *inverso = t;
    return 1;
}

// Exponenciação modular
int pot_m(int base, int expoente, int modulo) {
    int resultado = 1;
    base %= modulo;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % modulo;
        base = (base * base) % modulo;
        expoente /= 2;
    }
    return resultado;
}

// Ve se um número é primo
int primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

// Calcula a função de Euler
int quoci(int n) {
    int resultado = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            resultado -= resultado / i;
        }
    }
    if (n > 1)
        resultado -= resultado / n;
    return resultado;
}

int main() {
    int H, G, n, x, n1;

    printf("Coloque H, G, n, x e n₁ (ex: 38 79 252 117 101): ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    printf("\n 1: se G e n são coprimos: \n");
    if (!coprimos(G, n)) {
        printf("G = %d e n = %d não são coprimos. A divisão modular não da.\n", G, n);
        
        return 1;
    }
    printf("G = %d e n = %d são coprimos.\n", G, n);

    printf("\n 2: O inverso de G em Z_%d ==\n", n);
    int G_inv;
    if (!inverso_modular(G, n, &G_inv)) {
        printf("Não tem inverso modular de G = %d em Z_%d.\n", G, n);
        return 1;
    }
    printf("Inverso de G é: %d\n", G_inv);

    printf("\n 3: Calculando a = H * G⁻¹ mod n ==\n");
    int a = (H * G_inv) % n;
    printf("Result: a = %d\n", a);

    printf("\n 4: a e n₁ são coprimos:\n");
    if (!coprimos(a, n1)) {
        printf("a = %d e n₁ = %d não são coprimos.\n", a, n1);
    } else {
        printf("a = %d e n₁ = %d são coprimos.\n", a, n1);
    }

    printf("\n 5: Se n₁ = %d é primo ==\n", n1);
    int x1;
    if (primo(n1)) {
        x1 = n1 - 1;
        printf("n₁ é primo. Teorema de Fermat: %d\n", x1);
    } else {
        x1 = quoci(n1);
        printf("n₁ não é primo. Teorema de Euler: %d\n", x1);
    }

    printf("\n 6: x = %d em x = x₁ * q + r:\n", x);
    int q = x / x1;
    int r = x % x1;
    printf("q: %d, r: %d\n", q, r);

    printf("\n 7: Calculando potências:\n");
    int x2 = pot_m(a, x1, n1);
    int x2q = pot_m(x2, q, n1);
    int ar = pot_m(a, r, n1);

    printf("a^x₁ mod n₁:  %d\n", x2);
    printf("x₂^q mod n₁: %d\n", x2q);
    printf("a^r mod n₁: %d\n", ar);

    printf("\n 8: Calculando resultado final: \n");
    int resultado = (x2q * ar) % n1;
    printf("Resultado final: %d\n", resultado);

    return 0;
}

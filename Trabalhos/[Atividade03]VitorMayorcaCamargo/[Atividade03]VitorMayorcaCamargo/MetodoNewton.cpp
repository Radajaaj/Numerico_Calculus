#include <thread>
#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>

using namespace std;

//Bissecção: ponto, dentro de um intervalo [a, b], aonde uma função f(x) = 0
    //Nota2 Podemos usar isso para calcular a raiz quadrada de qualquer numero

float fx(float a, int b, float c, float x){ //Essa função apenas calcula o valor de f(x), aonde f(X) = aX^b + c
    float resultado = 1.0; //Para o caso de b == c == 0
    for(int i = 0; i < b; i++){//Multiplicações sucessivas, vai calcular o x^b
        resultado = resultado * x;
    }
    resultado = resultado * a;
    resultado = resultado + c;

    //cout << "\nResulta em " << resultado << endl;
    return resultado;
}

float fdx(float a, int b, float c, float x){ // Calcula o valor da derivada da funcao inserida, onde f(X) = aX^b + c
    //Metodo do tombamento
    c = 0;
    a = a * b;
    b = b - 1;
    float resultado = 1;
    for(int i = 0; i < b; i++){//Multiplicações sucessivas, vai calcular o x^b
        resultado = resultado * x;
    }
    resultado = resultado * a;
    //cout << "\nResulta em " << resultado << endl;
    return resultado;
}

float modulo(float f){
    if(f < 0){ //Tiramos modulo
        f = f * (-1);
    }
    return f;
}

double calculaprecisao(int Eprecisao){ //retorno == 10^(-Eprecisao)
//Esta função simplesmente converte o valor de precisao inserido pelo usuario [10^(-x)] em um numero real [0,000...01]
    double d = 1.0;

    for(int i = 0; i < Eprecisao; i++){
        d = d * 1/10;
    }
    return d;
}

int main(){
   float aFunc, cFunc, X0, X1;
   double precisao;
   int Eprecisao, No, op = 0, bFunc;
    
    // Abaixo, o usuário será capaz de inserir os valores de 'a', 'b' e 'c' para a função genérica f(X) = aX^b + c
    do{
        cout << "\n=--=--= Dada a Funcao:\n\tf(x) = aX^b + c\n\n=-= Insira 'a', 'b' e 'c'." << endl;
        cout << "Insira 'a' (numero real)\n-R: ";
        cin  >> aFunc;
        cout << "Insira 'b' (numero inteiro)\n-R: ";
        cin  >> bFunc;
        cout << "Insira 'c' (numero real)\n-R: ";
        cin  >> cFunc;

        do{
            cout << "\n=-= A funcao a ser avaliada eh\n\tf(x) = " << aFunc << "X^(" << bFunc;
            if(cFunc > 0){
                cout << ") + " << cFunc << endl;
            }else if(cFunc < 0){
                cout << ") - " << modulo(cFunc) << endl;
            }else{
                cout << ")" << endl;
            }
            
            
             
            cout << "=- Isso esta correto?\n[1] Sim\n[0] Nao\n-R: ";
            cin  >> op;
            if(op != 1 && op != 0){
                cout << endl << "Opcao invalida! Tente de novo" << endl;
            }
        }while(op != 1 && op != 0);
    }while(op != 1);

    // Abaixo, o usuário irá definir a precisão e o número máximo de iterações a serem calculados
    do{
        cout << endl << "=--=--= O valor de precisao eh notado como E = 10^(-x);" << endl;
        cout << "=-= Insira o valor de x (numero inteiro, menor que 318)\n-R: "; 
        //REVISAR ESSE LIMITE DEPOIS
        cin  >> Eprecisao;

        No = 1000;
        do{
            cout << "\n=--= Agora, insira o numero maximo de iteracoes que serao calculadas, caso a interseccao exata nao seja encontrada (numero inteiro positivo diferente de 0)\n-R: ";
            cin  >>  No;
            if(No < 0){
                cout << endl << "-=- O numero que voce inseriu eh menor que 1! Tente de novo." << endl;
            }
        }while(No < 1);
        precisao = calculaprecisao(Eprecisao);
        do{

            cout << "\n\n=-= A precisao eh E = 10^(-" << Eprecisao << "), ou " << precisao << endl;
            //printf("\n %lf \n", (precisao * 100000000));
            cout << "=-= Serao calculadas " << No << " iteracoes" << endl;
            cout << "\n=- Isso esta certo?\n[1] Sim\n[0] Nao\n-R: ";
            cin  >> op;
            if(op != 1 && op != 0){
                cout << endl << "\t-- Opcao invalida! Tente de novo --" << endl;
            }
        }while(op != 1 && op != 0);
    }while(op != 1);

    // Por fim, o usuário vai decidir o ponto inicial a ser analisado!

    do{
        do{
            cout << "\n\n\n=--=--= Por fim, Faremos nosso calculo a partir de um ponto X0;" << endl;
            cout << "\n=--= Insira o valor de 'X0' (numero real)\n-R: ";
            cin  >> X0;
            //cout << "=--= Insira o valor de 'b' (numero real)\n-R: ";
            //cin  >> bIntervalo;

            do{
                cout << "\n\n=-= X0 = " << X0 << endl;
                cout << "Fx eh " << fx(aFunc, bFunc, cFunc, X0) << " Fdx eh " << fdx(aFunc, bFunc, cFunc, X0) << endl;
                cout << "\n=- Isso esta certo?\n[1] Sim\n[0] Nao\n-R: ";
                cin  >> op;
                if(op != 1 && op != 0){
                    cout << endl << "\t-- Opcao invalida! Tente de novo --" << endl;
                }
            }while(op != 1 && op != 0);
        }while(op != 1);        
    }while(op != 1);
    
    
//precisao
//fx (float a, int b, float c, float x)
//fdx(float a, int b, float c, float x)
//cout << "Comecou" << endl;
int i;
    for(i = 0; i < No; i++){ //No = numero de iterações, escolhido pelo usuário

        X1 = X0 - ((fx(aFunc, bFunc, cFunc, X0)) / (fdx(aFunc, bFunc, cFunc, X0)));

        //Teste de parada

        if(modulo(X1 - X0) < precisao){
            //X1 é a solução!
            cout << "\n\n=--= Resultado obtido! X1 = " << X1 << endl;
            cout << "=-= Solucao eh f(" << X1 << ") = " << fx(aFunc, bFunc, cFunc, X1) << endl << endl;
            i = No + 2; // Garante a quebra do laço for
        }

        X0 = X1;

        //cout << "100" << endl;
    }
    if(i == No){
        cout << "\n\n==-=-=-== Numero maximo de iteracoes alcancado!" << endl;
            cout << "==-=-- f(" << X1 << ") = " << fx(aFunc, bFunc, cFunc, X1) << endl;
            cout << "==-=-- Valores fora da precisao inserida!" << endl << endl;
    }
}

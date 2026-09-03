/*
 * File:   main.c
 * Author: Automacao
 * Microcontrolador: PIC16F628A
 * Compilador: XC8
 */
//  ############### UNINTER #################
//  ###### Projeto Automacao de bombeio #####
//  ## Aluno: Andre Luiz de Paula Cardoso ###
//  ############## RU 3368302 ###############
// incluido delay mb001 religamento em 30 minutos


// Configuracoes dos Bits de Codigo (Configuration Bits)
#include <xc.h>;
#pragma config FOSC = XT        // Cristal externo de 4MHz nos pinos 15 e 16
#pragma config WDTE = OFF       // Watchdog Timer desativado
#pragma config PWRTE = ON       // Power-up Timer ativado
#pragma config MCLRE = ON       // Pino Master Clear ativado
#pragma config BOREN = ON       // Brown-out Detect ativado
#pragma config LVP = OFF        // Programacao em baixa tensao desativada
#pragma config CPD = OFF        // Protecao de memoria de dados desativada
#pragma config CP = OFF         // Protecao de codigo desativada

// Definicao da frequencia do oscilador para as funcoes de delay
#define _XTAL_FREQ 4000000

// Mapeamento das Entradas Digitais
#define LSL001 PORTBbits.RB3
#define LSL002 PORTBbits.RB2
#define LSL003 PORTBbits.RB1
#define FSL001 PORTBbits.RB0

// Mapeamento das Saidas Digitais
#define MB001 PORTBbits.RB4
#define LV001 PORTBbits.RB5
#define LV002 PORTBbits.RB6
#define LV003 PORTBbits.RB7

// Declara a variavel T1 como int
int T1 = 0;

// Funcao auxiliar para gerar atrasos longos em segundos
void delay_segundos(int segundos) {
    for (int i = 0; i < segundos; i++) {
        __delay_ms(1000);
    }
}

void main(void) {
    
   TRISB=0b00001111;
   CMCON=0x07;
   PORTB=0x00;
    

    // Rotulo de reinicio do programa
    inicio:

    // No inicio do programa as saidas digitais deverao ser colocadas em nivel logico 0
    MB001 = 0;
    LV001 = 0;
    LV002 = 0;
    LV003 = 0;
    T1 = 0; // Reinicia o contador T1

    while(1) {
        // Se LSL001=1 entao a saida MB001 e LV001 deverao ir para nivel logico 1
        if (LSL001 == 1) {
            MB001 = 1;
            LV001 = 1;
        }
        
        // Se LSL002=1 entao a saida MB001 e LV002 deverao ir para nivel logico 1
        if (LSL002 == 1) {
            MB001 = 1;
            LV002 = 1;
        }
        
        // Se LSL003=1 entao a saida MB001 e LV003 deverao ir para nivel logico 1
        if (LSL003 == 1) {
            MB001 = 1;
            LV003 = 1;
        }

        // Se LSL001=0 e LSL002=0 e LSL003=0 entao MB001=0 e introduzir um delay de 5 segundos
        if (LSL001 == 0 && LSL002 == 0 && LSL003 == 0) {
            MB001 = 0;
            delay_segundos(5);
        }

        // Se LSL001=0 entao LV001 deverao ir para nivel logico 0
        if (LSL001 == 0) {
            LV001 = 0;
        }
        
        // Se LSL002=0 entao LV002 deverao ir para nivel logico 0
        if (LSL002 == 0) {
            LV002 = 0;
        }
        
        // Se LSL003=0 entao LV003 deverao ir para nivel logico 0
        if (LSL003 == 0) {
            LV003 = 0;
        }

        // Se FSL001=0 e MB001=1 inicie o contador T1
        if (FSL001 == 0 && MB001 == 1) {
            __delay_ms(1000); // Aguarda 1 segundo
            T1++;             // Incrementa o contador de segundos
            
            // Se T1>15 segundos coloque a MB001=0, LV001=0, LV002=0, LV003=0. Pausa 1800 segundos e retorna para o inicio
            if (T1 >= 15) {
                MB001 = 0;
                LV001 = 0;
                LV002 = 0;
                LV003 = 0;
                
                delay_segundos(1800); // insere delay de 30 minutos
                goto inicio;        // Retorna para o inicio
            }
        } else {
            T1 = 0; // Reseta T1 se a vazao normalizar em ate 15 segundos
        }

        // Retorna para o inicio (Executa o ciclo novamente voltando ao topo do loop)
        __delay_ms(10); 
    }
}
# Hangman-Game
Um jogo de Hangman (Jogo da Forca), feito em linguagem C. Contendo a criação de contas e palavras, utilizando arquivos. 

# Imagens

![a](https://github.com/Paulo-Henrique-Silva/Hangman-Game/blob/main/Hangman-Game/Hangman-game-menu.PNG)

![a](https://github.com/Paulo-Henrique-Silva/Hangman-Game/blob/main/Hangman-Game/Hangman-game-Accounts.PNG)

![a](https://github.com/Paulo-Henrique-Silva/Hangman-Game/blob/main/Hangman-Game/Hangman-game-wordlist.PNG)

![a](https://github.com/Paulo-Henrique-Silva/Hangman-Game/blob/main/Hangman-Game/Hangman-game-Gameplay.PNG)

# Sobre o Projeto

No programa, há um total de 9 opções com quais o Usuário pode interagir:

**1 - Jogar**

Após o login em uma conta, o jogo, que funciona assim como um jogo de forca normal, inicia. O usuário digita letra por letra e a palavra se completa caso tenha acertado e o desenho do Enforcado se completa caso tenha errado.

A lista de palavras é um dos arquivos do jogo. O programa escolhe aleatoriamente uma palavra da lista antes de iniciar a partida.

- O programa, por padrão, criará 10 palavras caso não haja nenhum arquivo presente no jogo. 

**2 - Como Jogar**

Tutorial do jogo

**3 - Criar Conta**

O usuário introduz um nome e uma senha que serão armazenados em Arquivos contidos na mesma pasta que o arquivo principal. Desse modo, as dados são salvos após o programa se encerrar.

**4 - Deletar Conta**

Uma lista numerada de todas as contas existentes aparecem. Após o usuário digitar o número da conta, ela é apagada dos arquivos do programa.

**5 - Mostrar Contas**

Mostra uma lista numerada de todas as contas existentes e suas respectivas pontuações.
- A pontução é calculada da seguinte forma: O total de pontos ganhos em UMA partida será **6** menos o número de letras erradas que o usuário digitiou. 

**6 - Adicionar uma Palavra**

O programa pede ao usuário para que digite uma palavra que, necessariamente, deverá conter apenas caracteres do Alfabeto e não pode ser igual a outra palavra presente no arquivo.

- O programa só armazena palavras em Caixa alta para evitar problemas de processamento.

**7 - Deletar Palavra**

De forma similar a opção 5, o programa mostra a lista numerada de palavras, o usuário digita um número e a palavra é deletada dos arquivos do jogo.

**8 - Mostrar Palavras**

Mostra a lista numerada de todas as palavras

**9 - Sair**

Fecha o programa

# Informações Adicionais

 - O principal objetivo do projeto é o aprendizado, portanto o uso do código é **Totalmente livre**.
 - O arquivo .exe do programa só funciona no Sistema Operacional Windows. 

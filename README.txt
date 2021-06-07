O algoritmo imprime um calendário em forma de lista em português ou inglês a partir de um arquivo dado pelo usuário, ordena e busca dentro deste arquivo e, por fim, gera um pdf com o calendário.
Para utilizar o programa, deverá ser colocado um arquivo .txt (cujo nome será requisitado quando compilar) na pasta do projeto.
O arquivo deve estar na pasta do projeto ou configurado de acordo com a IDE para usá-lo.
O nome do arquivo deverá ser colocado no compilador com o final .txt. Por exemplo, se o arquivo se chamar "Arquivo", como será dito no programa, é necessário escrever como "Arquivo.txt" no compilador
O .txt deve conter o tipo de evento, dia, mês, ano, e especificação.
Por exemplo:
A 12 03 1999 Aniversário
O 15 03 1999 Outros
V 9  03 1999 Viagem
F 19 03 1999 Feriado
A especificação do evento deve ter até 25 caracteres.
Tais eventos serão impressos no programa em uma lista em forma de calendário contendo o dia da semana equivalente a cada dia.
Obs: Eventos cujo dia do mês é "0" serão impressos em todos os dias.
Quando compilado, o programa imprimirá, na tela, as instruções para selecionar a língua desejada (1 inglês e 0 poruguês).
Após a seleção da lingua, digite o mês e o ano  desejado (o calendário deverá ter dados apenas de um mês, especificado nesta hora).
A data deverá ser colocada da seguinte forma: "MM AAAA". Por exemplo, "07 2019". E então, o calendário será impresso na tela (em forma de lista).

Após a impressão do calendário em forma de lista, será perguntado se o usuário deseja ordenar o arquivo (digite 1 para sim, 0 para não).
Caso sim, há 2 tipos de ordenação:
1)Na ordem aniversários, feriados, viagens e outros (digite 0).
2)Na ordem cronológica de eventos. (digite 1)

E então, a parte da pesquisa se inicia. Digite 1 para pesquisar, 0 para pular.
Em caso afirmativo, 0 para pesquisar por dia e 1 para pesquisar por tipo definido de evento.
0)Digite o dia que quer pesquisar e o programa imprimirá os arquivos relacionados a tal dia.
1)Digite o Evento "A", "F", "V" ou "O" e o programa imprimirá todos os arquivos relacionados ao evento procurado.

Após todos os passos anteriores, é necessário informar como se deseja que o pdf do calendário seja gerado, sendo:
1 para o calendário com o mês anterior
2 para o calendário com o mês posterior
3 para apenas o mês dos arquivos
4 para incluir o mês anterior e o posterior
Obs: O diretório das imagens usadas para gerar o pdf está escrito no programa para ir para a pasta "calendario", que contêm as imagens JPEG que estão sendo usadas.
Já o dos ícones associados aos eventos, estão na pasta "icones".
Estas pastas estão no ZIP baixado e deverão ser colocadas na pasta do projeto para que o programa funcione como esperado, caso contrário, o fundo do calendário não será impresso.
Os nomes das imagens deverão ser mantidos como foram baixaxdos.

Por fim, será gerado um arquivo PDF (output.pdf) na pasta do projeto com o calendário feito com os eventos.

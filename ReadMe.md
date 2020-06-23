
Roberto Menegais 201810233

Instruções para o uso do programa:
* Se houver um arquivo input.dct já existente na pasta, o programa abrirá diremate on arquivo, caso não haja, serão gerados  amostras aleatórias. 
* É possivel gerar amostrar aleatórias controlando o slider ao lado do botão de salvar dados, podendo gerar de 8 a 64 amostras, que atualizarão automaticamente os gráficos
* Caso se deseje salvar as amostras geradas, basta clicar no botão Save Data.
* Para carregar o último arquivo com amostras salvo, basta clicar no botão Load Data. 
* As base functions continuas e discretas podem ser vizualizadas nos botões de mesmo nome, para fechar a janela aberta basta clicar novamente no botão usado para abri-lá. 
* O slider ao lado dos botões das base functions controla qual o fator de quantização aplicado nas amostras após a transformada dicreta do cosseno, indo de 0 a 100.
    * Se o fator for zero, não é aplicada nenhuma quantização, caso contrário, quanto maior o fator maior será a diferença entre o input original e a IDCT, devido ao processo de quantização. 
* Todas as janelas podem ser movidas para melhor vizualização na tela.


Funcionalidades implementadas:

* Leitura das amostras do arquivo de entrada no formato especificado. Os dados lidos
serão do tipo byte, mas devem ser armazenado em memória utilizando um array de
int, variando entre -127 e +128.
* Aplicação da DCT sobre as amostras de entrada.
* Aplicar algum tipo de “compressão” parametrizável e interativo. Pode ser eliminação
de frequências altas ou uso de vetor de quantização.
* Aplicação da transformada inversa (IDCT) para reconstrução dos dados originais.
* Calcular a diferença entre a entrada e os dados reconstruídos.
* Plotagem dos gráficos das quatro diferentes amostragens. O tamanho do gráfico
deve se adaptar horizontalmente à quantidade de amostras lidas.
* Exibir as N funções bases usadas na DCT, em sua forma discreta e contínua. A forma
discreta é usada na DCT.


Extras: 

* (+1) Implementação de uma interface interativa ( botões para carregar o input,
 aplicar DCT, aplicar IDCT, sliders para visualizar melhor as amostras, etc. ). Quanto
 menos cliques melhor.
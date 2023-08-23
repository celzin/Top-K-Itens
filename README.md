<div style="display: inline_block">
  <img align="center" alt="VS" src="https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white" />
  <img align="center" alt="Linux" src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" />
  <img align="center" alt="C++" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
</div><br>

# ⚠️ Apresentação do Problema 

<div align="justify">

Um exemplo clássico de problema que pode ser solucionado utilizando-se hash e heap é o chamado top k itens. Neste problema, é preciso encontrar os k itens mais valiosos de uma coleção de dados. Logo, utiliza-se o hash para contar a frequência de todos os itens, enquanto o heap se aplica na manutenção de uma lista dos k itens de maior valor.

Sabendo-se disso, elabore uma solução em C/C++ que dado uma entrada:

1. Crie uma tabela de dispersão (hash) para contar a frequência de cada elemento tokenizado da coleção de dados de entrada.

2. Crie uma árvore de prioridades (heap) de tamanho k e insira os primeiros k elementos do hash nela.

3. Para cada elemento restante na hash, compare a contagem com o menor valor do heap.

4. Se a contagem for maior do que o menor valor da heap, remova o menor valor, insira o novo elemento e refaça a estrutura.

5. Caso contrário, ignore o elemento e vá para o próximo.

6.   Este programa deverá ler uma coleção de arquivos contendo textos sem nenhuma formatação ("arquivo ASCII") onde cada sentença termina por um sinal de pontuação (".", "?", "!").

7. Cada parágrafo é separado por, pelo menos, uma linha em branco.

8. Considere como palavra uma sequência de letras delimitada por espaço em branco, ”coluna da esquerda”, ”coluna da direita” e símbolos de pontuação.

9. O programa deverá fazer a identificação de "stop words" (palavras que não têm conteúdo semântico) através da leitura de um arquivo "stopwords.txt" realizando a exclusão dessas palavras na análise do texto sendo necessário o tratamento para identificação caso apareçam maiúsculas ou minúsculas ao longo dos textos.

Ao final, a heap conterá os k elementos com maiores valores (frequências) da coleção de dados. Então, imprima-os em formato de tabela em ordem crescente juntamente com a quantidade de vezes em que aparecem. 

Esse algoritmo deve ser uma combinação eficiente do uso de hash para contar a frequência dos elementos e heap para manter a lista dos k elementos com maiores valores. Sua complexidade, caso implementado adequadamente, é de O(nlogk), onde n é o tamanho da coleção de dado e k o número de itens mais relevantes.
 
</div>


# 💡 Solução do Problema 

## **Hash**

### 1. Função Hash

<div align="justify">

A função adotada usa um método popular e simples para strings, multiplicando o valor hash acumulado por um número primo (31 neste caso) e adicionando o valor ASCII do próximo caractere da string. Isso ajuda a distribuir as strings uniformemente no espaço do hash. O operador `% size` garante que o valor retornado estará dentro dos limites da tabela hash.

```C
size_t HashTable::hash(const std::string &key) const {
    size_t hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % size;
    }
    return hash;
}
```

</div>

### 2. Tratamento de Colisões
<div align="justify">

 A colisão é tratada usando **Encadeamento**. Cada índice na tabela hash armazena uma lista (neste caso, um `std::vector`) de pares chave-valor. Se duas chaves diferentes tiverem o mesmo valor hash, elas serão armazenadas na mesma posição da tabela, mas em posições diferentes do vetor. Se a chave não existe, ela é adicionada com uma contagem de 1.

</div>

### 3. Inserção
 Ao inserir uma nova chave:

  - Primeiro, a função hash é usada para determinar o índice na tabela. 
  - Se a chave já existe na posição correspondente, sua contagem/frequência é aumentada.
  - Se a chave não existe, ela é adicionada com uma contagem de 1.

### 4. Busca 
Para buscar a frequência de uma chave:

  - A função hash é usada para determinar o índice na tabela. 
  - A posição correspondente é verificada para encontrar a chave desejada e retornar sua contagem.
  - Se a chave não é encontrada, a função retorna 0, indicando que a chave não foi inserida na tabela.

### 5. Complexidade 
<div align="justify">

Em teoria, a busca, inserção e exclusão em uma tabela hash têm uma complexidade de tempo médio de O(1). No entanto, no pior caso (quando todas as chaves colidem), a complexidade pode degradar para O(n), onde n é o número de chaves.

No entanto, o encadeamento (como o método de tratamento de colisões) ajuda a reduzir o impacto das colisões. Na prática, se a função hash estiver bem projetada e a tabela hash tiver um bom tamanho (não muito pequeno em relação ao número de entradas), as operações tendem a permanecer muito rápidas.

</div>

## Heap

<div align="justify">
Em um heap, os elementos são organizados em uma estrutura de árvore binária completa, onde cada nó tem até dois filhos. No código proposto, optou-se por utilizar um vetor <code>(std::vector)</code> para armazenar os elementos da heap, já que é uma representação comum e eficiente para uma árvore binária completa.
</div>

### Implementação da Heap:
<div align="justify">
Aqui estão os detalhes de como a heap é implementada no código:

1. **Representação da Árvore:** 

# 🔬 Experimentação 

<div align="justify">
	
Nesta seção, apresentamos os resultados de experimentos envolvendo as operações propostas.

</div>

<p align="center">
<img src="imgs/" width="250"/> 
</p>
<p align="center">
<em>Imagem 1: Saída no terminal para os top 20 elementos. </em>
</p>

<div align="justify">
	
Em resumo, 

</div>
	
# 🎯 Conclusão 

<div align="justify">
	
O programa desenvolvido utiliza duas estruturas de dados principais, a Hash e a Heap, para encontrar e imprimir os k elementos com as maiores frequências em uma coleção de dados. Aqui está uma revisão das abordagens e como as duas estruturas de dados foram usadas:

**Hash:** Usou-se um mapa desordenado <code>(std::unordered_map)</code> para contar a frequência de cada palavra no texto. O mapa desordenado permite armazenar pares chave-valor, onde a chave é a palavra e o valor é a frequência da palavra. Este mapa é usado como uma tabela de dispersão (hash) que ajuda a armazenar e acessar os elementos de maneira eficiente. Utilizamos uma função hash interna do std::unordered_map para calcular o valor hash das palavras, o que ajuda a distribuir os elementos na tabela. As colisões, que ocorrem quando duas ou mais palavras têm o mesmo valor hash, são tratadas pelo mapa desordenado usando encadeamento separado.

**Heap:** Utilizou-se um vetor <code>(std::vector)</code> para implementar uma heap de forma personalizada. A heap é uma estrutura de árvore binária completa onde cada nó tem até dois filhos. O vetor é usado para representar essa árvore, onde cada elemento tem um pai na posição <code>(i - 1) / 2</code> e filhos nas posições <code>2 * i + 1</code> e <code>2* i + 2</code>. No programa, usou-se o vetor para manter os k elementos com maiores frequências sem ordená-los automaticamente. Adicionamos e removemos elementos com base em sua frequência sem manter automaticamente a propriedade da heap.

**Processamento:** Primeiro, lemos a coleção de arquivos e processamos o texto para tokenizar as palavras e atualizar a tabela de dispersão (hash) com as frequências das palavras. Durante esse processo, tratamos as "stop words" e removemos os símbolos de pontuação. Em seguida, preenchemos o vetor (heap personalizada) com os primeiros k elementos do mapa desordenado. Para cada elemento restante no mapa desordenado, comparamos sua frequência com a menor frequência no vetor. Se a frequência do novo elemento for maior do que a menor frequência no vetor, removemos o elemento de menor frequência e inserimos o novo elemento.

**Ordenação e Impressão:** Após adicionar e remover elementos no vetor, ordenamos o vetor em ordem crescente de frequência utilizando a função std::sort. Isso garante que os elementos sejam impressos em ordem crescente de frequência. Em seguida, imprimimos os k elementos com maiores frequências e suas respectivas frequências.

No geral, o programa combina eficientemente o uso da Hash para contar a frequência das palavras e a Heap personalizada para manter a lista dos k elementos com maiores frequências. A ordenação final e a impressão são feitas para atender aos requisitos específicos do problema.

</div>

# 🔄 Compilação e Execução 

## Leitura de Arquivos

<p align="justify">

Primeiramente, para o correto funcionamento do programa é necessário incluir os arquivos preferencialmente nomeados de <code>inputN.data</code> dentro da pasta <code>dataset</code>, devendo ser alterado ou adicionado às condições da [linha 14](https://github.com/celzin/Top-K-Elementos/blob/main/src/main.cpp/#L14) da <code>main.cpp</code> no seguinte formato:

</p>

```c
// Aqui, voce pode adicionar uma lista de arquivos a serem analisados
   std::vector<std::string> files = { "./dataset/input1.txt", "./dataset/input2.txt", /*...*/ };
```

## Execução

<p align="justify">
Por fim, esse programa possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:
</p>

<table align="center">
  <tr>
    <th>Comando</th>
    <th>Função</th>
  </tr>
  <tr>
    <td>make clean</td>
    <td>Apaga a última compilação realizada contida na pasta build</td>
  </tr>
  <tr>
    <td>make</td>
    <td>Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build</td>
  </tr>
  <tr>
    <td>make run</td>
    <td>Executa o programa da pasta build após a realização da compilação</td>
  </tr>
</table>
	
# 📞 Contato

<table align="center">
  <tr>
    <th>Participante</th>
    <th>Contato</th>
  </tr>
  <tr>
    <td>Celso</td>
    <td><a href="https://t.me/celso_vsf"><img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> </td>
  </tr>
</table>

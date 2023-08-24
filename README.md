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

Esse algoritmo deve ser uma combinação eficiente do uso de hash para contar a frequência dos elementos e heap para manter a lista dos k elementos com maiores valores. Sua complexidade, caso implementado adequadamente, é de `O(nlogk)`, onde n é o tamanho da coleção de dado e k o número de itens mais relevantes.
 
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

Em teoria, a busca, inserção e exclusão em uma tabela hash têm uma complexidade de tempo médio de `O(1)`. No entanto, no pior caso (quando todas as chaves colidem), a complexidade pode degradar para `O(n)`, onde n é o número de chaves.

No entanto, o encadeamento (como o método de tratamento de colisões) ajuda a reduzir o impacto das colisões. Na prática, se a função hash estiver bem projetada e a tabela hash tiver um bom tamanho (não muito pequeno em relação ao número de entradas), as operações tendem a permanecer muito rápidas.

</div>

## **Heap**

### 1. Representação da Árvore
<div align="justify">

Uma das coisas mais notáveis sobre a implementação de uma heap é que, embora represente uma árvore binária, ela é armazenada como um vetor. Esta representação eficiente é possível graças à relação estruturada entre um nó e seus filhos e pai:

- Pai de um índice `i`: `(i - 1) / 2`
- Filho esquerdo de um índice `i`: `2i + 1`
- Filho direito de um índice `i`: `2i + 2`

Usando essa representação, é possível evitar o uso explícito de nodos e ponteiros, tornando a estrutura de dados mais compacta e o acesso aos nodos extremamente rápido.

Na implementação atual as funções auxiliares `left_child_index`, `right_child_index`, e `parent_index` são funções que ajudam a localizar os índices do filho esquerdo, filho direito e pai de um nó dado, respectivamente. Como a heap é implementada usando um vetor, essas funções usam cálculos simples para determinar os índices.

</div>

### 2. Inserção e Remoção
<div align="justify">

Ao inserir um novo elemento, você o adiciona ao final da heap (ou seja, ao final do vetor `elements`) e, em seguida, ajusta sua posição através da função `heapify_up()`. Essa função verifica se o elemento inserido é menor que seu pai. Se for, eles são trocados, e o processo continua até que a propriedade da heap seja restaurada.

Além disso, como você deseja manter apenas os top-k elementos, verifica se o tamanho da heap excede k após a inserção. Se exceder, o menor elemento (a raiz) é removido, o último elemento é movido para a raiz e a função `heapify_down()` é chamada para restaurar a propriedade da heap.

> `heapify_down()`: Essa função é usada após a remoção do menor elemento. Ela verifica se algum dos filhos do nó atual é menor que o próprio nó. Em caso afirmativo, troca o nó com seu filho menor e repete o processo até que a propriedade da heap seja restaurada.

</div>

### 3. Manutenção da Propriedade da Heap
<div align="justify">

A propriedade fundamental da heap implementada (min-heap) é que, para qualquer nó `i`, o valor em i é menor ou igual aos valores de seus filhos. Esta propriedade é mantida por duas funções principais: `heapify_up()` e `heapify_down()`.

Ao final a função `get_top_k()` simplesmente retorna o vetor `elements`, que contém os top-k elementos em ordem de heap (não necessariamente em ordem estritamente crescente ou decrescente).

### 4. Complexidade

- Inserção: `O(log n)`
  - Adicionar o elemento ao final do vetor: Isso é uma operação `O(1)` na média. Ocasionalmente, pode ser `O(n)` quando o vetor precisa ser redimensionado, mas, na média, inserir no final de um vetor dinâmico (como std::vector) é constante.
  - `heapify_up`: No pior caso, este processo pode ter que percorrer toda a altura da árvore, que para uma árvore binária completa (como é o caso da nossa heap) é `O(logn)`.

- Remoção: `O(log n)` 
  - Remover a raiz e colocar o último elemento no lugar dela: Isso é `O(1)`.
  - `heapify_down`: Semelhante ao `heapify_up`, no pior caso, pode percorrer toda a altura da árvore, ou seja, `O(logn)`.

- Buscar o menor: `O(1)` 
  - Como a menor elemento (em uma min-heap) é sempre a raiz, buscar por ele é uma operação `O(1)`.

- Manutenção (heapify): `O(log n)` 
  - Como discutido, heapify_up e heapify_down são ambos operações `O(logn)` no pior caso, já que, no máximo, eles percorrem a altura da árvore.

É importante notar que os elementos retornados por `get_top_k()` estão ***na ordem da heap** e não necessariamente em ordem estrita. Se fosse necessário obter os k elementos mais frequentes em ordem, seria necessário fazer mais processamentos (como ordenar os elementos antes de retornar).

</div>

# 🔬 Experimentação 

<div align="justify">
	
Testando o funcionamento do programa para o **Top 20 palavras mais frequentes** através da leitura dos arquivos [`input1.txt`](https://github.com/celzin/Top-K-Itens/blob/main/dataset/input1.txt) e [`input2.txt`](https://github.com/celzin/Top-K-Itens/blob/main/dataset/input2.txt) com o acervo de `stopwords` (palavras que são ignoradas ao processar o texto) fornecidos pelo arquivo [`stopwords.txt`](https://github.com/celzin/Top-K-Itens/blob/main/dataset/stopwords.txt) obteve-se a seguinte saída no terminal.

</div>

<p align="center">
<img src="imgs/terminal.png" width="250"/> 
</p>
<p align="center">
<em>Imagem 1: Saída no terminal para os Top 20 elementos mais frequentes. </em>
</p>
	
# 🎯 Conclusão 

<div align="justify">
	
O programa desenvolvido demonstra a poderosa combinação de duas estruturas de dados distintas e suas sinergias: a tabela hash e a heap.

A tabela hash serve como um meio eficaz de contabilizar a frequência de palavras de forma quase instantânea. Cada palavra serve como uma chave e sua frequência é o valor associado. Devido à natureza da tabela hash, inserir e buscar palavras são operações que, em média, ocorrem em tempo constante `O(1)`, tornando essa estrutura extremamente eficiente para o processo de contagem.

Entretanto, quando se trata de identificar os "top-k" elementos, ou seja, as palavras mais frequentes, uma tabela hash por si só não seria suficiente. Aqui entra o papel da heap, especificamente uma min-heap. Ela nos permite manter uma coleção de tamanho fixo (k) dos elementos mais frequentes enquanto processamos cada palavra. Adições e remoções são eficientes com complexidade `O (logk)`, e sempre temos acesso ao elemento de menor frequência em `O(1)`, o que facilita a decisão de quando remover ou adicionar um novo elemento.

A combinação dessas duas estruturas garante que, ao processar uma grande coleção de palavras, o programa consiga, em tempo real, manter um registro das palavras mais frequentes. No final desse processamento, a heap contém exatamente o que precisamos: as k palavras mais frequentes.

Em termos de complexidade, as operações individuais de ambas as estruturas são eficientes. O desafio real surge na interação entre elas. Ao processar cada palavra, há uma busca na tabela hash (que é rápida) e possivelmente uma inserção ou remoção na heap. Em termos práticos, o desempenho ainda é bastante eficiente, pois a heap tem um tamanho fixo de "k", e as operações na tabela hash são, na média, constantes.

Concluindo, a interação harmoniosa entre a tabela hash e a heap neste programa é um exemplo clássico de como diferentes estruturas de dados podem ser combinadas para criar soluções mais eficientes e elegantes para problemas complexos. Em nossa aplicação, conseguimos contabilizar palavras e identificar as mais frequentes de maneira otimizada, garantindo escalabilidade e eficiência no processamento de grandes conjuntos de dados.

</div>

# 🔄 Compilação e Execução 

## 1. Arquivos de Leitura

<div align="justify">

O programa foi projetado para processar um conjunto de arquivos de texto (.txt) contidos na pasta [`dataset`](https://github.com/celzin/Top-K-Itens/tree/main/dataset). Então, para o correto funcionamento do programa:

- Certifique-se de incluir os arquivos preferencialmente no formato <code>inputN.txt</code> dentro da pasta [<code>dataset</code>](https://github.com/celzin/Top-K-Itens/tree/main/dataset).
-  Ateste que os arquivos de texto estejam no formato correto (por exemplo, .txt) e que não contenham caracteres inválidos ou não reconhecidos.

</div>

## 2. Stopwords

<div align="justify">

O programa também faz uso de um arquivo [`stopwords.txt`](https://github.com/celzin/Top-K-Itens/blob/main/dataset/stopwords.txt). Este arquivo contém palavras que são comumente usadas, mas que geralmente são ignoradas ao processar texto (por exemplo, "e", "o", "de" etc.).

  - Certifique-se de que o arquivo `stopwords.txt` esteja localizado no diretório [`dataset`](https://github.com/celzin/Top-K-Itens/tree/main/dataset).

</div>

## 3. Top K elementos

<div align="justify">

Para alterar o valor de k, para por exemplo, obter as Top 20 palavras mais frequentes basta alterar a seguinte [linha de código](https://github.com/celzin/Top-K-Itens/blob/main/src/main.cpp/#L8):

```C
// Aqui, é possivel alterar o valor de k, por exemplo, top 20 palavras
const int TOP_K = 20;
```

</div>


## 4. Execução

<div align="justify">

Por fim, esse programa possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

</div>

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

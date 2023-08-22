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

## Hash

<div align="justify">
	
O algoritmo fornecido utiliza a estrutura <code>std::unordered_map</code>, para implementação da tabela hash em C++, essa estrutura usa uma combinação de técnicas matemáticas e algorítmicas para garantir uma distribuição eficiente dos dados e uma recuperação rápida.

1. **Função Hash:** A função hash usada pelo <code>std::unordered_map</code> pode variar dependendo do compilador e da biblioteca padrão usada. No caso de strings, cenário atual, a função hash considera os valores ASCII dos caracteres, utilizando o método do valor polinomial, também conhecido como [Horner's method](https://en.wikipedia.org/wiki/Horner%27s_method)

2. **Tratamento de Colisões:** O <code>std::unordered_map</code> lida com as colisões usando o método de encadeamento. Neste método, cada entrada na tabela de hash mantém uma lista de todos os pares chave-valor que têm o mesmo valor hash. Assim, se duas chaves têm o mesmo valor hash, elas são armazenadas na mesma entrada, mas são mantidas como elementos separados na lista.

3. **Inserção e Fator de Carga:** No código em análise, não é especificado explicitamente um tamanho inicial mas quando inserimos uma chave-valor na tabela hash, verificamos o fator de carga atual. Se o fator de carga exceder um certo limite (por exemplo, 0,7), redimensionamos a tabela hash.

4. **Redimensionamento:** Redimensionamos a tabela hash aumentando o número de baldes (por exemplo, dobrando o tamanho). Recalculamos os valores de hash para todas as chaves existentes usando a função hash de Horner e inserimos cada chave na nova posição apropriada na tabela hash redimensionada.

5. **Busca e Deleção:** Quando buscamos ou excluímos uma chave, calculamos seu valor de hash usando a função hash de Horner para determinar a posição na tabela hash.

</div>

### Cálculo da Hash:

<div align="justify">
	
No caso analisado o cálculo do valor hash para strings é o método do valor polinomial, também nomeado como [hash de Horner](https://en.wikipedia.org/wiki/Horner%27s_method) Vejamos o passo a passo de como a função hash de Horner, também conhecida como hash polinomial é implementada. 
	
- Neste método, cada caractere da string é tratado como um coeficiente polinomial, e um valor de hash é calculado de acordo com um polinômio.

1. **Escolha uma base e um módulo:** A base é um número que é multiplicado pelo valor de hash a cada iteração. O módulo é um número grande usado para evitar o overflow. A base é geralmente um número primo, como 31, e o módulo é frequentemente um número primo grande, como 1'000'000'007.

2. **Inicialize o valor de hash:** O valor inicial do hash é definido como 0.

3. **Processe cada caractere da string:** Percorra a string caractere por caractere e atualize o valor de hash a cada iteração.

4. **Atualize o valor de hash:** A cada iteração, atualize o valor de hash usando a fórmula:

```
'hash_value = (base * hash_value + c) % modulo'
```

- Onde 'base' é a base escolhida, 'hash_value' é o valor atual do hash, 'c' é o valor ASCII do caractere atual, e 'modulo' é o módulo escolhido.

Aqui está um exemplo de código em C++ para a função hash de Horner:

```c++
const size_t base = 31;
const size_t modulo = 1'000'000'007;

size_t horner_hash(const std::string &str) {
    size_t hash_value = 0;
    for (char c : str) {
        hash_value = (base * hash_value + c) % modulo;
    }
    return hash_value;
}
```

</div>

## Heap

<div align="justify">
Em um heap, os elementos são organizados em uma estrutura de árvore binária completa, onde cada nó tem até dois filhos. No código proposto, optou-se por utilizar um vetor <code>(std::vector)</code> para armazenar os elementos da heap, já que é uma representação comum e eficiente para uma árvore binária completa.
</div>

### Implementação da Heap:
<div align="justify">
Aqui estão os detalhes de como a heap é implementada no código:

1. **Representação da Árvore:** Um vetor é utilizado para representar a árvore binária completa. Se um elemento está na posição <code>'i'</code> no vetor, então seus filhos estão nas posições <code>2 * i + 1</code> e <code>2 * i + 2</code>, e seu pai está na posição <code>(i - 1) / 2.</code>

2. **Adição de Elementos:** Quando um novo elemento é adicionado à heap, ele é inserido na próxima posição disponível no vetor (no final do vetor). Depois disso, o elemento é movido para cima na árvore (sift up) até que esteja em uma posição onde a propriedade da heap seja mantida.

3. **Remoção de Elementos:** Ao remover o elemento de menor valor (para um min heap), o último elemento do vetor é movido para a posição do elemento removido. Então, esse elemento é movido para baixo na árvore (sift down) até que esteja em uma posição onde a propriedade da heap seja mantida.

4. **Manutenção da Propriedade da Heap:** Durante as operações de adição e remoção de elementos, a propriedade da heap é mantida através das operações de sift up e sift down. Para um min heap, a propriedade da heap é que o valor de um nó deve ser menor ou igual aos valores de seus filhos. Para um max heap, a propriedade da heap é que o valor de um nó deve ser maior ou igual aos valores de seus filhos.
</div>

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

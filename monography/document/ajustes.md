# Pontos para melhorar no TCC

- [X] Fazer dedicatória.
- [X] Fazer agradecimentos.
- [X] Fazer epigrafo.
- [X] Fazer ficha catalográfica.
- [X] Analisar o que está em itálico e ver se faz sentido ou não.
- [x] Mover do template antigo para o novo.

## João Vilnei

- [x] Documento

## Paulo de Tarso

- [x] Melhorar o tamanho das figuras. Exportar Imagens para PDF e deixar elas maiores.
- [x] Adicionar contribuições -> Repaginar com as contribuições do TCC.
- [x] Colocar um exemplo na parte que fala das limitações da PCG.

## Cristiano:

- [x] Adicionar na parte de contribuições os links to roguelike e do gerador de mapas.
- [x] Colocar um apêndice quando eu falo de gerar JSON mostrando um JSON de um mapa gerado.

# Dúvidas

- Que data colocar em "\dataaprovacao{xx/xx/xxxx.}"?
- A partir de quantas figuras, algoritmos, siglas/abreviaturas, tabelas, quadros... é preciso fazer uma lista lá no início do TCC. Por exemplo, se eu só tenho um algoritmo no meu TCC, eu preciso fazer uma lista para isso?

## Sugestões Cristiano

- Na parte de contribuições do TCC eu coloquei o link para os repositórios da implementação tanto do Gerador de Assets quanto do Gerado de Mapas.
- Na parte de contribuições do TCC quando eu falo sobre gerar JSON, eu referencio um apêndice mostrando um exemplo de uma saída JSON.

## Sugestões Paulo de Tarso

- Deixei o texto do Fluxo da Metodologia e do Fluxo de geração do Pacote de Assets maior.
- Na parte de metodologia deixei um exemplo mostrando como deixar o LLM gerar topologias gera falhas no mapa como tiles faltantes e vazamentos para fora dos limites das salas.
- Troca de Objetivos por Contribuições do TCC

## Sugestões do João Vilnei

- Importação do TCC para o modelo novo com formato de citações corretos.
- "onde" é para lugares físicos, então troquei por no(a) qual.
- No começo do TCC, removi as listas de algoritmos e de tabelas. Mantive só a lista de figuras e a lista de siglas. Fiz isso porque o TCC só tem 1 algoritmo e 2 tabelas.
- Adicionar a data de acesso dos links.
- Nos trabalho relacionados coloquei o que são os trabalhos (artigo, tese de mestrado, tcc...). Também referenciei os trabalhos pelo nome dos projetos que são desenvolvidos neles. Agora na tabela tem tanto a referência como o nome do projeto de cada trabalho.

## Minha Alterações

- Trocar de `Figura \ref{...}` pro `Figura~\ref{...}`. O `~` evita que o LaTeX quebre uma linha e separe o número da palavra "Figura". Fiz a mesma coisa para tabelas e algoritmos.
- Adicionar dedicatória, agradecimentos, epígrafo, ficha catalográfica.
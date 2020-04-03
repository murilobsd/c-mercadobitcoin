# C Mercadobitcoin

[![Travis (.org) branch](https://img.shields.io/travis/murilobsd/c-mercadobitcoin/master?style=for-the-badge)](https://travis-ci.org/murilobsd/c-mercadobitcoin)
[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

- **Código Fonte:** https://github.com/murilobsd/c-mercadobitcoin
- **Bugs:** https://github.com/murilobsd/c-mercadobitcoin/issues
- **SO:** OpenBSD/Linux

Biblioteca para comunicar com a API do MercadoBitcoin, essa biblioteca **não é
oficial**.

**Prioridade no momento é fornecer os métodos de consulta para a API Pública.**

## Instalação

Antes de instalar a biblioteca será necessário instalar as dependências:

1. [libcurl 3](1) 
2. [json-c](2)

Exemplo da instalação das dependências em alguns sistemas operacionais.

OpenBSD:

```
doas pkg_add curl json-c
```

Ubuntu:

```
sudo apt-get install libcurl-dev libjson-c-dev
```

Arch:

```
sudo pacman -S libcurl-compat json-c
```

Clone o repositório:

```bash
git clone https://github.com/murilobsd/c-mercadobitcoin.git mb
cd mb
```

Compilar a biblioteca:

```bash
make
```

Caso queira compilar o exemplo basta digita o comando abaixo:

```bash
make example
```

## ToDo

Free Api:

|Method|Status|Test|
|------|------|----|
|ticker|Implementing|-|
|orderbook|-|-|
|trades|-|-|
|day-summary|-|-|

## Outras bibliotecas

|Linguagem|Repo|
|--------|----|
|Python|[https://github.com/alfakini/python-mercadobitcoin](https://github.com/alfakini/python-mercadobitcoin)|
|Javascript|[https://github.com/marcbarbosa/mercadobitcoin](https://github.com/marcbarbosa/mercadobitcoin)|
|PHP|[https://github.com/diegoBSousa/mercadobitcoin-php-api](https://github.com/diegoBSousa/mercadobitcoin-php-api)|


## Referências da API

- [Mercado Bitcoin public data API](https://www.mercadobitcoin.com.br/api-doc)
- [Mercado Bitcoin private trade API](https://www.mercadobitcoin.com.br/trade-api)


[1]: https://curl.haxx.se
[2]: http://json-c.github.io/json-c/

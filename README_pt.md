<p align="center">
	<img src="https://raw.githubusercontent.com/murilobsd/c-mercadobitcoin/master/assets/mbc.jpg">
</p>

# 

[![Build Status](https://img.shields.io/travis/murilobsd/c-mercadobitcoin/master?style=for-the-badge)](https://travis-ci.org/murilobsd/c-mercadobitcoin)
[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

> Biblioteca não oficial para comunicação com API do [MercadoBitcoin][3]

- **Código Fonte:** https://github.com/murilobsd/c-mercadobitcoin
- **Bugs:** https://github.com/murilobsd/c-mercadobitcoin/issues
- **SO:** OpenBSD/Linux

**POR FAVOR NÂO USE**


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

## Usando

```c
#include <stdio.h>

#include <mb/mb.h>

int
main(int argc, char *argv[])
{
		FreeApi *f = freeapi_init();
		MBData	d;

		d = f->methods->ticker(f, BTC);

		if (d.error != MBE_OK)
				fprintf(stderr, "Error: %s\n", mb_get_strerro(d.error);
		else {
				printf("=========== Ticker ===========\n");
				printf("High: %f\n", d.data.ticker->high);
				printf("Low: %f\n", d.data.ticker->low);
				printf("Vol: %f\n", d.data.ticker->vol);
				printf("Last: %f\n", d.data.ticker->last);
				printf("Buy: %f\n", d.data.ticker->buy);
				printf("Sell: %f\n", d.data.ticker->sell);
				printf("Date: %u\n", d.data.ticker->date);
				printf("===============================\n");
		}

		clean_data(d);
		clean_freeapi(f);
		
		return (0);
}
```

compilando:

```bash
cc ticker.c -o ticker -lmbc
./ticker
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
[3]: https://www.mercadobitcoin.com.br

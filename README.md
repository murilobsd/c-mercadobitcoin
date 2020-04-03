# C Mercadobitcoin

[![Travis (.org) branch](https://img.shields.io/travis/murilobsd/c-mercadobitcoin/master?style=for-the-badge)](https://travis-ci.org/murilobsd/c-mercadobitcoin)
[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

- **Source code:** https://github.com/murilobsd/c-mercadobitcoin
- **Bug reports:** https://github.com/murilobsd/c-mercadobitcoin/issues
- **OS:** OpenBSD/Linux

## Install

Before installing the library has two **dependencies** [libcurl](1) and [json-c](2)

```bash
git clone https://github.com/murilobsd/c-mercadobitcoin.git mb
cd mb
```

Build lib:

```bash
make
```

Build example:

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

## Other libraries

|Language|Repo|
|--------|----|
|Python|[https://github.com/alfakini/python-mercadobitcoin](https://github.com/alfakini/python-mercadobitcoin)|
|Javascript|[https://github.com/marcbarbosa/mercadobitcoin](https://github.com/marcbarbosa/mercadobitcoin)|
|PHP|[https://github.com/diegoBSousa/mercadobitcoin-php-api](https://github.com/diegoBSousa/mercadobitcoin-php-api)|


## References

- [Mercado Bitcoin public data API](https://www.mercadobitcoin.com.br/api-doc)
- [Mercado Bitcoin private trade API](https://www.mercadobitcoin.com.br/trade-api)


[1]: https://curl.haxx.se
[2]: http://json-c.github.io/json-c/

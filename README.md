<p align="center">
	<img src="https://raw.githubusercontent.com/murilobsd/c-mercadobitcoin/master/assets/mbc.jpg">
</p>

# 

[![Build Status](https://img.shields.io/travis/murilobsd/c-mercadobitcoin/master?style=for-the-badge)](https://travis-ci.org/murilobsd/c-mercadobitcoin)
[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

> Unofficial library to communicate with [MercadoBitcoin][3] API

- **Source code:** https://github.com/murilobsd/c-mercadobitcoin
- **Bug reports:** https://github.com/murilobsd/c-mercadobitcoin/issues
- **OS:** OpenBSD, Linux

**PLEASE DO NOT USE**

## Install

Before installing the library has **dependencies**:

1. [libcurl][1] 
2. [libjansson][2]


```bash
git clone https://github.com/murilobsd/c-mercadobitcoin.git mb
cd mb
```

Build lib:

```bash
make
```

```

## ToDo

Free Api:

|Method|Status|Test|
|------|------|----|
|ticker|Implemented|OK|
|orderbook|Implemented|OK|
|trades|Implemented|OK|
|day-summary|Implemented|OK|

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
[2]: http://www.digip.org/jansson/
[3]: https://www.mercadobitcoin.com.br

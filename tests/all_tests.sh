#!/bin/sh

VERBOSE=$1

./test_json $VERBOSE
./test_order $VERBOSE
./test_orderbook $VERBOSE
./test_ticker $VERBOSE

#!/bin/sh

VERBOSE=$1

./test_json $VERBOSE
./test_order $VERBOSE
./test_orderbook $VERBOSE
./test_ticker $VERBOSE
./test_trade $VERBOSE
./test_day_summary $VERBOSE

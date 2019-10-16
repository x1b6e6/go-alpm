#!/bin/bash

docker build -t go-alpm-builder . || exit $?

docker run --rm go-alpm-builder make || exit $?

docker run --rm go-alpm-builder make test || exit $?

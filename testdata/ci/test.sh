#!/bin/bash

docker build -f "${1:-Dockerfile}" -t go-alpm-"${2:-builder}" . || exit $?

docker run --rm go-alpm-"${2:-builder}" make || exit $?

docker run --rm go-alpm-"${2:-builder}" make test || exit $?

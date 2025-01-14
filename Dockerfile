FROM lopsided/archlinux:devel
LABEL maintainer="Jguer,joaogg3 at google mail"

ENV GO111MODULE=on
WORKDIR /app

RUN pacman -Syu --overwrite=* --needed --noconfirm go

RUN curl -sSfL https://raw.githubusercontent.com/golangci/golangci-lint/master/install.sh | sh -s v1.39.0

COPY go.mod .

RUN go mod download

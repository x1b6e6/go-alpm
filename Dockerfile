FROM lopsided/archlinux:latest
LABEL maintainer="Jguer,joaogg3 at google mail"

ENV GO111MODULE=on
WORKDIR /app

RUN pacman -Syu --overwrite=* --needed --noconfirm archlinux-keyring go fakeroot binutils gcc make git gettext

RUN curl -sSfL https://raw.githubusercontent.com/golangci/golangci-lint/master/install.sh | sh -s v1.37.1

COPY go.mod .

RUN go mod download

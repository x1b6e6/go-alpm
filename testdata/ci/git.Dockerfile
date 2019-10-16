FROM archlinux:latest
LABEL maintainer="Jguer,joaogg3 at google mail"

ENV GO111MODULE=on
WORKDIR /app

RUN echo $'[eschwartz]\nServer = https://pkgbuild.com/~eschwartz/repo/$arch' >> /etc/pacman.conf && \
    (yes | pacman -Sy --overwrite=* --needed \
    git archlinux-keyring make gcc gcc-go awk pacman-contrib pacman-git) && \
    paccache -rfk0

# Dependency for linting
# RUN curl -sfL https://raw.githubusercontent.com/golangci/golangci-lint/master/install.sh| sh -s -- -b /bin v1.20.0
# RUN go get golang.org/x/lint/golint && mv /root/go/bin/golint /bin/

COPY . .

FROM alpine:3.6

RUN apk add --update \
    curl-dev \
    make \
    cmake \
    g++ \
    valgrind \
    gdb \
&& rm -rf /var/cache/apk/*

WORKDIR /app

COPY . /app
# RUN mkdir build && cd build && cmake .. && make && chmod +x PersonalWiki

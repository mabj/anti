FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y nasm make mingw-w64 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /experiment
COPY . .

CMD ["make"]

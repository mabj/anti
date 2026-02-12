FROM ubuntu:22.04

# Install MinGW cross-compiler
RUN apt-get update && \
    apt-get install -y \
    make \
    mingw-w64 \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /work

# Default command
CMD ["make", "all"]

FROM debian:buster-slim

# Install common tools
RUN \
    apt-get update -y && \
    apt-get install -y  --no-install-recommends \
        apt-transport-https \
        software-properties-common \
        ca-certificates \
        libcurl4 \
        wget \
        rsync

# Install complier tools
RUN \
    apt-get update -y && \
    apt-get install -y  --no-install-recommends \
        build-essential \
        gcc \
        g++ \
        python-dev \
        make \
        cmake

# Container setting
WORKDIR /repo

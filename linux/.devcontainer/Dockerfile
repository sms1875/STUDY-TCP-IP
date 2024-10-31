# .devcontainer/Dockerfile
FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-20.04

# Install necessary packages
RUN apt-get update && \
    apt-get install -y gcc make && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

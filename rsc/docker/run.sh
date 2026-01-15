#!/bin/bash

docker build -t famine-run ./rsc/docker

docker run -d --name famine-container -p 9001:9001 --workdir=/app --rm -v "$(pwd)":/app -v ~/.ssh/:/root/.ssh famine-run sleep infinity

# Set up git user configuration
GIT_EMAIL=$(git config user.email)
GIT_NAME=$(git config user.name)
docker exec famine-container git config --global user.email "${GIT_EMAIL}"
docker exec famine-container git config --global user.name "${GIT_NAME}"

# Start zsh in the container
docker exec -it famine-container zsh

docker rm -f famine-container
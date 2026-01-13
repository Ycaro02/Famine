FROM ubuntu:24.04

RUN apt update && apt install -y curl zsh clang make valgrind gdb git libcriterion-dev vim 

ENV TZ=Europe/Paris
ENV EDITOR=/bin/vim

RUN git config --global --add safe.directory /app

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# add basic alias for git
RUN echo 'alias add_all="git add . && git commit -m"' >> /root/.zshrc

# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM ubuntu:latest

# These commands copy your files into the specified directory in the image
# and set that as the working location
#COPY . /usr/src/myapp
VOLUME [ "/work" ]
WORKDIR /work

# This command compiles your app using GCC, adjust for your source code
RUN apt update && \
 apt upgrade -y
RUN apt install gcc curl zsh make valgrind -y
RUN apt install git -y
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" | zsh || true

# This command runs your application, comment out this line to compile only
# CMD ["zsh"]
ENTRYPOINT [ "zsh" ]

LABEL Name=philosopher Version=0.0.1

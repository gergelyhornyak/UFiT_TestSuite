FROM ubuntu:22.04

WORKDIR /ProjectDir

#ENV QT_API=pyqt5
#ENV ETS_TOOLKIT=qt
#ENV DISPLAY=:99
ENV DEBIAN_FRONTEND=noninteractive

RUN mkdir -p /ProjectDir/testSuite
RUN mkdir -p /ProjectDir/target

COPY docker/requirements.txt .
COPY docker/list_of_commands.sh .
COPY testSuite/ /ProjectDir/testSuite/

# Install dependencies
RUN apt-get update
RUN apt-get install -y git
RUN apt-get install -y gfortran
RUN apt-get install -y build-essential
RUN apt-get install -y g++
RUN apt-get install -y cmake
RUN apt-get install -y python3
RUN apt-get install -y python3-pip
RUN apt-get install -y graphviz
RUN apt-get install -y valgrind
RUN apt-get install -y lcov
#RUN apt-get install -y texlive-base texlive-latex-base dvipng texlive-fonts-recommended texlive-fonts-extra texlive-latex-extra cm-super
#RUN apt-get install -y tree
RUN apt-get autoclean

RUN pip install --upgrade pip
RUN pip install -r ./requirements.txt

CMD ["bash","/ProjectDir/list_of_commands.sh"]

FROM ubuntu:22.04 AS builder
#already minimal ~ 30 MB

LABEL maintainer="Gergely Hornyak <gergely.hornyak.1@gmail.com>"

WORKDIR /build

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    gfortran \
    g++ \
    git \
    python3 \
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Pre-build GoogleTest (so the script doesn't have to)
RUN git clone https://github.com/google/googletest.git -b v1.16.0 /opt/googletest \
    && cd /opt/googletest && mkdir build && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local .. \
    && make \
    && make install

WORKDIR /ProjectDir/target

RUN git clone https://github.com/Valentin-Aslanyan/UFiT.git UFiT \
    && cd UFiT && make

COPY docker/requirements.txt .
RUN pip install --upgrade pip && \
    pip install --user --no-cache-dir -r requirements.txt

#--------------------------------------------------------#

FROM ubuntu:22.04 AS runner

ENV PATH="/root/.local/bin:$PATH" \
    PYTHONPATH="/root/.local/lib/python3.10/site-packages"

WORKDIR /ProjectDir

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    gfortran \
    build-essential \
    cmake \
    g++ \
    graphviz \
    valgrind \
    lcov \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /usr/local/include/gtest /usr/local/include/gtest
COPY --from=builder /usr/local/lib/libgtest* /usr/local/lib/
RUN ldconfig

COPY --from=builder /root/.local /root/.local
COPY --from=builder /ProjectDir/target /ProjectDir/target

RUN mkdir -p testSuite testOutput testInput

COPY testSuite/ ./testSuite/
COPY docker/list_of_commands.sh ./

RUN chmod +x list_of_commands.sh

ENTRYPOINT ["/bin/bash", "/ProjectDir/list_of_commands.sh"]
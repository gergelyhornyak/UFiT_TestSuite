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
    && cmake .. && make && make install

WORKDIR /ProjectDir/target

RUN git clone https://github.com/Valentin-Aslanyan/UFiT.git UFiT \
    && cd UFiT && make && gfortran -fPIC -shared -c *.F90

#--------------------------------------------------------#

FROM ubuntu:22.04 AS runner

ENV PYTHONPATH="/root/.local/lib/python3.10/site-packages" \
    PATH="/root/.local/bin:$PATH"

WORKDIR /ProjectDir

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    graphviz \
    valgrind \
    lcov \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /usr/.local /usr/.local
COPY --from=builder /ProjectDir/target /ProjectDir/target

COPY docker/requirements.txt .
RUN pip install --upgrade pip && \
    pip install --no-cache-dir -r requirements.txt

RUN mkdir -p testSuite target testOutputs testInputs

COPY testSuite/ ./testSuite/
COPY docker/list_of_commands.sh ./

RUN chmod +x list_of_commands.sh

ENTRYPOINT [ "/bin/bash" ]
CMD ["./list_of_commands.sh"]

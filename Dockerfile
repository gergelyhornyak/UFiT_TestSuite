FROM ubuntu:22.04 AS builder 
#already minimal ~ 30 MB

LABEL maintainer="Gergely Hornyak <gergely.hornyak.1@gmail.com>"

WORKDIR /build

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    cmake \
    gfortran \
    g++ \
    git \
    python3 \
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Pre-build GoogleTest
RUN git clone https://github.com/google/googletest.git -b v1.16.0 /opt/googletest \
    && cd /opt/googletest && mkdir build && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local .. \
    && make && make install

WORKDIR /ProjectDir/target

# Pre-build UFiT
RUN git clone https://github.com/Valentin-Aslanyan/UFiT.git UFiT \
    && cd UFiT \
    && make

WORKDIR /ProjectDir

# Install Python dependencies for the test suite
COPY docker/requirements.txt .
RUN pip install --upgrade pip && \
    pip install --no-cache-dir --prefix=/install -r requirements.txt

#--------------------------------------------------------#

FROM ubuntu:22.04 AS runner

ENV PYTHONPATH="/usr/local/lib/python3.10/site-packages"

WORKDIR /ProjectDir

# Install runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    gfortran \
    build-essential \
    cmake \
    make \
    g++ \
    graphviz \
    valgrind \
    lcov \
    #texlive-base texlive-latex-base dvipng texlive-fonts-recommended texlive-fonts-extra texlive-latex-extra cm-super
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Copy the built python packages 
COPY --from=builder /install/local/. /usr/local/ 
# Copy the built GoogleTest libraries and headers
COPY --from=builder /usr/local/include/gtest /usr/local/include/gtest
COPY --from=builder /usr/local/lib/libgtest* /usr/local/lib/
# Copy the built UFiT binaries
COPY --from=builder /ProjectDir/target /ProjectDir/target

WORKDIR /ProjectDir

RUN mkdir -p testSuite
COPY testSuite/ ./testSuite/
RUN cd testSuite \
    && rm -rf build \
    && mkdir build && cd build \
    && cmake .. && make

# Update the shared library cache
RUN ldconfig

# Set the entry point to run the test suite script
# The scripts/ dir is mounted at runtime
ENTRYPOINT ["/bin/bash", "/ProjectDir/scripts/list_of_commands_modular.sh"]
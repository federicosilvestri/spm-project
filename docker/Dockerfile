FROM gcc:8.3

RUN apt-get update
RUN apt-get install -y cmake

RUN git clone https://gitlab.kitware.com/cmake/cmake /tmp/cmake
WORKDIR /tmp/cmake
RUN ./configure --no-qt-gui
RUN make && make install

# install GRPPI
RUN git clone https://github.com/arcosuc3m/grppi.git
RUN cd grppi && mkdir build && cd build && cmake .. && make -j && make install
RUN rm -r grppi

# install RPLSH
RUN git clone https://github.com/Murray1991/rplsh.git
RUN cd rplsh && mkdir build && cd build && cmake ../rpl-shell -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release && make -j
RUN mv rplsh/build/rplsh /usr/bin/rplsh
RUN rm -r rplsh

# install FastFlow
RUN git clone  https://github.com/fastflow/fastflow.git
RUN cd fastflow && git checkout b396caa129761f1a633b6b290373f79c0ddb7025 && mkdir build && cd build && cmake .. -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=ON && make && make install

WORKDIR /mnt/src
CMD make

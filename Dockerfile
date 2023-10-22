FROM gcc:11.4.0

RUN mkdir -p /opt/code/

WORKDIR /opt/code
RUN apt-get update && apt-get install -qy cmake zip gdb

RUN wget https://github.com/fastflow/fastflow/archive/refs/tags/3.0.0.zip
RUN unzip 3.0.0.zip && mv fastflow-3.0.0 fastflow && rm 3.0.0.zip && mkdir -p fastflow/build

WORKDIR /opt/code/fastflow/build

RUN /usr/bin/cmake .. -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=OFF && make

RUN make install
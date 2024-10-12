FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    qtbase5-dev \
    qtcreator \
    libx11-dev \
    g++ \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app/src

COPY . .

RUN make install

CMD ["../build/SmartCalc.app"] 

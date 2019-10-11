FROM ubuntu:18.04
LABEL maintainer "sunghwan19 <sunghwan519@hotmail.com>"

RUN apt-get update && apt-get install -y \
	build-essential \
	cmake \
	--no-install-recommends \
	&& rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app/build
RUN cmake .. && \
	make -j "$(nproc)" && \
	make install && \
	bin/UnitTest

WORKDIR /
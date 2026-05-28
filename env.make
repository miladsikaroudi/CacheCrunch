.PHONY: build-env run-benchmark clean

HOST_DIR := $(shell pwd)
IMAGE_NAME := cachecrunch-env

# Command 1: Builds the reusable Docker image
build-env:
	@echo "=== Creating temporary Dockerfile ==="
	@echo "FROM ubuntu:latest" > Dockerfile.tmp
	@echo "RUN apt-get update -qq && apt-get install -y gcc valgrind -qq" >> Dockerfile.tmp
	@echo "=== Building Docker image: $(IMAGE_NAME) ==="
	docker build -t $(IMAGE_NAME) -f Dockerfile.tmp .
	@rm Dockerfile.tmp
	@echo "=== Image built successfully! ==="


clean:
	@echo "=== Cleaning up workspace ==="
	rm -f matrix cachegrind.out.* Dockerfile.tmp
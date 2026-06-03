.PHONY: run-benchmark run-test build-env clean


ROOT_DIR  := $(shell pwd)
IMAGE_NAME := cachecrunch-env

# Usage: make run-benchmark DIR=cpp-experiments/matrix-multiplications/transpose
run-benchmark:
	@if [ -z "$(DIR)" ]; then echo "ERROR: specify DIR=<path>"; exit 1; fi
	@echo "=== Running benchmarks in $(DIR) ==="
	docker run --rm \
		-v "$(ROOT_DIR)/$(DIR):/app" \
		-w /app $(IMAGE_NAME) bash -c "\
		echo '-> Compiling matrices.cpp...' && \
		g++ -O1 matrices.cpp -o matrix && \
		echo '-> Running Naive (i-j-k) Benchmark...' && \
		valgrind --tool=cachegrind --cache-sim=yes ./matrix 1 && \
		echo '-> Running Optimized Benchmark...' && \
		valgrind --tool=cachegrind --cache-sim=yes ./matrix 2"

# Runs test.cpp from root — always mounts full repo
run-test:
	@echo "=== Running tests ==="
	docker run --rm \
		-v "$(ROOT_DIR):/app" \
		-w /app $(IMAGE_NAME) bash -c "\
		echo '-> Compiling...' && \
		g++ -O1 test.cpp cpp-experiments/matrix-multiplications/transpose/matrices.cpp -o test_bin -lm && \
		echo '-> Running tests...' && \
		./test_bin"

# Command 1: Builds the reusable Docker image
build-env:
	@echo "=== Creating temporary Dockerfile ==="
	@echo "FROM ubuntu:latest" > Dockerfile.tmp
	@echo "RUN apt-get update -qq && apt-get install -y gcc g++ valgrind -qq" >> Dockerfile.tmp
	@echo "=== Building Docker image: $(IMAGE_NAME) ==="
	docker build --no-cache -t $(IMAGE_NAME) -f Dockerfile.tmp .
	@rm Dockerfile.tmp
	@echo "=== Image built successfully! ==="

clean:
	@echo "=== Cleaning up ==="
	rm -f $(ROOT_DIR)/test_bin
	find $(ROOT_DIR)/cpp-experiments -name "matrix" -delete
	find $(ROOT_DIR)/cpp-experiments -name "cachegrind.out.*" -delete

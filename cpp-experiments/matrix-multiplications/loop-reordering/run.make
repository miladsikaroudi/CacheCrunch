.PHONY: build-env run-benchmark clean

HOST_DIR := $(shell pwd)/cpp-experiments/matrix-multiplications/loop-reordering/
IMAGE_NAME := cachecrunch-env


# Mounts the code and runs the tests using the dev image
run-benchmark:
	@echo "=== Running benchmarks inside $(IMAGE_NAME) ==="
	docker run --rm -v "$(HOST_DIR):/app" -w /app $(IMAGE_NAME) bash -c "\
		echo '-> Compiling matrices.c...' && \
		gcc -O1 matrices.c -o matrix && \
		echo '-> Running Naive (i-j-k) Benchmark...' && \
		valgrind --tool=cachegrind --cache-sim=yes ./matrix 1 && \
		echo '-> Running Optimized (i-k-j) Benchmark...' && \
		valgrind --tool=cachegrind --cache-sim=yes ./matrix 2"

clean:
	@echo "=== Cleaning up workspace ==="
	rm -f $(HOST_DIR)/matrix $(HOST_DIR)/cachegrind.out.* $(HOST_DIR)/Dockerfile.tmp
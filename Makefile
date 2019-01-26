.PHONY: run

run:
	bazel build //:yali && ./bazel-bin/yali
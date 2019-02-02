.PHONY: run build clean app ast build-graph

run:
	bazel build //:yali --verbose_failures && ./bazel-bin/yali

build:
	bazel build //:yali && mv -f ./bazel-bin/yali yali

clean:
	bazel clean

app:
	bazel build //app:app

ast:
	bazel build //ast:ast

build-graph:
	bash -c "xdot <(bazel query --nohost_deps --noimplicit_deps 'deps(//:yali)' --output graph)"
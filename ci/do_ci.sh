#!/bin/bash -e

# 定义了两个函数：do_build和do_test。do_build函数会使用Bazel构建项目，do_test函数会运行项目的测试。这个脚本会在CircleCI的build和test工作流中被调用。

export PATH=/usr/lib/llvm-8/bin:$PATH
export CC=clang
export CXX=clang++
export ASAN_SYMBOLIZER_PATH=/usr/lib/llvm-7/bin/llvm-symbolizer
echo "$CC/$CXX toolchain configured"

if [[ -f "${HOME:-/root}/.gitconfig" ]]; then
  mv "${HOME:-/root}/.gitconfig" "${HOME:-/root}/.gitconfig_save"
fi

function do_build() {
  bazel build --verbose_failures=true //:envoy
}

function do_test() {
  bazel test --test_output=all --test_env=ENVOY_IP_TEST_VERSIONS=v4only \
    //:echo2_integration_test
}

case "$1" in
build)
  do_build
  ;;
test)
  do_test
  ;;
*)
  echo "must be one of [build,test]"
  exit 1
  ;;
esac

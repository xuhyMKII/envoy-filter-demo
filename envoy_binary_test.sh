#!/bin/bash
#

# 检查Envoy的二进制文件是否已经成功生成并且可以被执行。

# 使用set -e命令，这个命令会让脚本在任何命令失败时立即退出。
set -e

# 试运行envoy --help命令。这个命令会打印Envoy的帮助信息，
# 并返回一个成功的退出码，如果Envoy的二进制文件已经成功生成并且可以被执行的话。
# Just test that the binary was produced and can be executed.
# envoy --help will give a success return code if working.
envoy --help

echo "PASS"

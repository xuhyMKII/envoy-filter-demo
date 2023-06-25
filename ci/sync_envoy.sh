#!/bin/bash

# 这个sync_envoy.sh脚本的主要功能是同步Envoy的最新代码到这个项目的Envoy子模块，并更新WORKSPACE文件。以下是它的详细步骤：

# 更新子模块：脚本首先获取Envoy源代码目录（$ENVOY_SRC_DIR）中的最新commit SHA（$ENVOY_SHA），然后比较这个SHA和当前子模块的SHA（$CURRENT_SHA）。如果这两个SHA相同，说明子模块已经是最新的，脚本就会退出。否则，脚本会更新子模块到最新的Envoy SHA。

# 更新WORKSPACE文件：脚本会用sed命令将$ENVOY_SRC_DIR/ci/WORKSPACE.filter.example文件中的{ENVOY_SRC_DIR}替换为envoy，然后将结果写入到WORKSPACE文件。

# 提交和推送：脚本会设置git的用户邮箱和用户名为环境变量$GITHUB_EMAIL和$GITHUB_NAME，然后提交所有的更改，并将更改推送到origin main。

# 这个脚本的主要目的是确保这个项目的Envoy子模块总是跟Envoy的最新代码保持同步。这对于确保这个项目可以使用Envoy的最新特性和修复非常重要。

set -e

echo "Updating Submodule..."
# Update submodule to latest Envoy SHA
ENVOY_SHA=$(git -C "$ENVOY_SRC_DIR" rev-parse HEAD)
CURRENT_SHA="$(git ls-files -s envoy | cut -d' ' -f2)"
COMMITTER_NAME="${GITHUB_NAME:-}"
COMMITTER_EMAIL="${GITHUB_EMAIL:-}"

if [[ "$CURRENT_SHA" == "$ENVOY_SHA" ]]; then
    echo "Submodule already up to date (${ENVOY_SHA})"
    exit 0
fi

git submodule update --init
git -C envoy/ checkout "$ENVOY_SHA"

echo "Updating Workspace file."
sed -e "s|{ENVOY_SRC_DIR}|envoy|" "${ENVOY_SRC_DIR}/ci/WORKSPACE.filter.example" >"WORKSPACE"

echo "Committing, and Pushing..."
git config --global user.email "$COMMITTER_EMAIL"
git config --global user.name "$COMMITTER_NAME"
git commit -a -m "Update Envoy submodule to $ENVOY_SHA"
git push origin main
echo "Done"

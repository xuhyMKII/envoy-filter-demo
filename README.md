# Envoy Filter Example

这个项目演示了如何将额外的过滤器链接到Envoy二进制文件。我们引入了两个新的过滤器：`sample`和`echo2`。`sample`过滤器是一个HTTP过滤器，它会添加一个HTTP头部。`echo2`过滤器与现有的[`echo`](https://github.com/envoyproxy/envoy/blob/master/source/extensions/filters/network/echo/echo.h)过滤器几乎相同，只是进行了重命名。我们还提供了演示过滤器端到端行为的集成测试。

## 构建

要构建Envoy静态二进制文件，请执行以下命令：

1. `git submodule update --init`
2. `bazel build //:envoy`（构建整个项目）
3. `bazel build //http-filter-example:envoy`（只构建`sample`过滤器）

## 测试

要运行`echo2`集成测试，请执行以下命令：

`bazel test //:echo2_integration_test`

要运行`sample`集成测试，请执行以下命令：

`bazel test //http-filter-example:http_filter_integration_test`

要运行此项目的常规Envoy测试，请执行以下命令：

`bazel test @envoy//test/...`

## 工作原理

[Envoy仓库](https://github.com/envoyproxy/envoy/)作为一个子模块提供。[`WORKSPACE`](WORKSPACE)文件将`@envoy`仓库映射到这个本地路径。

[`BUILD`](BUILD)文件引入了一个新的Envoy静态二进制目标`envoy`，它将新的过滤器和`@envoy//source/exe:envoy_main_entry_lib`链接在一起。`echo2`过滤器在Envoy二进制的静态初始化阶段注册自己作为一个新的过滤器。



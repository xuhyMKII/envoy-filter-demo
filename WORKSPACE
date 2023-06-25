-- WORKSPACE文件是Bazel构建系统使用的文件，它定义了项目的外部依赖项。

-- 定义了当前工作空间的名称为envoy_filter_example。
workspace(name = "envoy_filter_example")

-- 定义了一个名为envoy的本地仓库，路径为{ENVOY_SRCDIR}。这个本地仓库是Envoy的源代码。
local_repository(
    name = "envoy",
    path = "{ENVOY_SRCDIR}",
)

-- 这些函数加载了Envoy的一些Bazel函数，并调用这些函数来加载Envoy的依赖项。
-- 这些依赖项包括Envoy的API依赖项（envoy_api_dependencies）、
-- 其他依赖项（envoy_dependencies）、额外的依赖项（envoy_dependencies_extra）、
-- Python依赖项（envoy_python_dependencies）和导入的依赖项（envoy_dependency_imports）。

load("@envoy//bazel:api_binding.bzl", "envoy_api_binding")

envoy_api_binding()

load("@envoy//bazel:api_repositories.bzl", "envoy_api_dependencies")

envoy_api_dependencies()

load("@envoy//bazel:repositories.bzl", "envoy_dependencies")

envoy_dependencies()

load("@envoy//bazel:repositories_extra.bzl", "envoy_dependencies_extra")

envoy_dependencies_extra()

load("@envoy//bazel:python_dependencies.bzl", "envoy_python_dependencies")

envoy_python_dependencies()

load("@envoy//bazel:dependency_imports.bzl", "envoy_dependency_imports")

envoy_dependency_imports()


-- Bazel的WORKSPACE文件和BUILD文件一起用于定义和管理项目的依赖关系。

-- WORKSPACE文件定义了项目的外部依赖项，包括Envoy的源代码和Envoy的一些依赖项。
-- 这些依赖项在构建项目时会被Bazel下载和使用。

-- BUILD文件则定义了项目内部的构建规则，包括如何编译源代码、
-- 如何生成库和可执行文件、如何运行测试等。BUILD文件也可以指定源代码文件的依赖关系，
-- Bazel会根据这些依赖关系来确定构建的顺序。
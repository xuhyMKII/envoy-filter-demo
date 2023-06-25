// 入口方法
// 这个方法接收一个Buffer::
// Instance参数，这个参数包含了接收到的数据。方法首先记录了一个日志，然后将接收到的数据写回到连接中。最后，方法返回Network::
// FilterStatus::StopIteration，这表示过滤器已经完成了对数据的处理，不需要再调用其他的过滤器。

// 需要注意的是，这个方法是在过滤器的源代码中定义的，而不是在Envoy的配置文件中。当Envoy启动并加载这个过滤器时，它会执行这个方法。

#include "echo2.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "source/common/common/assert.h"

namespace Envoy {
namespace Filter {

Network::FilterStatus Echo2::onData(Buffer::Instance& data, bool) {
  ENVOY_CONN_LOG(trace, "echo: got {} bytes", read_callbacks_->connection(), data.length());
  read_callbacks_->connection().write(data, false);
  return Network::FilterStatus::StopIteration;
}

} // namespace Filter
} // namespace Envoy

// 如果想让过滤器接收typed_config中的参数，你需要在你的过滤器的代码中添加对这些参数的处理。具体来说，需要做以下几个步骤：

// 定义一个配置类，这个类的字段对应于typed_config中的参数。这个类需要继承自Envoy::Extensions::
// NetworkFilters::Common::FactoryBase或者Envoy::Extensions::HttpFilters::Common::
// FactoryBase，取决于过滤器是一个网络过滤器还是一个HTTP过滤器。

// 在过滤器的构造函数中，接收一个这个配置类的实例，并将它保存为过滤器的一个成员变量。

// 在过滤器的方法中，使用这个配置类的实例来获取和使用typed_config中的参数。

// #include "envoy/extensions/filters/network/common/factory_base.h"

// namespace Envoy {
// namespace Filter {

// // 配置类
// class Echo2Config : public Extensions::NetworkFilters::Common::FactoryBase {
// public:
//   Echo2Config(const nlohmann::json& config) {
//     // 解析配置
//     param1_ = config["param1"].get<std::string>();
//     param2_ = config["param2"].get<int>();
//   }

//   std::string param1() const { return param1_; }
//   int param2() const { return param2_; }

// private:
//   std::string param1_;
//   int param2_;
// };

// class Echo2 : public Network::ReadFilter {
// public:
//   Echo2(const Echo2Config& config) : config_(config) {}

//   Network::FilterStatus onData(Buffer::Instance& data, bool) override {
//     ENVOY_CONN_LOG(trace, "echo: got {} bytes", read_callbacks_->connection(), data.length());
//     ENVOY_CONN_LOG(trace, "param1: {}, param2: {}", read_callbacks_->connection(),
//     config_.param1(),
//                    config_.param2());
//     read_callbacks_->connection().write(data, false);
//     return Network::FilterStatus::StopIteration;
//   }

// private:
//   const Echo2Config& config_;
// };

// } // namespace Filter
// } // namespace Envoy

// 在这个示例中，Echo2Config类定义了两个参数param1和param2，这两个参数可以在typed_config中设置。Echo2过滤器在构造函数中接收一个Echo2Config的实例，并在onData方法中使用这个实例来获取和使用param1和param2。
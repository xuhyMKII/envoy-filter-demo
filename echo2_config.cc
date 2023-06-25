#include <string>

#include "echo2.h"

#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"

namespace Envoy {
namespace Server {
namespace Configuration {

// 定义了一个名为Echo2ConfigFactory的类，
// 这个类实现了NamedNetworkFilterConfigFactory接口，
// 用于创建Echo2过滤器的实例。

    /**
     * Config registration for the echo2 filter. @see NamedNetworkFilterConfigFactory.
     */
    class Echo2ConfigFactory : public NamedNetworkFilterConfigFactory {
public:
// 这个方法创建一个过滤器工厂，这个工厂可以创建Echo2过滤器的实例。这个方法忽略了其protobuf消息参数，因为Echo2过滤器不需要任何配置。

      Network::FilterFactoryCb
      createFilterFactoryFromProto(const Protobuf::Message&, FactoryContext&) override {
    return [](Network::FilterManager& filter_manager) -> void {
      filter_manager.addReadFilter(Network::ReadFilterSharedPtr{new Filter::Echo2()});
    };
  }

// 这个方法创建一个空的protobuf消息，这个消息可以用于接收过滤器的配置。
// 为Echo2过滤器不需要任何配置，所以这个方法返回一个空的Struct消息。
  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new Envoy::ProtobufWkt::Struct()};
  }

  std::string name() const override { return "echo2"; }


这个方法返回一个布尔值，表示这个过滤器是否是终端过滤器。
// 终端过滤器是指在过滤器链中的最后一个过滤器，
// 它直接与下游客户端或上游服务器交互。在这个例子中，Echo2过滤器是一个终端过滤器。

  bool isTerminalFilterByProto(const Protobuf::Message&, ServerFactoryContext&) override { return true; }
};

/**
 * Static registration for the echo2 filter. @see RegisterFactory.
 */


// 一个静态注册，用于将Echo2ConfigFactory注册到Envoy的过滤器配置工厂注册表中。
// 这样，当Envoy启动并加载配置时，它就可以找到Echo2ConfigFactory，
// 并使用它来创建Echo2过滤器的实例。

static Registry::RegisterFactory<Echo2ConfigFactory, NamedNetworkFilterConfigFactory> registered_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy

// 已经在.proto文件中定义了一个名为Echo2Config的消息，这个消息有两个字段：key和val。

// #include "echo2_config.h"

// #include "envoy/registry/registry.h"
// #include "envoy/server/filter_config.h"

// #include "echo2.h"

// namespace Envoy {
// namespace Server {
// namespace Configuration {

// class Echo2ConfigFactory : public NamedNetworkFilterConfigFactory {
// public:
//   // 注意：这里的方法返回类型和参数类型已经改变
//   Network::FilterFactoryCb
//   createFilterFactoryFromProtoTyped(const Echo2Config& proto_config,
//                                     Server::Configuration::FactoryContext&) override {
//     // 从protobuf消息中提取配置数据
//     std::string key = proto_config.key();
//     std::string val = proto_config.val();

//     // 创建过滤器工厂
//     return [key, val](Network::FilterManager& filter_manager) -> void {
//       filter_manager.addReadFilter(Network::ReadFilterSharedPtr{new Filter::Echo2(key, val)});
//     };
//   }

//   // 注意：这里的方法返回类型已经改变
//   ProtobufTypes::MessagePtr createEmptyConfigProtoTyped() override {
//     // 返回你的消息类型的新实例
//     return std::make_unique<Echo2Config>();
//   }

//   std::string name() const override { return "echo2"; }

//   bool isTerminalFilterByProtoTyped(const Echo2Config&) override { return true; }
// };

// // 注意：这里的注册宏已经改变
// REGISTER_FACTORY(Echo2ConfigFactory, NamedNetworkFilterConfigFactory);

// } // namespace Configuration
// } // namespace Server
// } // namespace Envoy

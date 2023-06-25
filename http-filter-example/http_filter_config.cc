#include <string>

#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"

#include "http-filter-example/http_filter.pb.h"
#include "http-filter-example/http_filter.pb.validate.h"
#include "http_filter.h"

namespace Envoy {
namespace Server {
namespace Configuration {

// 定义了一个名为HttpSampleDecoderFilterConfigFactory的类，这个类实现了NamedHttpFilterConfigFactory接口，用于创建和配置HTTP过滤器。
// NamedHttpFilterConfigFactory是Envoy内部的一个接口，它定义了创建HTTP过滤器配置的方法。当你创建一个自定义的HTTP过滤器时，你需要实现这个接口，以便Envoy可以创建和配置你的过滤器。

// NamedHttpFilterConfigFactory接口定义了以下几个方法：

// createFilterFactoryFromProto : 从protobuf配置消息创建一个过滤器工厂。

// createEmptyConfigProto : 创建一个空的protobuf配置消息。

// name: 返回过滤器的名字。
// 通过实现这个接口，你可以控制如何从配置数据创建和配置你的过滤器。这是实现自定义过滤器的一个重要步骤。

      class HttpSampleDecoderFilterConfigFactory : public NamedHttpFilterConfigFactory {
public:
  // createFilterFactoryFromProto：这个方法从protobuf配置消息创建一个过滤器工厂。它首先验证并转换protobuf配置消息，然后调用createFilter方法创建过滤器工厂。

      Http::FilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& proto_config, const std::string&,
                                   FactoryContext& context) override {

    return createFilter(Envoy::MessageUtil::downcastAndValidate<const sample::Decoder&>(
                            proto_config, context.messageValidationVisitor()),
                        context);
  }

  /**
   *  Return the Protobuf Message that represents your config incase you have config proto
   */

  // createEmptyConfigProto：这个方法创建一个空的protobuf配置消息。这个消息可以被填充配置数据，然后传递给createFilterFactoryFromProto方法。
      ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new sample::Decoder()};
  }

  std::string name() const override { return "sample"; }

private:

// createFilter：这个私有方法从protobuf配置消息创建一个过滤器工厂。它首先创建一个过滤器配置，然后创建一个过滤器，并将这个过滤器添加到过滤器链中。

  Http::FilterFactoryCb createFilter(const sample::Decoder& proto_config, FactoryContext&) {
    Http::HttpSampleDecoderFilterConfigSharedPtr config =
        std::make_shared<Http::HttpSampleDecoderFilterConfig>(
            Http::HttpSampleDecoderFilterConfig(proto_config));

    return [config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      auto filter = new Http::HttpSampleDecoderFilter(config);
      callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{filter});
    };
  }
};

/**
 * Static registration for this sample filter. @see RegisterFactory.
 */

// 静态注册代码，这段代码在程序启动时注册HttpSampleDecoderFilterConfigFactory，使其可以被Envoy的过滤器配置系统使用。

static Registry::RegisterFactory<HttpSampleDecoderFilterConfigFactory, NamedHttpFilterConfigFactory>
    register_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy

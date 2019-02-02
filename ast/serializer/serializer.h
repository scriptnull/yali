#pragma once

#include "../ast.h"
#include <memory>

namespace yali {
namespace ast {
namespace serializer {

class Serializer {
public:
    virtual std::ostream& serialize(std::ostream&, std::unique_ptr<yali::ast::AbstractSyntaxTree> const&) = 0;
    virtual ~Serializer() = default;
};

class MarkdownLevelTableSerializer: public Serializer {
public:
    std::ostream& serialize(std::ostream&, std::unique_ptr<yali::ast::AbstractSyntaxTree> const&);
};

class GraphvizSerializer: public Serializer {
public:    
    std::ostream& serialize(std::ostream&, std::unique_ptr<yali::ast::AbstractSyntaxTree> const&);
};

}
}
}
#include "parser.h"
#include <cctype>

namespace yali {
namespace parser {

Parser::Parser(std::istream & _stream) {
    stream = std::unique_ptr{_stream};

    blank = new blank{this};
    open_brac = new open_brac{this};
    func_name = new func_name{this};
    func_arg = new func_arg{this};
    close_brac = new close_brac{this};
    eof = new eof{this};

    state = blank;
}

std::unique_ptr<yali::ast::AbstractSyntaxTree> Parser::parse() {
    while (!stream.eof()) {
        stream.get(current_character);

        if (current_character == '(')
            state.on_open_brac();
        else if (current_character == ')')
            state.on_close_brac();
        else if (is_blank(current_character))
            state.on_blank();
        else if (is_alpha(current_character))
            state.on_alpha();
    }

    state.on_eof();
}

}
}
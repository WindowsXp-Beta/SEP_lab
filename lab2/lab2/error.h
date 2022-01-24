//
// Created by 魏新鹏 on 2022/1/17.
//

#ifndef ED_ERROR_H
#define ED_ERROR_H
#include <exception>
#include <string>

class EdException : public std::exception {
public:
    enum Type {
        BadCommand, LineNumberOutOfRange, NumberRangeError,
        DeleteRangeError, FileNameNotSpecified
    };
    explicit EdException(Type type) {
        switch (type) {
            case BadCommand:
                message_ = "Bad/Unknown command";
                break;
            case LineNumberOutOfRange:
                message_ = "Line number out of range";
                break;
            case NumberRangeError:
                message_ = "Number range error";
                break;
            case DeleteRangeError:
                message_ = "Delete range error";
                break;
            case FileNameNotSpecified:
                message_ = "Filename not specified";
                break;
            default:
                std::unexpected();
        }
    }
    const char *what() const noexcept override {
        return message_.data();
    }
private:
    std::string message_;
};

#endif //ED_ERROR_H

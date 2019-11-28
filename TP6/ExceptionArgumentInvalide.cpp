#include "ExceptionArgumentInvalide.h"

/**
ExceptionArgumentInvalide::ExceptionArgumentInvalide(QString const& s) noexcept
    :s_(s) {}

ExceptionArgumentInvalide::ExceptionArgumentInvalide(const ExceptionArgumentInvalide& eAI) {this->s_ = eAI.s_; }

ExceptionArgumentInvalide::~ExceptionArgumentInvalide(){}

void ExceptionArgumentInvalide::raise() const { throw *this; }

ExceptionArgumentInvalide * ExceptionArgumentInvalide::clone() const { return new ExceptionArgumentInvalide(*this); }

const char * ExceptionArgumentInvalide::what() const noexcept
{
    return this->s_.toStdString().c_str();
}
*/

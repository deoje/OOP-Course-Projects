#ifndef EXCEPTIONARGUMENTINVALIDE_H
#define EXCEPTIONARGUMENTINVALIDE_H

#include <QException>
#include <QString>

class ExceptionArgumentInvalide : public QException {

public:
    // Constructors
    ExceptionArgumentInvalide(QString const& s=" ") noexcept :s_(s) {}
    ExceptionArgumentInvalide(const ExceptionArgumentInvalide & eAI) {this->s_ = eAI.s_; }

    /*
    *   @brief raise() To throw this custom exception.
    */
    void raise() const override { throw *this; }

    /*
    *   @brief clone() To return a copy of this custom exception
    *   @return ExceptionArgumentInvalide* Pointer to the new dynamically allocated copy
    */
    ExceptionArgumentInvalide *clone() const override { return new ExceptionArgumentInvalide(*this); }

    /*
    *   @brief what() To return the actual message of this custom exception
    */
    const char * what() const noexcept override {

        // Apply transformation to the QString to obtain an array of `char` type
        return this->s_.toStdString().c_str();
    }

private:

    /*
    *   @brief s_ Attribute necessary to store the message of this custom exception
    */
    QString s_;
};
#endif // EXCEPTIONARGUMENTINVALIDE_H

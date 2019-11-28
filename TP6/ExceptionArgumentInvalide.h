#ifndef EXCEPTIONARGUMENTINVALIDE_H
#define EXCEPTIONARGUMENTINVALIDE_H

#include <QException>
#include <QString>

class ExceptionArgumentInvalide : public QException {

public:
    ExceptionArgumentInvalide(QString const& s=" ") noexcept :s_(s) {};
    ExceptionArgumentInvalide(const ExceptionArgumentInvalide & eAI) {this->s_ = eAI.s_; };
    ~ExceptionArgumentInvalide() override;

    void raise() const override { throw *this; };
    ExceptionArgumentInvalide *clone() const override { return new ExceptionArgumentInvalide(*this); };
    const char *what() const noexcept override {
        return this->s_.toStdString().c_str();
    };

private:
    QString s_;
};
#endif // EXCEPTIONARGUMENTINVALIDE_H

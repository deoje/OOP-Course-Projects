#ifndef EXCEPTIONARGUMENTINVALIDE_H
#define EXCEPTIONARGUMENTINVALIDE_H

#include <QException>
#include <QString>

class ExceptionArgumentInvalide : public QException {

public:
    ExceptionArgumentInvalide(QString const& s=" ") noexcept;
    ExceptionArgumentInvalide(const ExceptionArgumentInvalide & eAI);
    ~ExceptionArgumentInvalide() override;

    void raise() const override;
    ExceptionArgumentInvalide *clone() const override;
    const char *what() const noexcept override;

private:
    QString s_;
};
#endif // EXCEPTIONARGUMENTINVALIDE_H

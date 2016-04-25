#ifndef MODIFYASMBAR_HPP
#define MODIFYASMBAR_HPP

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "code_container.hpp"

class CodeContainer::ModifyASMBar : public QWidget
{
    Q_OBJECT
public:
    explicit ModifyASMBar(QWidget *parent = 0);

signals:

public slots:
private:
private:
    QLabel *modify;
    QLineEdit *text;
    QPushButton *ok;
};

#endif // MODIFYASMBAR_HPP

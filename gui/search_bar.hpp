#ifndef SEARCHBAR_HPP
#define SEARCHBAR_HPP

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>

class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = 0);

signals:

public slots:
private:
    QLabel *search;
    QLineEdit *text;
    QGroupBox *radiobox;
    QPushButton *next, *previous;
    QRadioButton *hex, *dec, *string;
};

#endif // SEARCHBAR_HPP

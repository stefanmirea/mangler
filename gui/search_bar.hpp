#ifndef SEARCHBAR_HPP
#define SEARCHBAR_HPP

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QGroupBox>
#include <QRadioButton>

class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = 0);

signals:

public slots:
private:
    QLabel *search;
    QTextEdit *text;
    QGroupBox *radiobox;
    QRadioButton *hex, *dec, *string;
};

#endif // SEARCHBAR_HPP

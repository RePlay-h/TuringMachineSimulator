#ifndef MACHINE_H
#define MACHINE_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QDebug>
#include <QObject>

struct Сonfiguration {
    int state;
    int mv;
    QChar word;
};

class Machine : public QObject
{
    Q_OBJECT
signals:
    void MoveTo(int step);
    void ChangeItem(QChar word);
    void StopCircle();

public slots:
    void GetWord(QChar word);

public:
    Machine();
    void Init(QVector<QVector<Сonfiguration>> *table, QStringList* alp);
    void ResetMachine();
private:
    QString word_;
    int state_;

    QVector<QVector<Сonfiguration>> *table_;
    QStringList *alp_;
};

#endif // MACHINE_H

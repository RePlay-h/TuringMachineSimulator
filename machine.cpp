#include "machine.h"
#include <iostream>
Machine::Machine() : word_{""}, state_{0}, table_{nullptr}, alp_{nullptr} {}

void Machine::Init(QVector<QVector<Сonfiguration>> *table, QStringList *alp) {
    table_ = table;
    alp_ = alp;

    //StartCircle();
}

void Machine::ResetMachine() {
    word_ = "";
    state_ = 0;
}

void Machine::GetWord(QChar word) {
    word_ = word;


    Сonfiguration &conf = (*table_)[state_][alp_->indexOf(word_)];

    qDebug() << '[' << conf.word << conf.mv << conf.state << ']';

    if(conf.word == word_ && conf.state == state_ && conf.mv == 0) {
        emit StopCircle();
    }
    else {
        emit ChangeItem(conf.word);
        emit MoveTo(conf.mv);
        state_ = conf.state;
    }


}


//
// Created by 13191 on 2023/8/3.
//

#include "TaskCat.h"

TaskCat::TaskCat(QString task) {
    this->task = task;
}

TaskCat::TaskCat(QString task, QString pre, QString pst) {
    this->task = task;
    this->pre = pre;
    this->pst = pst;
}

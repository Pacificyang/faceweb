#ifndef FACEDNN_H
#define FACEDNN_H

#include <QObject>
#include <QList>
#include "ExtractFeature_.h"
#include "FaceDetect.h"
#include "ComputeDistance.h"
#include "Register.h"
#include "Recognition.h"
#include <time.h>
#include "qtsinglecoreapplication.h"

class FaceDnn : public QObject
{
    Q_OBJECT
public:
    explicit FaceDnn(QObject *parent = 0);

    vector<string> getModelList(QByteArray);
    string getUser(QByteArray);
    string userRegister(string,QByteArray);
signals:

public slots:

private:
    Recognition m_model;
    Recognition m_user;
};

#endif // FACEDNN_H

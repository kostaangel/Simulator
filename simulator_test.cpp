#include "simulator_test.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QSslError>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QFile>
#include <QAuthenticator>
#include <QGridLayout>
#include <QDateTime>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include "qcompressor.h"
#include "initjobbox.h"

Simulator_Test::Simulator_Test(QWidget *parent)
    : QWidget(parent)
{
    m_nam = new QNetworkAccessManager();

    connect(m_nam, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), this, SLOT(sslErrorIgnore(QNetworkReply*, QList<QSslError>)));
    connect(m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
//    connect(m_nam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticationNeeded(QNetworkReply*,QAuthenticator*)));
//    connect(m_nam, SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)), this, SLOT(testFunc()));

    setupUi();

//    initJobRequest();
//    QString filename = "/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/initJobReturnMessageRequest.xml";
//    QFile file( filename );
//    if ( file.open(QIODevice::ReadOnly) )
//    {
//        QTextStream stream( &file );
//        QString text = stream.readAll();
//        qDebug()<<text;


//        QByteArray compressedText;
//        QCompressor::gzipCompress(text.toLatin1(), compressedText);

//        qDebug()<<"compressedText = "<<compressedText.toBase64();

//        QByteArray decompressedText;
//        QCompressor::gzipDecompress(compressedText.toBase64(), decompressedText);

//        qDebug()<<"decompressedText = "<<decompressedText;
//    }


//    file.close();
}

Simulator_Test::~Simulator_Test()
{

}

void Simulator_Test::setupUi()
{
    QGridLayout *mainLayout = new QGridLayout();

    m_initJobBtn = new QPushButton("InitJob", this);
    m_GetPricesTechnicalJob_getDataByIdBtn = new QPushButton("GetPricesTechnicalJob_getDataById", this);
    m_GetPricesTechnicalJobResponceBtn = new QPushButton("GetPricesTechnicalJobResponce", this);
    m_GetPricesTechnicalJob_Deactivated_Request_getDataByIdBtn = new QPushButton("GetPricesTechnicalJob_Deactivated_Request_getDataById", this);
    m_GetPricesTechnicalJob_Deactivated_ResponseBtn = new QPushButton("GetPricesTechnicalJob_Deactivated_Response", this);
    m_TransferJobToDms_Request_getDataByIdBtn = new QPushButton("TransferJobToDms_Request_getDataById", this);
    m_TransferJobToDms_ResponseBtn = new QPushButton("TransferJobToDms_Response", this);
    m_TransferJobToErepko_ResponseBtn = new QPushButton("TransferJobToErepko_Response", this);
    m_FinishOrderResponseBtn = new QPushButton("FinishOrderResponse", this);
    m_GetInvoiceCodesRequest_getDataByIdBtn = new QPushButton("GetInvoiceCodesRequest_getDataById", this);
    m_GetInvoiceCodesResponseBtn = new QPushButton("GetInvoiceCodesResponse", this);
    m_RunVerificationRequest_getDataByIdBtn = new QPushButton("RunVerificationRequest_getDataById", this);
    m_RunVerificationResponseBtn = new QPushButton("RunVerificationResponse", this);
    m_GetLocalOperationsRequest_getDataByIdBtn = new QPushButton("GetLocalOperationsRequest_getDataById", this);
    m_GetLocalOperationsResponseBtn = new QPushButton("GetLocalOperationsResponse", this);
    m_ServiceFault_from_DMSBtn = new QPushButton("ServiceFault_from_DMS", this);
    m_ServiceFault_from_XENTRY_PortalBtn = new QPushButton("ServiceFault_from_XENTRY_Portal", this);

    m_ConnectPartsListAndOrderRequestBtn = new QPushButton("ConnectPartsListAndOrderRequest", this);
    m_GetDetailsFromPartsSearchRequestBtn = new QPushButton("GetDetailsFromPartsSearchRequest", this);
    m_GetPricesPartsResponseBtn = new QPushButton("GetPricesPartsResponse", this);

    mainLayout->addWidget(m_initJobBtn, 0, 0, 1, 1);
    mainLayout->addWidget(m_GetPricesTechnicalJob_getDataByIdBtn, 1, 0, 1, 1);
    mainLayout->addWidget(m_GetPricesTechnicalJobResponceBtn, 2, 0, 1, 1);
    mainLayout->addWidget(m_GetPricesTechnicalJob_Deactivated_Request_getDataByIdBtn, 3, 0, 1, 1);
    mainLayout->addWidget(m_GetPricesTechnicalJob_Deactivated_ResponseBtn, 4, 0, 1, 1);
    mainLayout->addWidget(m_TransferJobToDms_Request_getDataByIdBtn, 5, 0, 1, 1);
    mainLayout->addWidget(m_TransferJobToDms_ResponseBtn, 6, 0, 1, 1);
    mainLayout->addWidget(m_TransferJobToErepko_ResponseBtn, 7, 0, 1, 1);
    mainLayout->addWidget(m_FinishOrderResponseBtn, 9, 0, 1, 1);
    mainLayout->addWidget(m_GetInvoiceCodesRequest_getDataByIdBtn, 10, 0, 1, 1);
    mainLayout->addWidget(m_GetInvoiceCodesResponseBtn, 11, 0, 1, 1);
    mainLayout->addWidget(m_RunVerificationRequest_getDataByIdBtn, 12, 0, 1, 1);
    mainLayout->addWidget(m_RunVerificationResponseBtn, 13, 0, 1, 1);
    mainLayout->addWidget(m_GetLocalOperationsRequest_getDataByIdBtn, 14, 0, 1, 1);
    mainLayout->addWidget(m_GetLocalOperationsResponseBtn, 15, 0, 1, 1);
    mainLayout->addWidget(m_ServiceFault_from_DMSBtn, 16, 0, 1, 1);
    mainLayout->addWidget(m_ServiceFault_from_XENTRY_PortalBtn, 17, 0, 1, 1);
    mainLayout->addWidget(m_ConnectPartsListAndOrderRequestBtn, 0, 1, 1, 1);
    mainLayout->addWidget(m_GetDetailsFromPartsSearchRequestBtn, 1, 1, 1, 1);
    mainLayout->addWidget(m_GetPricesPartsResponseBtn, 2, 1, 1, 1);

    setLayout(mainLayout);

    connect(m_initJobBtn, SIGNAL(clicked(bool)), this, SLOT(initJobRequest()));
    connect(m_GetPricesTechnicalJob_getDataByIdBtn, SIGNAL(clicked(bool)), this, SLOT(GetPricesTechnicalJob_getDataByIdSlot()));
    connect(m_GetPricesTechnicalJobResponceBtn, SIGNAL(clicked(bool)), this, SLOT(GetPricesTechnicalJobResponceSlot()));
    connect(m_GetPricesTechnicalJob_Deactivated_Request_getDataByIdBtn, SIGNAL(clicked(bool)),
            this, SLOT(GetPricesTechnicalJob_Deactivated_Request_getDataByIdSlot()));
    connect(m_GetPricesTechnicalJob_Deactivated_ResponseBtn, SIGNAL(clicked(bool)),
            this, SLOT(GetPricesTechnicalJob_Deactivated_ResponseSlot()));
    connect(m_TransferJobToDms_Request_getDataByIdBtn, SIGNAL(clicked(bool)), this, SLOT(TransferJobToDms_Request_getDataByIdSlot()));
    connect(m_TransferJobToDms_ResponseBtn, SIGNAL(clicked(bool)), this, SLOT(TransferJobToDms_ResponseSlot()));
    connect(m_TransferJobToErepko_ResponseBtn, SIGNAL(clicked(bool)), this, SLOT(TransferJobToErepko_ResponseSlot()));
    connect(m_FinishOrderResponseBtn, SIGNAL(clicked(bool)), this, SLOT(FinishOrderResponseSlot()));
    connect(m_GetInvoiceCodesRequest_getDataByIdBtn, SIGNAL(clicked(bool)), this, SLOT(GetInvoiceCodesRequest_getDataByIdSlot()));
    connect(m_GetInvoiceCodesResponseBtn, SIGNAL(clicked(bool)), this, SLOT(GetInvoiceCodesResponseSlot()));
    connect(m_RunVerificationRequest_getDataByIdBtn, SIGNAL(clicked(bool)), this, SLOT(RunVerificationRequest_getDataByIdSlot()));
    connect(m_RunVerificationResponseBtn, SIGNAL(clicked(bool)), this, SLOT(RunVerificationResponseSlot()));
    connect(m_GetLocalOperationsRequest_getDataByIdBtn, SIGNAL(clicked(bool)), this, SLOT(GetLocalOperationsRequest_getDataByIdSlot()));
    connect(m_GetLocalOperationsResponseBtn, SIGNAL(clicked(bool)), this, SLOT(GetLocalOperationsResponseSlot()));
    connect(m_ServiceFault_from_DMSBtn, SIGNAL(clicked(bool)), this, SLOT(ServiceFault_from_DMSSlot()));
    connect(m_ServiceFault_from_XENTRY_PortalBtn, SIGNAL(clicked(bool)), this, SLOT(ServiceFault_from_XENTRY_PortalSlot()));

    connect(m_ConnectPartsListAndOrderRequestBtn, SIGNAL(clicked(bool)), this, SLOT(ConnectPartsListAndOrderRequestSlot()));
    connect(m_GetDetailsFromPartsSearchRequestBtn, SIGNAL(clicked(bool)), this, SLOT(GetDetailsFromPartsSearchRequestSlot()));
    connect(m_GetPricesPartsResponseBtn, SIGNAL(clicked(bool)), this, SLOT(GetPricesPartsResponseSlot()));
}

void Simulator_Test::finished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray replyByteArray = reply->readAll();
        QString replyString = QString(replyByteArray);
        qDebug()<<"replyString = "<<replyString;
        parseXml(replyByteArray);
    }
    else
    {
        qDebug()<<"reply = "<<reply->readAll();
        qDebug()<<"Error = "<<reply->errorString();
    }

}

void Simulator_Test::sslErrorIgnore(QNetworkReply* reply, const QList<QSslError> & errors)
{
    qDebug()<<"sslErrorIgnore();";
    reply->ignoreSslErrors();
}

void Simulator_Test::initJobRequest()
{
//    InitJobBox *form = new InitJobBox(this);
//    form->exec();

//    return;
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));
//    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/Server?action=connect&id=GS0004675"));
//    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/Server"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");
//    request.setRawHeader("Accept-Encoding", "gzip");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/InitJob_Request_Basic.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

//    QByteArray fajlText = form->createInitJobXml().toAscii();
    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);
    qDebug()<<"initJobRequest(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qDebug()<<fajlText;
//    createInitJobXml();

}

void Simulator_Test::GetPricesTechnicalJob_getDataByIdSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"GetDataById\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesTechnicalJob_Request_getDataById.xml", this);
//    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/InitJob_Request_01.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetPricesTechnicalJob_getDataByIdSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetPricesTechnicalJobResponceSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesTechnicalJob_Response.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetPricesTechnicalJobResponceSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetPricesTechnicalJob_Deactivated_Request_getDataByIdSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"GetDataById\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesTechnicalJob_Deactivated_Request_getDataById.xml", this);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetPricesTechnicalJob_Deactivated_Request_getDataByIdSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetPricesTechnicalJob_Deactivated_ResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesTechnicalJob_Deactivated_Response.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetPricesTechnicalJob_Deactivated_ResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::TransferJobToDms_Request_getDataByIdSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"GetDataById\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/TransferJobToDms_Request_getDataById.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"TransferJobToDms_Request_getDataByIdSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::TransferJobToDms_ResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

//    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/TransferJobToDms_Response.xml", this);
    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/TransferJobToDms_Request_Basic.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"TransferJobToDms_ResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::TransferJobToErepko_ResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/TransferJobToErepko_Request.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"TransferJobToErepko_ResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::FinishOrderResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/FinishOrderRequest.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"FinishOrderResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetInvoiceCodesRequest_getDataByIdSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"GetDataById\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetInvoiceCodesRequest_getDataById.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetInvoiceCodesRequest_getDataByIdSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetInvoiceCodesResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetInvoiceCodesResponse.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetInvoiceCodesResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::RunVerificationRequest_getDataByIdSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"GetDataById\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/RunVerificationRequest_getDataById.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"RunVerificationRequest_getDataByIdSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::RunVerificationResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/RunVerificationResponse.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"RunVerificationResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetLocalOperationsRequest_getDataByIdSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"GetDataById\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetLocalOperationsRequest_getDataById.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetLocalOperationsRequest_getDataByIdSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetLocalOperationsResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetLocalOperationsResponse.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetLocalOperationsResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::ServiceFault_from_DMSSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/ServiceFault_from_DMS.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"ServiceFault_from_DMSSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::ServiceFault_from_XENTRY_PortalSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/InitJob_Request_ServiceFault.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"ServiceFault_from_XENTRY_PortalSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::ConnectPartsListAndOrderRequestSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/ConnectPartsListAndOrderRequest.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"ConnectPartsListAndOrderRequestSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetDetailsFromPartsSearchRequestSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetDetailsFromPartsSearchRequest.xml", this);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetDetailsFromPartsSearchRequestSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetPricesPartsResponseSlot()
{
//    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));
    QUrl url(QString("https://srs-ds-int1.i.daimler.com/STARCDS/services/ExternalInterface"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesPartsResponse.xml", this);
//    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesPartsRequest.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetPricesPartsResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::authenticationNeeded(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qDebug()<<"authenticationNeeded();";
//    authenticator->setUser("DSP10201");
//    authenticator->setPassword("dsp10201P");
}

void Simulator_Test::testFunc()
{
    qDebug()<<"testFunc();";
}

void Simulator_Test::parseXml(QByteArray replyString)
{
    QDomDocument *doc = new QDomDocument();

    doc->setContent(replyString);



    QDomElement root = doc->documentElement();
    QDomElement compressedData = root.firstChildElement("soapenv:Body").firstChildElement("stcdsext:sendSyncDataResponse")
            .firstChildElement("stcdsext:data").firstChildElement("stcds:compressedData");

    qDebug()<<"compressedData = "<<compressedData.text().toLatin1();
    QStringList compresedList = compressedData.text().split("\r");
//    for(int i = 0;i < compresedList.length();i++)
//    {
//        qDebug()<<i<<" - "<<compresedList.at(i);
//        qDebug()<<qUncompress(compresedList.at(i).toAscii());
//    }

    int startPos = 0;
    int endPos = 0;
    for(int i = 0;i<replyString.length();i++)
    {
        if(replyString.left(i).endsWith("<stcds:compressedData stcds:compression=\"GZIP\">"))
            startPos = i;

        if(replyString.right(i).startsWith("</stcds:compressedData>"))
        {
//            qDebug()<<i<<" - "<<replyString.right(i);
            endPos = replyString.length() - i;
        }
    }


//    qDebug()<<startPos<<", "<<endPos;
//    qDebug()<<"result = "<<replyString.mid(startPos, endPos - startPos);

//    QByteArray decompress;
//    if(QCompressor::gzipDecompress(compressedData.text().toLatin1(), decompress))
//        qDebug()<<"decompress = "<<decompress;
//    else
//        qDebug()<<"ne moze da se dekompresira";

    QByteArray text4Decompresion = QByteArray::fromBase64(compressedData.text().toLatin1());

    qDebug()<<"gUncompress - "<<gUncompress(text4Decompresion);
//    qDebug()<<"gzipDecompress() = "<<gzipDecompress(compressedData.text().toLatin1());

//    QFile *fi = new QFile("/home/kostadin/brisi.txt.gz", this);
    QString filename = "/home/kostadin32/brisi.txt.gz";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << QByteArray::fromBase64(compressedData.text().toLatin1());
    }


    file.close();
//    QByteArray decompress;
//    QCompressor::gzipDecompress(compressedData.text().toLatin1(), decompress);

//    qDebug()<<"decompress = "<<qUncompress(compressedData.text().toAscii());

}

void Simulator_Test::createInitJobXml()
{
    QDomDocument *domDocument = new QDomDocument();

    QDomElement envelopeElement = domDocument->createElement("env:Envelope");
    envelopeElement.setAttribute("xmlns:env", "http://www.w3.org/2003/05/soap-envelope");

    QDomElement headerElement = domDocument->createElement("env:Header");
    envelopeElement.appendChild(headerElement);

    QDomElement securityElement = domDocument->createElement("wsse:Security");
    securityElement.setAttribute("xmlns:wsse", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd");
    headerElement.appendChild(securityElement);

    QDomElement usernameTokenElement = domDocument->createElement("wsse:UsernameToken");
    securityElement.appendChild(usernameTokenElement);

    QDomElement usernameElement = domDocument->createElement("wsse:Username");
    QDomText usernameText = domDocument->createTextNode("DSP10201");
    usernameElement.appendChild(usernameText);
    usernameTokenElement.appendChild(usernameElement);

    QDomElement passwordElement = domDocument->createElement("wsse:Password");
    passwordElement.setAttribute("Type", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText");
    QDomText passwordText = domDocument->createTextNode("dsp10201P");
    passwordElement.appendChild(passwordText);
    usernameTokenElement.appendChild(passwordElement);

    QDomElement bodyElement = domDocument->createElement("env:Body");
    envelopeElement.appendChild(bodyElement);

    QDomElement sendSyncDataRequestElement = domDocument->createElement("ext:sendSyncDataRequest");
    sendSyncDataRequestElement.setAttribute("ext:version", "1.4");
    sendSyncDataRequestElement.setAttribute("xsi:schemaLocation", "http://stc.daimler.com/2009/08/DS/ext file:///C:/Xentry_Portal/Schnittstellen_Spezifikationen/XML-Schema_V_1.4.5/XML-Instanzen-V1.4.5/03_DataServer_Instanzen/XML-Artefacts/XML-Artefacts/StarConnectDataServerExt.xsd");
    bodyElement.appendChild(sendSyncDataRequestElement);

    QDomElement typeElement = domDocument->createElement("ext:type");
    QDomText typeText = domDocument->createTextNode("SERVICE_JOB_z");
    typeElement.appendChild(typeText);
    sendSyncDataRequestElement.appendChild(typeElement);

    QDomElement eventElement = domDocument->createElement("ext:event");
    QDomText eventText = domDocument->createTextNode("UPDATE");
    eventElement.appendChild(eventText);
    sendSyncDataRequestElement.appendChild(eventElement);

    QDomElement dataElement = domDocument->createElement("ext:data");
    sendSyncDataRequestElement.appendChild(dataElement);

    domDocument->appendChild(envelopeElement);

    qDebug()<<domDocument->toString();
}

QByteArray Simulator_Test::gUncompress(const QByteArray &data)
{
    if (data.size() <= 4) {
        qWarning("gUncompress: Input data is truncated");
        return QByteArray();
    }

    qDebug()<<data.size();

    QByteArray result;

    int ret;
    z_stream strm;
    static const int CHUNK_SIZE = 32*1024;//1024;
    char out[CHUNK_SIZE];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = data.size();
    strm.next_in = (Bytef*)(data.data());

    ret = inflateInit2(&strm, 15 + 32); // gzip decoding
    if (ret != Z_OK)
        return QByteArray();


    // run inflate()
    do {
        strm.avail_out = CHUNK_SIZE;
        strm.next_out = (Bytef*)(out);

        ret = inflate(&strm, Z_NO_FLUSH);

        Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

//        qDebug()<<"ret = "<<ret;
        switch (ret) {
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR;     // and fall through
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            (void)inflateEnd(&strm);
            return QByteArray();
        }

        result.append(out, CHUNK_SIZE - strm.avail_out);
    } while (strm.avail_out == 0);

    // clean up and return
    inflateEnd(&strm);
    return result;
}

QByteArray Simulator_Test::gzipDecompress( QByteArray compressData )
{
    //strip header
        compressData.remove(0, 10);

        const int buffer_size = 32*1024;
        quint8 buffer[buffer_size];

        z_stream cmpr_stream;
        cmpr_stream.next_in = (unsigned char *)compressData.data();
        cmpr_stream.avail_in = compressData.size();
        cmpr_stream.total_in = 0;

        cmpr_stream.next_out = buffer;
        cmpr_stream.avail_out = buffer_size;
        cmpr_stream.total_out = 0;

        cmpr_stream.zalloc = Z_NULL;
        cmpr_stream.zfree = Z_NULL;
        cmpr_stream.opaque = Z_NULL;

        int status = inflateInit2( &cmpr_stream, -8 );
        if (status != Z_OK) {
            qDebug() << "cmpr_stream error!";
        }

        QByteArray uncompressed;
        do {
            cmpr_stream.next_out = buffer;
            cmpr_stream.avail_out = buffer_size;

            status = inflate( &cmpr_stream, Z_NO_FLUSH );

            if (status == Z_OK || status == Z_STREAM_END)
            {
                QByteArray chunk = QByteArray::fromRawData((char *)buffer, buffer_size - cmpr_stream.avail_out);
                uncompressed.append( chunk );
            }
            else
            {
                inflateEnd(&cmpr_stream);
                break;
            }

            if (status == Z_STREAM_END)
            {
                inflateEnd(&cmpr_stream);
                break;
            }
        }
        while (cmpr_stream.avail_out == 0);

        return uncompressed;
}

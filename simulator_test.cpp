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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/InitJob_Request_01.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);
    qDebug()<<"initJobRequest(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
//    createInitJobXml();

}

void Simulator_Test::GetPricesTechnicalJob_getDataByIdSlot()
{
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesTechnicalJob_Response.xml", this);
//    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/InitJob_Request_01.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetPricesTechnicalJobResponceSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetPricesTechnicalJob_Deactivated_Request_getDataByIdSlot()
{
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/TransferJobToDms_Response.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"TransferJobToDms_ResponseSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::TransferJobToErepko_ResponseSlot()
{
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

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
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncData\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetDetailsFromPartsSearchRequest.xml", this);
//    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/InitJob_Request_01.xml", this);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QByteArray fajlText = file->readAll();

    m_nam->post(request, fajlText);

    qDebug()<<"GetDetailsFromPartsSearchRequestSlot(); - "<<QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
}

void Simulator_Test::GetPricesPartsResponseSlot()
{
    QUrl url(QString("http://192.166.58.228/dmstt/rest/xpSimulator/2_4"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/soap+xml;charset=UTF-8;action=\"SendSyncResponse\"");

    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/XML_primeri/GetPricesPartsResponse.xml", this);
//    QFile *file = new QFile("/home/kostadin32/Documents/Knigi/Xentry/InitJob_Request_01.xml", this);
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

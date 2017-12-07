#include "initjobbox.h"
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
#include <QGridLayout>
#include <QLabel>

InitJobBox::InitJobBox(QWidget *parent) : QDialog(parent)
{
    m_daimlerUser = "D5ANGELK";
    m_dmsUser = "D5ANGELK";

    QGridLayout *mainLayout = new QGridLayout();

    m_orderIdEdit = new QLineEdit("abc", this);
    m_receptionDate = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    m_returnDate = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    m_serviceAdvisorFirstNameEdit = new QLineEdit("Kostadin", this);
    m_serviceAdvisorLastNameEdit = new QLineEdit("Angelov", this);

    m_FinOrVinEdit = new QLineEdit("WDD2120981A723973", this);
    m_FirstRegistrationDate = new QDateEdit(QDate::currentDate(), this);
    m_OdometerReadingEdit = new QLineEdit("51002", this);
    m_OperatingHoursEdit = new QLineEdit("90000", this);
    m_RegistrationNumberEdit = new QLineEdit("SK 5437 AM", this);

    m_customerFirstNameEdit = new QLineEdit("Kostadin", this);
    m_customerLastNameEdit = new QLineEdit("Angelov", this);
    m_customerPhoneNumberEdit = new QLineEdit("071548452", this);

    m_initJobBtn = new QPushButton(tr("Init job"), this);
    m_cancelBtn = new QPushButton(tr("Cancel"));

    mainLayout->addWidget(new QLabel("orderId:", this), 0, 0, 1, 1);
    mainLayout->addWidget(m_orderIdEdit, 0, 1, 1, 1);
    mainLayout->addWidget(new QLabel("reception date:"), 1, 0, 1, 1);
    mainLayout->addWidget(m_receptionDate, 1, 1, 1, 1);
    mainLayout->addWidget(new QLabel("return date:"), 2, 0, 1, 1);
    mainLayout->addWidget(m_returnDate, 2, 1, 1, 1);
    mainLayout->addWidget(new QLabel("advisor firsname:", this), 3, 0, 1, 1);
    mainLayout->addWidget(m_serviceAdvisorFirstNameEdit, 3, 1, 1, 1);
    mainLayout->addWidget(new QLabel("advisor lastname:", this), 4, 0, 1, 1);
    mainLayout->addWidget(m_serviceAdvisorLastNameEdit, 4, 1, 1, 1);
    mainLayout->addWidget(new QLabel("FinOrVin:", this), 5, 0, 1, 1);
    mainLayout->addWidget(m_FinOrVinEdit, 5, 1, 1, 1);
    mainLayout->addWidget(new QLabel("first reg.date:", this), 6, 0, 1, 1);
    mainLayout->addWidget(m_FirstRegistrationDate, 6, 1, 1, 1);
    mainLayout->addWidget(new QLabel("Odometer reading:", this), 7, 0, 1, 1);
    mainLayout->addWidget(m_OdometerReadingEdit, 7, 1, 1, 1);
    mainLayout->addWidget(new QLabel("Operating hours:", this), 8, 0, 1, 1);
    mainLayout->addWidget(m_OperatingHoursEdit, 8, 1, 1, 1);
    mainLayout->addWidget(new QLabel("Registration number", this), 9, 0, 1, 1);
    mainLayout->addWidget(m_RegistrationNumberEdit, 9, 1, 1, 1);
    mainLayout->addWidget(new QLabel("Customer firstname:", this), 10, 0, 1, 1);
    mainLayout->addWidget(m_customerFirstNameEdit, 10, 1, 1, 1);
    mainLayout->addWidget(new QLabel("Customer lastname:", this), 11, 0, 1, 1);
    mainLayout->addWidget(m_customerLastNameEdit, 11, 1, 1, 1);
    mainLayout->addWidget(new QLabel("Customer phone no."), 12, 0, 1, 1);
    mainLayout->addWidget(m_customerPhoneNumberEdit, 12, 1, 1, 1);
    mainLayout->addWidget(m_initJobBtn, 0, 2, 1, 1);
    mainLayout->addWidget(m_cancelBtn, 0, 3, 1, 1);

    setLayout(mainLayout);

    connect(m_initJobBtn, SIGNAL(clicked(bool)), this, SLOT(initBtnPressed()));
    connect(m_cancelBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void InitJobBox::initBtnPressed()
{
    accept();
}

QString InitJobBox::createInitJobXml()
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
    QDomText usernameText = domDocument->createTextNode("TD02234");
    usernameElement.appendChild(usernameText);
    usernameTokenElement.appendChild(usernameElement);

    QDomElement passwordElement = domDocument->createElement("wsse:Password");
    passwordElement.setAttribute("Type", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText");
    QDomText passwordText = domDocument->createTextNode("QmrkeC7RXQ");
    passwordElement.appendChild(passwordText);
    usernameTokenElement.appendChild(passwordElement);

    QDomElement bodyElement = domDocument->createElement("env:Body");
    envelopeElement.appendChild(bodyElement);

    QDomElement sendSyncDataRequestElement = domDocument->createElement("ext:sendSyncDataRequest");
    sendSyncDataRequestElement.setAttribute("ext:version", "1.4");
    sendSyncDataRequestElement.setAttribute("xsi:schemaLocation", "http://stc.daimler.com/2009/08/DS/ext file:///C:/Xentry_Portal/Schnittstellen_Spezifikationen/XML-Schema_V_1.4.5/XML-Instanzen-V1.4.5/03_DataServer_Instanzen/XML-Artefacts/XML-Artefacts/StarConnectDataServerExt.xsd\" xmlns:ext=\"http://stc.daimler.com/2009/08/DS/ext\" xmlns:ds=\"http://stc.daimler.com/2009/08/DS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance");
    bodyElement.appendChild(sendSyncDataRequestElement);

    QDomElement extTypeElement = domDocument->createElement("ext:type");
    QDomText typeText = domDocument->createTextNode("SERVICE_JOB_7");
    extTypeElement.appendChild(typeText);
    sendSyncDataRequestElement.appendChild(extTypeElement);

    QDomElement eventElement = domDocument->createElement("ext:event");
    QDomText eventText = domDocument->createTextNode("UPDATE");
    eventElement.appendChild(eventText);
    sendSyncDataRequestElement.appendChild(eventElement);

    QDomElement operationElement = domDocument->createElement("ext:operation");
    QDomText operationText = domDocument->createTextNode("InitJob");
    operationElement.appendChild(operationText);
    sendSyncDataRequestElement.appendChild(operationElement);

    QDomElement dataElement = domDocument->createElement("ext:data");
    sendSyncDataRequestElement.appendChild(dataElement);

    QDomElement structuredDataElement = domDocument->createElement("ds:structuredData");
    QDomElement messageElement = domDocument->createElement("env:Message");
    messageElement.setAttribute("xsi:schemaLocation", "http://dms.ri.as.daimler.com/DMSService IF_XP_DMS_2_4_message_envelope.xsd http://dms.ri.as.daimler.com/DMSService/dms_sending IF_XP_DMS_2_4_dms_sending.xsd http://dms.ri.as.daimler.com/DMSService/types IF_XP_DMS_2_4_types.xsd http://dms.ri.as.daimler.com/DMSService/currencies IF_XP_DMS_2_4_currencies.xsd http://dms.ri.as.daimler.com/DMSService/xp_sending IF_XP_DMS_2_4_xp_sending.xsd http://ws.eskulabdec.daimler.com/ IF_XP_DMS_2_4_eskulab_decision.xsd \" xmlns:cur=\"http://dms.ri.as.daimler.com/DMSService/currencies\" xmlns:dms=\"http://dms.ri.as.daimler.com/DMSService/dms_sending\" xmlns:env=\"http://dms.ri.as.daimler.com/DMSService\" xmlns:types=\"http://dms.ri.as.daimler.com/DMSService/types\" xmlns:xp=\"http://dms.ri.as.daimler.com/DMSService/xp_sending");

    QDomElement businessContextElement = domDocument->createElement("env:BusinessContext");

    QDomElement dmsTypeElement = domDocument->createElement("env:DmsType");
    QDomText dmsTypeElementText = domDocument->createTextNode("SampleDMS SOAPUI");
    dmsTypeElement.appendChild(dmsTypeElementText);
    businessContextElement.appendChild(dmsTypeElement);

    QDomElement dmsVersionElement = domDocument->createElement("env:DmsVersion");
    QDomText dmsVersionElementText = domDocument->createTextNode("Sample DMS Version 10.5a");
    dmsVersionElement.appendChild(dmsVersionElementText);
    businessContextElement.appendChild(dmsVersionElement);

    QDomElement dmsServiceVersionElement = domDocument->createElement("env:ServiceVersion");
    QDomText dmsServiceVersionElementText = domDocument->createTextNode("2.4");
    dmsServiceVersionElement.appendChild(dmsServiceVersionElementText);
    businessContextElement.appendChild(dmsServiceVersionElement);

    QDomElement typeElement = domDocument->createElement("env:Type");
    QDomText typeElementText = domDocument->createTextNode("REQUEST");
    typeElement.appendChild(typeElementText);
    businessContextElement.appendChild(typeElement);

    messageElement.appendChild(businessContextElement);

    QDomElement userContextElement = domDocument->createElement("env:UserContext");

    QDomElement daimlerUserIdElement = domDocument->createElement("env:DaimlerUserId");
    QDomText daimlerUserIdElementText = domDocument->createTextNode(m_daimlerUser);
    daimlerUserIdElement.appendChild(daimlerUserIdElementText);
    userContextElement.appendChild(daimlerUserIdElement);

    QDomElement dmsUserIdElement = domDocument->createElement("env:DmsUserId");
    QDomText dmsUserIdElementText = domDocument->createTextNode(m_dmsUser);
    dmsUserIdElement.appendChild(dmsUserIdElementText);
    userContextElement.appendChild(dmsUserIdElement);

    QDomElement userLocaleElement = domDocument->createElement("env:UserLocale");
    QDomText userLocaleElementText = domDocument->createTextNode("en_US");
    userLocaleElement.appendChild(userLocaleElementText);
    userContextElement.appendChild(userLocaleElement);

    messageElement.appendChild(userContextElement);

    QDomElement processContextElement = domDocument->createElement("env:ProcessContext");

    QDomElement timestampElement = domDocument->createElement("env:Timestamp");
    QDomText timestampElementText = domDocument->createTextNode(QDateTime::currentDateTime().toString(Qt::ISODate));
    timestampElement.appendChild(timestampElementText);
    processContextElement.appendChild(timestampElement);

    QDomElement trackingIdElement = domDocument->createElement("env:TrackingId");
    QDomText trackingIdElementText = domDocument->createTextNode("TJ24_1.1");
    trackingIdElement.appendChild(trackingIdElementText);
    processContextElement.appendChild(trackingIdElement);

    messageElement.appendChild(processContextElement);

    QDomElement serviceMessageElement = domDocument->createElement("env:ServiceMessage");

    QDomElement initJobRequestElement = domDocument->createElement("env:InitJobRequest");

    QDomElement jobElement = domDocument->createElement("dms:Job");
    jobElement.setAttribute("Currency", "EUR");

    QDomElement orderElement = domDocument->createElement("dms:Order");
    orderElement.setAttribute("OrderId", m_orderIdEdit->text());
    orderElement.setAttribute("PaymentMethod", "optional payment");
    orderElement.setAttribute("ReceptionDateTime", m_receptionDate->dateTime().toString(Qt::ISODate));
    orderElement.setAttribute("ReturnDateTime", m_returnDate->dateTime().toString(Qt::ISODate));
    QDomElement serviceAdvisorElement = domDocument->createElement("types:ServiceAdvisor");
    serviceAdvisorElement.setAttribute("FirstName", m_serviceAdvisorFirstNameEdit->text());
    serviceAdvisorElement.setAttribute("LastName", m_serviceAdvisorLastNameEdit->text());
    serviceAdvisorElement.setAttribute("Abbreviation", "testerde");
    orderElement.appendChild(serviceAdvisorElement);
    jobElement.appendChild(orderElement);

    QDomElement vehicleElement = domDocument->createElement("dms:Vehicle");
    vehicleElement.setAttribute("FinOrVin", m_FinOrVinEdit->text());
    vehicleElement.setAttribute("FirstRegistrationDate", m_FirstRegistrationDate->date().toString(Qt::ISODate));
    vehicleElement.setAttribute("OdometerReading", m_OdometerReadingEdit->text());
    vehicleElement.setAttribute("OdometerUnit", "km");
    vehicleElement.setAttribute("OperatingHours", m_OperatingHoursEdit->text());
    vehicleElement.setAttribute("RegistrationNumber", m_RegistrationNumberEdit->text());
    jobElement.appendChild(vehicleElement);

    QDomElement customerElement = domDocument->createElement("dms:Customer");
    customerElement.setAttribute("CallbackFlag", "false");
    customerElement.setAttribute("WaitingFlag", "false");
    customerElement.setAttribute("EmailAddress","kostadin.angelov@gmail.com");
    customerElement.setAttribute("FirstName", m_customerFirstNameEdit->text());
    customerElement.setAttribute("LastName", m_customerLastNameEdit->text());
    customerElement.setAttribute("PhoneNumber", m_customerPhoneNumberEdit->text());
    customerElement.setAttribute("Salutation", "Herr");
    customerElement.setAttribute("Title", "Mr");
    customerElement.setAttribute("Preferences", "car wash");
    customerElement.setAttribute("Number", "dmsNumber");
    customerElement.setAttribute("IdSource", "central system");
    customerElement.setAttribute("UCID", "1234567890123456789");
    jobElement.appendChild(customerElement);

    initJobRequestElement.appendChild(jobElement);

    serviceMessageElement.appendChild(initJobRequestElement);

    messageElement.appendChild(serviceMessageElement);

    structuredDataElement.appendChild(messageElement);

    dataElement.appendChild(structuredDataElement);

    domDocument->appendChild(envelopeElement);

    return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" + domDocument->toString();
}

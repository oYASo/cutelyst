#ifndef DISPATCHERTEST_H
#define DISPATCHERTEST_H

#include <QtTest/QTest>
#include <QtCore/QObject>
#include <QHostInfo>
#include <QUuid>

#include "headers.h"
#include "coverageobject.h"

#include <Cutelyst/application.h>
#include <Cutelyst/controller.h>
#include <Cutelyst/headers.h>

using namespace Cutelyst;

class TestRequest : public CoverageObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();

    void testController_data();
    void testController() {
        doTest();
    }

    void cleanupTestCase();

private:
    TestEngine *m_engine;

    TestEngine* getEngine();

    void doTest();

};

class RequestTest : public Controller
{
    Q_OBJECT
public:
    RequestTest(QObject *parent) : Controller(parent) {}

    C_ATTR(address, :Local :AutoArgs)
    void address(Context *c) {
        c->response()->setBody(c->request()->address().toString());
    }

    C_ATTR(hostname, :Local :AutoArgs)
    void hostname(Context *c) {
        c->response()->setBody(c->request()->hostname());
    }

    C_ATTR(port, :Local :AutoArgs)
    void port(Context *c) {
        c->response()->setBody(QByteArray::number(c->request()->port()));
    }

    C_ATTR(uri, :Local :AutoArgs)
    void uri(Context *c) {
        c->response()->setBody(c->request()->uri().toString());
    }

    C_ATTR(base, :Local :AutoArgs)
    void base(Context *c) {
        c->response()->setBody(c->request()->base());
    }

    C_ATTR(path, :Local :AutoArgs)
    void path(Context *c) {
        c->response()->setBody(c->request()->path());
    }

    C_ATTR(match, :Local :AutoArgs)
    void match(Context *c) {
        c->response()->setBody(c->request()->match());
    }

    C_ATTR(method, :Local :AutoArgs)
    void method(Context *c) {
        c->response()->setBody(c->request()->method());
    }

    C_ATTR(isPost, :Local :AutoArgs)
    void isPost(Context *c) {
        c->response()->setBody(QVariant(c->request()->isPost()).toString());
    }

    C_ATTR(isGet, :Local :AutoArgs)
    void isGet(Context *c) {
        c->response()->setBody(QVariant(c->request()->isGet()).toString());
    }

    C_ATTR(protocol, :Local :AutoArgs)
    void protocol(Context *c) {
        c->response()->setBody(c->request()->protocol());
    }

    C_ATTR(remoteUser, :Local :AutoArgs)
    void remoteUser(Context *c) {
        c->response()->setBody(c->request()->remoteUser());
    }

    C_ATTR(headers, :Local :AutoArgs)
    void headers(Context *c) {
        QUrlQuery ret;
        auto headers = c->request()->headers().map();
        auto it = headers.constBegin();
        while (it != headers.constEnd()) {
            ret.addQueryItem(it.key(), it.value());
            ++it;
        }
        c->response()->setBody(ret.toString(QUrl::FullyEncoded));
    }

    C_ATTR(userAgent, :Local :AutoArgs)
    void userAgent(Context *c) {
        c->response()->setBody(c->request()->userAgent());
    }

    C_ATTR(referer, :Local :AutoArgs)
    void referer(Context *c) {
        c->response()->setBody(c->request()->referer());
    }

    C_ATTR(contentEncoding, :Local :AutoArgs)
    void contentEncoding(Context *c) {
        c->response()->setBody(c->request()->contentEncoding());
    }

    C_ATTR(contentType, :Local :AutoArgs)
    void contentType(Context *c) {
        c->response()->setBody(c->request()->contentType());
    }

    C_ATTR(queryKeywords, :Local :AutoArgs)
    void queryKeywords(Context *c) {
        c->response()->setBody(c->request()->queryKeywords());
    }

    C_ATTR(uriWith, :Local :AutoArgs)
    void uriWith(Context *c, const QString &append) {
        c->response()->setBody(c->request()->uriWith(ParamsMultiMap{
                                                         {QStringLiteral("foo"),QStringLiteral("baz")},
                                                         {QStringLiteral("fooz"),QStringLiteral("bar")}
                                                     }, QVariant(append).toBool()).toString(QUrl::FullyEncoded));
    }

    C_ATTR(mangleParams, :Local :AutoArgs)
    void mangleParams(Context *c, const QString &append) {
        QUrlQuery ret;
        qDebug() << c->request()->bodyParameters(), QVariant(append).toBool();
        auto params = c->request()->mangleParams(c->request()->bodyParameters(), QVariant(append).toBool());
        auto it = params.constBegin();
        while (it != params.constEnd()) {
            ret.addQueryItem(it.key(), it.value());
            ++it;
        }
        c->response()->setBody(ret.toString(QUrl::FullyEncoded));
    }

    C_ATTR(body, :Local :AutoArgs)
    void body(Context *c) {
        c->response()->setBody(c->request()->body()->readAll());
    }

    C_ATTR(bodyParameters, :Local :AutoArgs)
    void bodyParameters(Context *c) {
        QUrlQuery ret;
        auto params = c->request()->bodyParameters();
        auto it = params.constBegin();
        while (it != params.constEnd()) {
            ret.addQueryItem(it.key(), it.value());
            ++it;
        }
        c->response()->setBody(ret.toString(QUrl::FullyEncoded));
    }

    C_ATTR(bodyParams, :Local :AutoArgs)
    void bodyParams(Context *c) {
        QUrlQuery ret;
        auto params = c->request()->bodyParams();
        auto it = params.constBegin();
        while (it != params.constEnd()) {
            ret.addQueryItem(it.key(), it.value());
            ++it;
        }
        c->response()->setBody(ret.toString(QUrl::FullyEncoded));
    }

    C_ATTR(bodyParameter, :Local :AutoArgs)
    void bodyParameter(Context *c) {
        c->response()->setBody(c->request()->bodyParameter(c->request()->queryParam(QStringLiteral("param")),
                                                           c->request()->queryParam(QStringLiteral("defaultValue"))));
    }

    C_ATTR(bodyParam, :Local :AutoArgs)
    void bodyParam(Context *c) {
        c->response()->setBody(c->request()->bodyParam(c->request()->queryParam(QStringLiteral("param")),
                                                       c->request()->queryParam(QStringLiteral("defaultValue"))));
    }

    C_ATTR(parameters, :Local :AutoArgs)
    void parameters(Context *c) {
        QUrlQuery ret;
        auto params = c->request()->parameters();
        auto it = params.constBegin();
        while (it != params.constEnd()) {
            ret.addQueryItem(it.key(), it.value());
            ++it;
        }
        c->response()->setBody(ret.toString(QUrl::FullyEncoded));
    }

    C_ATTR(paramsKey, :Local :AutoArgs)
    void paramsKey(Context *c, const QString &param) {
        c->response()->setBody(c->request()->params(param).join(QLatin1Char('/')));
    }

    C_ATTR(params, :Local :AutoArgs)
    void params(Context *c) {
        QUrlQuery ret;
        auto params = c->request()->params();
        auto it = params.constBegin();
        while (it != params.constEnd()) {
            ret.addQueryItem(it.key(), it.value());
            ++it;
        }
        c->response()->setBody(ret.toString(QUrl::FullyEncoded));
    }

    C_ATTR(paramsKeyDefaultValue, :Local :AutoArgs)
    void paramsKeyDefaultValue(Context *c, const QString &param, const QString &defaultValue) {
        c->response()->setBody(c->request()->param(param, defaultValue));
    }
};

void TestRequest::initTestCase()
{
    m_engine = getEngine();
    QVERIFY(m_engine);
}

TestEngine* TestRequest::getEngine()
{
    TestEngine *engine = new TestEngine(QVariantMap(), this);
    qputenv("RECURSION", QByteArrayLiteral("100"));
    auto app = new TestApplication;
    new RequestTest(app);
    if (!engine->initApplication(app, true)) {
        return nullptr;
    }
    return engine;
}


void TestRequest::cleanupTestCase()
{
    delete m_engine;
}

void TestRequest::doTest()
{
    QFETCH(QString, method);
    QFETCH(QString, url);
    QFETCH(Headers, headers);
    QFETCH(QByteArray, body);
    QFETCH(QByteArray, output);

    QUrl urlAux(url.mid(1));

    QByteArray result = m_engine->createRequest(method,
                                                urlAux.path(),
                                                urlAux.query(QUrl::FullyEncoded).toLatin1(),
                                                headers,
                                                &body);

    QCOMPARE( result, output );
}

void TestRequest::testController_data()
{
    QTest::addColumn<QString>("method");
    QTest::addColumn<QString>("url");
    QTest::addColumn<Headers>("headers");
    QTest::addColumn<QByteArray>("body");
    QTest::addColumn<QByteArray>("output");

    QString get = QStringLiteral("GET");
    QString post = QStringLiteral("POST");

    QUrlQuery query;
    Headers headers;
    QByteArray body;

    QTest::newRow("address-test00") << get << QStringLiteral("/request/test/address") << headers << QByteArray() << QByteArrayLiteral("127.0.0.1");
    QTest::newRow("hostname-test00") << get << QStringLiteral("/request/test/hostname") << headers << QByteArray()
                                     << QHostInfo::fromName(QStringLiteral("127.0.0.1")).hostName().toLatin1();
    QTest::newRow("port-test00") << get << QStringLiteral("/request/test/port") << headers << QByteArray() << QByteArrayLiteral("3000");
    QTest::newRow("uri-test00") << get << QStringLiteral("/request/test/uri") << headers << QByteArray() << QByteArrayLiteral("http://127.0.0.1/request/test/uri");
    QTest::newRow("base-test00") << get << QStringLiteral("/request/test/base") << headers << QByteArray() << QByteArrayLiteral("http://127.0.0.1/");
    QTest::newRow("path-test00") << get << QStringLiteral("/request/test/path") << headers << QByteArray() << QByteArrayLiteral("request/test/path");
    QTest::newRow("match-test00") << get << QStringLiteral("/request/test/match") << headers << QByteArray() << QByteArrayLiteral("request/test/match");

    QTest::newRow("method-test00") << get << QStringLiteral("/request/test/method") << headers << QByteArray() << QByteArrayLiteral("GET");
    QTest::newRow("method-test01") << post << QStringLiteral("/request/test/method") << headers << QByteArray() << QByteArrayLiteral("POST");
    QTest::newRow("method-test02") << QStringLiteral("HEAD") << QStringLiteral("/request/test/method") << headers << QByteArray() << QByteArrayLiteral("HEAD");

    QTest::newRow("isPost-test00") << get << QStringLiteral("/request/test/isPost") << headers << QByteArray() << QByteArrayLiteral("false");
    QTest::newRow("isPost-test01") << QStringLiteral("PoSt") << QStringLiteral("/request/test/isPost") << headers << QByteArray() << QByteArrayLiteral("false");
    QTest::newRow("isPost-test02") << post << QStringLiteral("/request/test/isPost") << headers << QByteArray() << QByteArrayLiteral("true");

    QTest::newRow("isGet-test00") << post << QStringLiteral("/request/test/isGet") << headers << QByteArray() << QByteArrayLiteral("false");
    QTest::newRow("isGet-test01") << QStringLiteral("GeT") << QStringLiteral("/request/test/isGet") << headers << QByteArray() << QByteArrayLiteral("false");
    QTest::newRow("isGet-test02") << get << QStringLiteral("/request/test/isGet") << headers << QByteArray() << QByteArrayLiteral("true");

    QTest::newRow("protocol-test00") << get << QStringLiteral("/request/test/protocol") << headers << QByteArray() << QByteArrayLiteral("HTTP/1.1");
    QTest::newRow("remoteUser-test00") << get << QStringLiteral("/request/test/remoteUser") << headers << QByteArray() << QByteArrayLiteral("");

    headers.clear();
    headers.setAuthorizationBasic(QStringLiteral("foo"), QStringLiteral("bar"));
    headers.setReferer(QStringLiteral("http://www.cutelyst.org"));
    QTest::newRow("headers-test00") << get << QStringLiteral("/request/test/headers") << headers << QByteArray()
                                    << QByteArrayLiteral("authorization=Basic%20Zm9vOmJhcg%3D%3D&referer=http://www.cutelyst.org");

    headers.clear();
    headers.setHeader(QStringLiteral("User-Agent"), QStringLiteral("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36"));
    QTest::newRow("userAgent-test00") << get << QStringLiteral("/request/test/userAgent") << headers << QByteArray()
                                      << QByteArrayLiteral("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36");

    headers.clear();
    headers.setHeader(QStringLiteral("Referer"), QStringLiteral("http://www.cutelyst.org"));
    QTest::newRow("referer-test00") << get << QStringLiteral("/request/test/referer") << headers << QByteArray()
                                    << QByteArrayLiteral("http://www.cutelyst.org");

    headers.clear();
    headers.setHeader(QStringLiteral("Content-Encoding"), QStringLiteral("gzip"));
    QTest::newRow("contentEncoding-test00") << get << QStringLiteral("/request/test/contentEncoding") << headers << QByteArray()
                                            << QByteArrayLiteral("gzip");

    headers.clear();
    headers.setHeader(QStringLiteral("Content-Type"), QStringLiteral("text/html; charset=UTF-8"));
    QTest::newRow("contentType-test00") << get << QStringLiteral("/request/test/contentType") << headers << QByteArray()
                                        << QByteArrayLiteral("text/html");

    query.clear();
    query.addQueryItem(QStringLiteral("some text to ask"), QString());
    QTest::newRow("queryKeywords-test00") << get << QStringLiteral("/request/test/queryKeywords?") + query.toString(QUrl::FullyEncoded)
                                          << headers << QByteArray()
                                          << QByteArrayLiteral("some text to ask");
    query.clear();
    query.addQueryItem(QStringLiteral("some text to ask"), QStringLiteral("not"));
    QTest::newRow("queryKeywords-test01") << get << QStringLiteral("/request/test/queryKeywords?") + query.toString(QUrl::FullyEncoded)
                                          << headers << QByteArray()
                                          << QByteArrayLiteral("");

    query.clear();
    query.addQueryItem(QStringLiteral("some text to ask"), QString());
    query.addQueryItem(QStringLiteral("another keyword"), QString());
    query.addQueryItem(QStringLiteral("and yet another is fine"), QString());
    QTest::newRow("queryKeywords-test02") << get << QStringLiteral("/request/test/queryKeywords?") + query.toString(QUrl::FullyEncoded)
                                          << headers << QByteArray()
                                          << QByteArrayLiteral("some text to ask&another keyword&and yet another is fine");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("bar"));
    QTest::newRow("uriWith-test00") << get << QStringLiteral("/request/test/uriWith/false?") + query.toString(QUrl::FullyEncoded)
                                    << headers << QByteArray()
                                    << QByteArrayLiteral("http://127.0.0.1/request/test/uriWith/false?foo=baz&fooz=bar");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("bar"));
    QTest::newRow("uriWith-test01") << get << QStringLiteral("/request/test/uriWith/true?") + query.toString(QUrl::FullyEncoded)
                                    << headers << QByteArray()
                                    << QByteArrayLiteral("http://127.0.0.1/request/test/uriWith/true?foo=bar&foo=baz&fooz=bar");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("baz"));
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("mangleParams-test00") << get << QStringLiteral("/request/test/mangleParams/false?foo=bar&x=y")
                                    << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                    << QByteArrayLiteral("foo=baz&x=y");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("baz"));
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("mangleParams-test01") << get << QStringLiteral("/request/test/mangleParams/true?foo=bar&x=y")
                                    << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                    << QByteArrayLiteral("foo=bar&foo=baz&x=y");

    query.clear();
    QTest::newRow("body-test00") << get << QStringLiteral("/request/test/body")
                                 << headers << QByteArray() << QByteArray();

    query.clear();
    body = QUuid::createUuid().toByteArray();
    QTest::newRow("body-test00") << get << QStringLiteral("/request/test/body")
                                 << headers << body << body;

    query.clear();
    query.addQueryItem(QStringLiteral("some text to ask"), QString());
    query.addQueryItem(QStringLiteral("another keyword"), QString());
    query.addQueryItem(QStringLiteral("and yet another is fine"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("bodyParams-test00") << get << QStringLiteral("/request/test/bodyParams")
                                       << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                       << QByteArrayLiteral("and%20yet%20another%20is%20fine&another%20keyword&some%20text%20to%20ask");

    query.clear();
    body = QUuid::createUuid().toByteArray();
    query.addQueryItem(QStringLiteral("foo"), QString::fromLatin1(body));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("and yet another is fine"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("bodyParam-test00") << get << QStringLiteral("/request/test/bodyParam?param=foo")
                                      << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                      << body;

    query.clear();
    body = QUuid::createUuid().toByteArray();
    query.addQueryItem(QStringLiteral("foo"), QString::fromLatin1(body));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("bodyParam-test01") << get << QStringLiteral("/request/test/bodyParam?param=y&defaultValue=SomeDefaultValue")
                                      << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                      << QByteArrayLiteral("SomeDefaultValue");

    query.clear();
    body = QUuid::createUuid().toByteArray();
    query.addQueryItem(QStringLiteral("foo"), QString::fromLatin1(body));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("bodyParam-test02") << get << QStringLiteral("/request/test/bodyParam?param=x&defaultValue=SomeDefaultValue")
                                      << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                      << QByteArrayLiteral("");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("Cutelyst"));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("parameters-test00") << get << QStringLiteral("/request/test/parameters?param=y&defaultValue=SomeDefaultValue")
                                       << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                       << QByteArrayLiteral("bar=baz&defaultValue=SomeDefaultValue&foo=Cutelyst&param=y&x");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("Cutelyst"));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("params-test00") << get << QStringLiteral("/request/test/params?param=y&defaultValue=SomeDefaultValue")
                                   << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                   << QByteArrayLiteral("bar=baz&defaultValue=SomeDefaultValue&foo=Cutelyst&param=y&x");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("Cutelyst"));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("paramsKey-test00") << get << QStringLiteral("/request/test/paramsKey/foo?param=y&defaultValue=SomeDefaultValue")
                                      << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                      << QByteArrayLiteral("Cutelyst");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("Cutelyst"));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("paramsKey-test00") << get << QStringLiteral("/request/test/paramsKey/x?param=y&defaultValue=SomeDefaultValue")
                                      << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                      << QByteArrayLiteral("");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("Cutelyst"));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("paramsKeyDefaultValue-test00") << get << QStringLiteral("/request/test/paramsKeyDefaultValue/foo/bar?param=y&defaultValue=SomeDefaultValue")
                                                  << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                                  << QByteArrayLiteral("Cutelyst");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("Cutelyst"));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("paramsKeyDefaultValue-test01") << get << QStringLiteral("/request/test/paramsKeyDefaultValue/x/gotDefault?param=y&defaultValue=SomeDefaultValue")
                                                  << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                                  << QByteArrayLiteral("");

    query.clear();
    query.addQueryItem(QStringLiteral("foo"), QStringLiteral("Cutelyst"));
    query.addQueryItem(QStringLiteral("bar"), QStringLiteral("baz"));
    query.addQueryItem(QStringLiteral("x"), QString());
    headers.setContentType(QStringLiteral("application/x-www-form-urlencoded"));
    QTest::newRow("paramsKeyDefaultValue-test01") << get << QStringLiteral("/request/test/paramsKeyDefaultValue/z/gotDefault?param=y&defaultValue=SomeDefaultValue")
                                                  << headers << query.toString(QUrl::FullyEncoded).toLatin1()
                                                  << QByteArrayLiteral("gotDefault");

}

QTEST_MAIN(TestRequest)

#include "testrequest.moc"

#endif
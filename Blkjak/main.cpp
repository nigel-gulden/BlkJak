#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>
#include "CardC.h"
#include "Hand.h"
#include "Blackjack.h"
#include "Deck.h"
#include "Random.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCoreApplication::setApplicationName("April18");
    QCoreApplication::setOrganizationName("Chessgames");
    QCoreApplication::setOrganizationDomain(".com");

    QQmlApplicationEngine engine;
    Deck d;
    Hand dealer;
    Hand player;
    Blackjack game;
    d.Shuffle();

    qmlRegisterType<CardC>("MyExt", 1, 0, "CardC");
    qmlRegisterType<Deck>("MyExt", 1, 0, "DeckC");
    qRegisterMetaType<CardC>();
    qRegisterMetaType<Hand>();
    engine.rootContext()->setContextProperty("deck", &d);
    engine.rootContext()->setContextProperty("dealer", &dealer);
    engine.rootContext()->setContextProperty("player", &player);
    engine.rootContext()->setContextProperty("game", &game);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

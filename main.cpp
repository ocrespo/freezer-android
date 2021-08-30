
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/view/FreezerPageModel.h"
#include "src/view/FilterFreezerPage.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


    QGuiApplication app(argc, argv);

    FreezerPageModel view_model;

    view_model.addItem({"Home", 1 ,1, "Item2", ""});
    view_model.addItem({"Home", 2 ,1, "Item3", ""});
    view_model.addItem({"Home", 3 ,1, "Item4", ""});
    view_model.addItem({"Home", 4 ,1, "Item5", ""});
    view_model.addItem({"Home", 5 ,1, "Item6", ""});
    view_model.addItem({"Home", 6 ,1, "Item7", ""});
    view_model.addItem({"Home", 7 ,1, "Item8", ""});
    view_model.addItem({"Home", 8 ,1, "Item10", ""});
    view_model.addItem({"Home2",1 ,1, "Item1", ""});
    view_model.addItem({"Home2",2 ,1, "HOME", ""});
    view_model.addItem({"Home2",3 ,1, "HOME", ""});
    view_model.addItem({"Home2",4 ,1, "HOME", ""});
    view_model.addItem({"Home2",5 ,1, "HOME", ""});
    view_model.addItem({"Home2",6 ,1, "HOME", ""});
    view_model.addItem({"Home2",7 ,1, "HOME", ""});
    view_model.addItem({"Home2",8 ,1, "HOME", ""});
    view_model.addItem({"Home2",9 ,1, "HOME", ""});
    view_model.addItem({"Home2",10 ,1, "HOME", ""});
    view_model.addItem({"Home2",11 ,1, "HOME", ""});
    view_model.addItem({"Home2",12 ,1, "HOME", ""});

    //Create filter model
    FilterFreezerPage filterModel;
    filterModel.setSourceModel(&view_model);
    //filterModel.setSortRole(FreezerPageModel::IdRole);
    filterModel.setDynamicSortFilter(true);
    filterModel.sort(0,Qt::AscendingOrder);

    filterModel.selectFreezer("Home");

    QQmlApplicationEngine engine;
    QQmlContext* context{engine.rootContext()};

    context->setContextProperty("freezerModel", &view_model);
    context->setContextProperty("filterFreezerModel", &filterModel);

    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    view_model.addItem({"Home2", 0 ,1, "ItemParty", ""});


    return app.exec();
}

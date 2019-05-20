#include "plugin.h"
#include "qmlsqldatabase.h"
#include "qqmlsqlquery.h"
#include "qmlsqlquerymodel.h"
#include "qmlsqlcreatedatabase.h"
#include "qmlsqlconnectionparameters.h"
#include <qqml.h>

static QObject *dbCallback( QQmlEngine *e, QJSEngine *se )
{
    Q_UNUSED( e )
    Q_UNUSED( se )
    QmlSqlDatabase *db = new QmlSqlDatabase();
    return db;
}

void QQmlSqlPlugin::registerTypes( const char *uri )
{
    // @uri QmlSql
    qmlRegisterSingletonType<QmlSqlDatabase>( uri, 1, 0, "SqlDatabase", &dbCallback );
    qmlRegisterType<QmlSqlConnectionParameters>( uri, 1, 0, "SqlConnectionParameters" );
    qmlRegisterType<QQmlSqlQuery>( uri, 1, 0, "SqlQuery");
    qmlRegisterType<QmlSqlQueryModel>( uri, 1, 0, "SqlQueryModel");
    qmlRegisterType<QmlSqlCreateDatabase>( uri, 1, 0, "SqlCreateDatabase");
}

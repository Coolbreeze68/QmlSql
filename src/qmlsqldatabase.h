#ifndef QMLSQLDATABASE_H
#define QMLSQLDATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

#include "qmlsqlconnectionparameters.h"

class QmlSqlDatabase : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool running READ running NOTIFY runningChanged )
    Q_PROPERTY( QString errorString READ errorString NOTIFY errorStringChanged )
    Q_PROPERTY( QStringList connectionNames READ connectionNames NOTIFY connectionNamesChanged )
    Q_PROPERTY( QmlSqlConnectionParameters *parameters READ parameters WRITE setParameters NOTIFY parametersChanged )

    Q_ENUMS( TableTypes )

public:
    explicit QmlSqlDatabase( QObject *parent = Q_NULLPTR );

    enum TableType {
        Tables,
        SystemTables,
        Views,
        AllTables
    };

    enum CloseReason {
        Error,
        Requested,
        Unknown
    };

    QStringList connectionNames();
    QString errorString() const;
    QString source() const;
    void setSource( const QString &source );

    Q_INVOKABLE void addDataBase();
    Q_INVOKABLE void removeDatabase( const QString &connectionName );
    Q_INVOKABLE void closeAllConnections();
    Q_INVOKABLE bool running();
    Q_INVOKABLE QStringList tables( const QString &connectionName, const TableType &tableType );

    QmlSqlConnectionParameters *parameters() const;
    void setParameters( QmlSqlConnectionParameters *parameters );
signals:
    void sourceChanged();
    void errorStringChanged();
    void runningChanged();

    void error( QString );
    void connectionOpened( QSqlDatabase, QString );
    void closeRequested( CloseReason, QString );
    void sqlError( QSqlError );
    void connectionNamesChanged(QStringList connectionNames);
    void parametersChanged();

public slots:
    void handelError( const QString &err );
    void handelOpened( QSqlDatabase database, const QString connectionName );
    void handelCloseRequested( const CloseReason &reason, const QString &connectionName );
    void handelSqlError( const QSqlError &err );

private:
    QSqlDatabase db;
    bool m_running;
    QString m_errorString;

    QSql::TableType setTableType( const QmlSqlDatabase::TableType &type );
    QString closeReasonToString( const CloseReason &cR );
    QStringList m_connectionNames;
    QmlSqlConnectionParameters *m_parameters;
};
#endif //  // QMLSQLDATABASE

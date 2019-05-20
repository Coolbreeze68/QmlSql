#ifndef QMLSQLCONNECTIONPARAMETERS_H
#define QMLSQLCONNECTIONPARAMETERS_H

#include <QObject>
#include <QHash>

class QmlSqlConnectionParameters : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString source READ source WRITE setSource NOTIFY sourceChanged )
    Q_PROPERTY( QString databaseName READ databaseName WRITE setdatabaseName NOTIFY databaseNameChanged )
    Q_PROPERTY( QString user READ user WRITE setUser NOTIFY userChanged )
    Q_PROPERTY( QString password READ password WRITE setPassword NOTIFY passwordChanged )
    Q_PROPERTY( int port READ port WRITE setPort NOTIFY portChanged )
    Q_PROPERTY( QString connectionName READ connectionName WRITE setConnectionName NOTIFY connectionNameChanged )

    Q_PROPERTY( QStringList databaseDriverList READ databaseDriverList NOTIFY databaseDriverListChanged )

    Q_PROPERTY( DataBaseDriver databaseDriver READ databaseDriver WRITE setDatabaseDriver NOTIFY databaseDriverChanged )
    Q_ENUMS( DataBaseDriver )
public:
    explicit QmlSqlConnectionParameters( QObject *parent = Q_NULLPTR );

    enum DataBaseDriver{
        PostGre,
        MySql,
        OCI,
        ODBC,
        DB2,
        TDS,
        SQLight,
        SQLight2,
        IBase
    };
    DataBaseDriver databaseDriver() const;
    void setDatabaseDriver( const DataBaseDriver &databaseDriver );
    QString getDatabaseDriverString( const DataBaseDriver &dbd );

    QString source() const;
    void setSource( const QString &source );

    QString databaseName() const;
    void setdatabaseName( const QString &databaseName );

    QString user() const;
    void setUser( const QString &user );

    QString password() const;
    void setPassword( const QString &password );

    int port() const;
    void setPort( const int &port );

    QString connectionName() const;
    void setConnectionName( const QString &connectionName );

    QStringList databaseDriverList() const;

signals:
    void databaseDriverChanged( DataBaseDriver );
    void sourceChanged( QString source );
    void databaseNameChanged( QString databaseName );
    void userChanged(QString user);
    void passwordChanged(QString password);
    void portChanged(int port);
    void connectionNameChanged(QString connectionName);
    void databaseDriverListChanged();

private:
    DataBaseDriver m_databaseDriver;
    QString m_source;
    QString m_databaseName;
    QString m_user;
    QString m_password;
    int m_port;
    QString m_connectionName;
    QStringList m_databaseDriverList;
    QHash<DataBaseDriver, QString> m_databaseDriverHash;
};

#endif // QMLSQLCONNECTIONPARAMETERS_H

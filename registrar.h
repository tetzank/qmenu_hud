#ifndef REGISTRAR_H
#define REGISTRAR_H

#include "dbusmenutypes_p.h"

#include <QString>
#include <QMap>


class Registrar: public QObject{
	Q_OBJECT
public:
	Registrar(QObject *parent=0);
	virtual ~Registrar();

public Q_SLOTS: // METHODS
	QString GetMenuForWindow(uint windowId, QDBusObjectPath &menuObjectPath);
	MenuInfoList GetMenus();
	void RegisterWindow(uint windowId, const QDBusObjectPath &menuObjectPath);
	void UnregisterWindow(uint windowId);

Q_SIGNALS: // SIGNALS
	void WindowRegistered(uint windowId, const QString &service, const QDBusObjectPath &menuObjectPath);
	void WindowUnregistered(uint windowId);

private:
	QMap<uint,std::pair<QString,QDBusObjectPath>> m_map;
};

#endif

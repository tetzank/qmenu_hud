#include "registrar.h"

#include <QtDebug>
#include <QDBusMessage>


Registrar::Registrar(QObject* parent)
	: QObject(parent)
{

}

Registrar::~Registrar(){
}

QString Registrar::GetMenuForWindow(uint windowId, QDBusObjectPath &menuObjectPath){
// 	qDebug() << "GetMenuForWindow called: " << windowId;

	if(m_map.find(windowId) != m_map.end()){
		QString service;
		QDBusObjectPath path;
		std::tie(service, path) = m_map[windowId];
		menuObjectPath = path;
		return service;
	}else{
		// kded appmenu module sends back a default empty QDBusObjectPath when window not registered
		//menuObjectPath = QDBusObjectPath();
		// (it uses QHash.value())
		// this doesn't work, assert in libdbus fails and brings down whole process

		sendErrorReply(QDBusError::Failed);

		// this works, but error better
		menuObjectPath.setPath("/");//ignored, because send error above
		return QString("");         //ignored, because send error above
	}
}

MenuInfoList Registrar::GetMenus(){
// 	qDebug() << "GetMenus called";

	sendErrorReply(QDBusError::NotSupported);

	return MenuInfoList(); //ignored, because send error above
}

void Registrar::RegisterWindow(uint windowId, const QDBusObjectPath &menuObjectPath){
// 	qDebug() << "RegisterWindow called: " << windowId << "; " << menuObjectPath.path();
	//get service name who send this
	QString service = message().service();
// 	qDebug() << service;

	m_map[windowId] = std::make_pair(service, menuObjectPath);

	emit WindowRegistered(windowId, service, menuObjectPath);
}

void Registrar::UnregisterWindow(uint windowId){
// 	qDebug() << "UnregisterWindow called: " << windowId;

	m_map.erase(windowId);

	emit WindowUnregistered(windowId);
}

#include "registrar.moc"

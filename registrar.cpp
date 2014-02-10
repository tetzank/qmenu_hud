#include "registrar.h"


Registrar::Registrar(QObject* parent)
	: QObject(parent)
{

}

Registrar::~Registrar(){
}

QString Registrar::GetMenuForWindow(uint windowId, QDBusObjectPath &menuObjectPath){
	return QString();
}

MenuInfoList Registrar::GetMenus(){
	MenuInfoList l;
	return l;
}

void Registrar::RegisterWindow(uint windowId, const QDBusObjectPath &menuObjectPath){
	//m_map.insert(windowId,);
	//TODO: get service name who send this
}

void Registrar::UnregisterWindow(uint windowId){
}

#include "registrar.moc"

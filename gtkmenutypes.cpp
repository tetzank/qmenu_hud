#include "gtkmenutypes.h"

#include <QDBusArgument>
#include <QDBusMetaType>


QDBusArgument &operator<<(QDBusArgument &argument, const GtkMenuEntry &item){
	argument.beginStructure();
	argument << item.first << item.second << item.entry;
	argument.endStructure();
	return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, GtkMenuEntry &item){
	argument.beginStructure();
	argument >> item.first >> item.second >> item.entry;
	argument.endStructure();
	return argument;
}

QDBusArgument& operator<<(QDBusArgument &argument, const SimplePair &item){
	argument.beginStructure();
	argument << item.first << item.second;
	argument.endStructure();
	return argument;
}
const QDBusArgument& operator>>(const QDBusArgument& argument, SimplePair& item){
	argument.beginStructure();
	argument >> item.first >> item.second;
	argument.endStructure();
	return argument;
}

QDBusArgument& operator<<(QDBusArgument &argument, const GtkMenuDesc &item){
	argument.beginStructure();
	argument << item.enabled << item.sig << item.props;
	argument.endStructure();
	return argument;
}
const QDBusArgument& operator>>(const QDBusArgument &argument, GtkMenuDesc &item){
	argument.beginStructure();
	argument >> item.enabled >> item.sig >> item.props;
	argument.endStructure();
	return argument;
}


void GtkMenuTypes_register(){
	qDBusRegisterMetaType<SillyList>();
	qDBusRegisterMetaType<GtkMenuEntry>();
	qDBusRegisterMetaType<GtkMenuEntryList>();
	qDBusRegisterMetaType<SimplePair>();
	qDBusRegisterMetaType<GtkMenuDesc>();
	qDBusRegisterMetaType<GtkMenuDescMap>();
}

#ifndef GTKMENUTYPES_H
#define GTKMENUTYPES_H

#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QDBusSignature>
class QDBusArgument;


typedef QMap<QString, QVariant> SillyMap;

typedef QList<uint> SillyList;
Q_DECLARE_METATYPE(SillyList)


struct GtkMenuEntry{
	uint first, second;
	QList<QVariantMap> entry;
};
Q_DECLARE_METATYPE(GtkMenuEntry)

QDBusArgument &operator<<(QDBusArgument &argument, const GtkMenuEntry &item);
const QDBusArgument &operator>>(const QDBusArgument &argument, GtkMenuEntry &item);

typedef QList<GtkMenuEntry> GtkMenuEntryList;
Q_DECLARE_METATYPE(GtkMenuEntryList)


struct SimplePair{
	uint first, second;
};
Q_DECLARE_METATYPE(SimplePair)

QDBusArgument &operator<<(QDBusArgument &argument, const SimplePair &item);
const QDBusArgument &operator>>(const QDBusArgument &argument, SimplePair &item);


struct GtkMenuDesc{ //FIXME: this semantic is just a guess
	bool enabled;
	QDBusSignature sig;
	QVariantList props;
};
Q_DECLARE_METATYPE(GtkMenuDesc)

QDBusArgument &operator<<(QDBusArgument &argument, const GtkMenuDesc &item);
const QDBusArgument &operator>>(const QDBusArgument &argument, GtkMenuDesc &item);

typedef QMap<QString,GtkMenuDesc> GtkMenuDescMap;
Q_DECLARE_METATYPE(GtkMenuDescMap)


void GtkMenuTypes_register();

#endif

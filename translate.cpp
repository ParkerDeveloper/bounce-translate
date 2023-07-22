#include "translate.h"

translate::translate(IniFile *ini, uint sampOffset, QString tr, uint origOffset)
{
	this->ini = ini;
	this->sampOffset.push_back(sampOffset);
	this->trOrig = origOffset;

	std::string str = read(tr, origOffset ? (char*)(g_handle.dwSAMP + origOffset) : "DUMMY");
	apply(str);
}

translate::translate(IniFile *ini, QList<uint> sampOffset, QString tr, uint origOffset)
{
	this->ini = ini;
	this->sampOffset = sampOffset;
	this->trOrig = origOffset;

	std::string str = read(tr, origOffset ? (char*)(g_handle.dwSAMP + origOffset) : "DUMMY");
	apply(str);
}

translate::~translate()
{
	for (uint offset : sampOffset){
		memsafe::write<char*>((void*)(g_handle.dwSAMP + offset), (char*)(g_handle.dwSAMP + trOrig));
	}
	delete trVar;
}

void translate::apply(std::string str)
{
	trVar = new char[str.length() + 1];
	memset(trVar, 0, sizeof(trVar));
	strcpy(trVar, str.c_str());

	for (uint offset : sampOffset){
		memsafe::write<char*>((void*)(g_handle.dwSAMP + offset), trVar);
	}
}

std::string translate::read(QString key, QString def)
{
	QStringList ff = key.split('/');
	return ini->esgString(ff.first().toStdString(), key.remove(ff.first() + '/').toStdString(), def.toStdString());
}

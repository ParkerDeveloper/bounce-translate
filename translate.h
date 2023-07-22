#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "loader.h"
#include "IniFiles.hpp"

class translate
{
public:
	translate(IniFile *ini, uint sampOffset, QString tr, uint origOffset);
	translate(IniFile *ini, QList<uint> sampOffset, QString tr, uint origOffset);
	~translate();

private:
	char *trVar;
	QList<uint> sampOffset;
	uint trOrig;
	IniFile *ini;

	void apply(std::string str);
	std::string read(QString key, QString def);
};

#endif // TRANSLATE_H

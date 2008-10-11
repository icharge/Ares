#include "Includes.h"
#include "Ares.h"

DynamicVectorClass<CCINIClass*> Includes::LoadedINIs;
DynamicVectorClass<char*> Includes::LoadedINIFiles;

// 474200, 6
EXPORT_FUNC(CCINIClass_ReadCCFile1)
{
	Includes::LoadedINIs.AddItem((CCINIClass *)R->get_ECX());
	Includes::LoadedINIFiles.AddItem(_strdup(((CCFileClass*)R->get_EAX())->GetFileName()));
	return 0;
}

// 474314, 6
EXPORT_FUNC(CCINIClass_ReadCCFile2)
{
	char buffer[0x80];
	CCINIClass *xINI = Includes::LoadedINIs[Includes::LoadedINIs.get_Count() - 1];
	const char *key;

	Includes::LoadedINIs.RemoveItem(Includes::LoadedINIs.get_Count() - 1);

	if(!xINI)
	{
		return 0;
	}

	char section[] = "#include";

	int len = xINI->GetKeyCount(section);
	for(int i = 0; i < len; ++i)
	{
		key = xINI->GetKeyName(section, i);
		if(xINI->ReadString(section, key, "", buffer, 0x80))
		{
			bool canLoad = 1;
			for(int j = 0; j < Includes::LoadedINIFiles.get_Count(); ++j )
			{
				if(!strcmp(Includes::LoadedINIFiles[j], buffer))
				{
					canLoad = 0;
					break;
				}
			}

			if(canLoad)
			{
				CCFileClass *xFile = new CCFileClass(buffer);
				if(xFile->Exists(NULL))
				{
					xINI->ReadCCFile(xFile);
				}
				delete xFile;
			}
		}
	}

	if(!Includes::LoadedINIs.get_Count() || Includes::LoadedINIs.get_Count() > 10)
	{
		for(int j = Includes::LoadedINIs.get_Count() - 1; j > 0; --j)
		{
			Includes::LoadedINIs.RemoveItem(j);
		}
		for(int j = Includes::LoadedINIFiles.get_Count() - 1; j > 0; --j)
		{
			delete Includes::LoadedINIFiles[j];
			Includes::LoadedINIFiles.RemoveItem(j);
		}
		return 0;
	}
	return 0;
}
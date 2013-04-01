#ifndef PLUGINMANAGER_H_INCLUDED
#define PLUGINMANAGER_H_INCLUDED

#include <stdlib.h>

#include "main.h"
#include "basicTypes.h"
#include "darray.h"

#include "RPEP.h"

class DArray;

class PluginInterface;
class plugin{
    public:
        ulong ID;
        MEMORYMODULE Module;
        PluginInterface* plugInterface;
};
class PluginManagerInterfacePrivate;
class RPEP;
class PluginManager{
        SHELLCODE_CONTEXT* Context;
        RPEP* protocol;
        static PluginManagerInterfacePrivate* pluginList;
    public:
        PluginManager();
        ~PluginManager();

        bool loadPlugin(RPEP_LOAD_PLUGIN *pluginModule);
        bool unload(ushort ID);
        bool initPlugin();
        bool stopPlugin();
        bool enumPluginLoad();
        bool isPluginLoad(ushort ID);
        bool updateManager();
        bool updateServer(DArray& newServer);
        bool stopServer();

        uint run(SHELLCODE_CONTEXT *Context);
        bool runPluginCMD(ulong pluginID,char* data,uint size);
        plugin* getPluginById(ulong id);
        RPEP* getProtocol();

        static int pluginThread(void*);
};

//extern PluginManager PlugMgr;

#endif // PLUGINMANAGER_H_INCLUDED
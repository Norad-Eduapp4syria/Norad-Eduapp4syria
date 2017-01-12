#ifndef __NATIVE_BRIDGE_H__
#define __NATIVE_BRIDGE_H__

#include "cocos2d.h"
#include "../Singleton.h"

USING_NS_CC;


class NativeBridge : public Singleton<NativeBridge> {
    friend class Singleton<NativeBridge>;
    
public:
    void createFolder(std::string folderPath);
    void createNecessaryFolders(std::string folderPath);
    void unZipArchiveToFolder(std::string archivePath, std::string destFolderPath);
    
protected:
    NativeBridge();
    
    
};

#endif // __NATIVE_BRIDGE_H__

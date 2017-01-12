#include "NativeBridge.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <Foundation/Foundation.h>

//#import "../../../proj.ios_mac/ios/SSZipArchive/SSZipArchive.h"

#include "AppController.h"

void NativeBridge::createFolder(std::string folderPath) {
    // TODO
}

void NativeBridge::createNecessaryFolders(std::string folderPath) {
    // TODO
}

/*
void NativeBridge::unZipArchiveToFolder(std::string archivePath, std::string destFolderPath)
{
    // TODO
}
*/

void NativeBridge::unZipArchiveToFolder(std::string _zipFilePath, std::string _destFolder)
{
    /*
    printf("Obj-C class called: now calling SSZip ...");
    
    //NSString *filename = @"MyZipFile.zip";
    NSString *zipFilePath = [NSString stringWithUTF8String:_zipFilePath.c_str()];
    
    NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *zipPath = [documentsDirectory stringByAppendingPathComponent:zipFilePath];
    
    //NSString *destinationPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *destinationPath = [NSString stringWithUTF8String:_destFolder.c_str()];
    
    [SSZipArchive unzipFileAtPath:zipFilePath toDestination:destinationPath];
    */
};


#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


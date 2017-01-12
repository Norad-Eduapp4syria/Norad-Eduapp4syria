#import "SSZipArchive/SSZipArchive.h"
#import "iosUnzip.h"

void iosUnzip::unZipArchiveToFolder(std::string _zipFilePath, std::string _destFolder)
{
    printf("Obj-C class called: now calling SSZip ...");
    
    //NSString *filename = @"MyZipFile.zip";
    NSString *zipFilePath = [NSString stringWithUTF8String:_zipFilePath.c_str()];
    
    NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *zipPath = [documentsDirectory stringByAppendingPathComponent:zipFilePath];

    //NSString *destinationPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *destinationPath = [NSString stringWithUTF8String:_destFolder.c_str()];
    
    [SSZipArchive unzipFileAtPath:zipFilePath toDestination:destinationPath];
};

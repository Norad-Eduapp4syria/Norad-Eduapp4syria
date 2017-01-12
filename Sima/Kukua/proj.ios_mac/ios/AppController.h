#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,
UIImagePickerControllerDelegate,UINavigationControllerDelegate> {
    UIWindow *window;
}
@property () BOOL restrictRotation;

@property(nonatomic, readonly) RootViewController* viewController;

- (void) openCamera:(NSString*)name :(NSInteger) width :(NSInteger) height;
- (void) saveImage:(NSString*)name;
@property(nonatomic, readonly) NSString *imageName;
@property NSInteger imageWidth;
@property NSInteger imageHeight;


@end


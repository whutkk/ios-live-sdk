//
//  UPAVCapturer.h
//  UPAVCaptureDemo
//
//  Created by DING FENG on 3/31/16.
//  Copyright © 2016 upyun.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, UPAVCapturerLogger_level) {
    UPAVCapturerLogger_level_debug,
    UPAVCapturerLogger_level_warn,
    UPAVCapturerLogger_level_error
};

typedef NS_ENUM(NSInteger, UPAVCapturerStatus) {
    UPAVCapturerStatusLiving,
    UPAVCapturerStatusStopped,
};

typedef NS_ENUM(NSInteger, UPAVCapturerPresetLevel) {
    UPAVCapturerPreset_480x360,
    UPAVCapturerPreset_640x480,
    UPAVCapturerPreset_1280x720
};

typedef NS_ENUM(NSInteger, UPBeautifyFilterLevel) {
    Beautify_None,
    Beautify_Low,
    Beautify_Normal,
    Beautify_High
};

typedef void(^UPAVCapturerStatusBlock)(UPAVCapturerStatus status, NSError *error);

@interface UPAVCapturer : NSObject

@property (nonatomic, strong) NSString *outStreamPath;
@property (nonatomic, strong, readonly) AVCaptureSession *captureSession;
@property (nonatomic) AVCaptureDevicePosition camaraPosition;
@property (nonatomic) BOOL camaraTorchOn;
@property (nonatomic) AVCaptureVideoOrientation videoOrientation;

@property (nonatomic, strong) UPAVCapturerStatusBlock uPAVCapturerStatusBlock;

@property (nonatomic) int32_t fps;
@property (nonatomic, assign) BOOL filter;
@property (nonatomic, assign) UPBeautifyFilterLevel filterLevel;

//默认为 YES，即 UPAVCapturer start 之后会立即推流直播; 如果想延时推流，可以先将 streamingOnOff 设置为 NO，随后需要推流的时候再置为 YES。
@property (nonatomic, assign) BOOL streamingOnOff;
@property (nonatomic) UPAVCapturerPresetLevel capturerPresetLevel;


- (void)start;
- (void)stop;
- (void)changeCamera;
- (UIView *)previewWithFrame:(CGRect)frame contentMode:(UIViewContentMode)mode;

+ (UPAVCapturer *)sharedInstance;
+ (void)setLogLevel:(UPAVCapturerLogger_level)level;



/* 生成推流 token
 例如推流地址：rtmp://bucket.v0.upaiyun.com/live/abc?_upt=abcdefgh1370000600
 其中：
 bucket 为 bucket name；
 live 为 appName；
 abc 为 streamName；
 
 abcdefgh1370000600 为推流token 可以用此方法计算生成。
 */
+ (NSString *)tokenWithKey:(NSString *)key //空间密钥
                    bucket:(NSString *)bucket //空间名
                expiration:(int)expiration //token 过期时间
           applicationName:(NSString *)appName //应用名，比如示例推流地址中的 live
                streamName:(NSString *)streamName; //流名， 比如示例推流地址中的 abc

@end


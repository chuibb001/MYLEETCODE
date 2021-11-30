//
//  ViewController.m
//  SUBJECT
//
//  Created by 晏榆 on 2021/11/30.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, assign) NSObject *zombieObject;

@end

@implementation ViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  // Do any additional setup after loading the view.
  NSString *str = @"123";
  NSData *data = [self dataWithHexString:str];
  NSString *hexString = [self hexStringWithData:data];
  NSLog(@"data %@",data);
  NSLog(@"hexString %@",hexString);
  //NSLog(@"zombieString %@", self.zombieObject);
}

- (NSData *)dataWithHexString:(NSString *)str
{
    NSObject *tempString = [[NSObject alloc] init];
    self.zombieObject = tempString;
  if (!str || [str length] == 0) {
          return nil;
      }
      
      NSMutableData *hexData = [[NSMutableData alloc] initWithCapacity:8];
      NSRange range;
      // 奇数的情况，第一个字符表示1个B，其他都是2个字符标识一1个B
      if ([str length] % 2 == 0) {
          range = NSMakeRange(0, 2);
      } else {
          range = NSMakeRange(0, 1);
      }
      for (NSInteger i = range.location; i < [str length]; i += 2) {
          unsigned int anInt;
          NSString *hexCharStr = [str substringWithRange:range];
          NSScanner *scanner = [[NSScanner alloc] initWithString:hexCharStr];
          
          //不用scanner也行，手算出16进制对应的十进制
          [scanner scanHexInt:&anInt];
          NSData *entity = [[NSData alloc] initWithBytes:&anInt length:1];
          [hexData appendData:entity];
          
          range.location += range.length;
          range.length = 2;
      }
      return hexData;
}

- (NSString *)hexStringWithData:(NSData *)data
{
    const unsigned char* dataBuffer = (const unsigned char*)[data bytes];
    if(!dataBuffer){
        return nil;
    }
    NSUInteger dataLength = [data length];
    NSMutableString* hexString = [NSMutableString stringWithCapacity:(dataLength * 2)];
    for(int i = 0; i < dataLength; i++){
        // %x以16进制的形式输出整数
        [hexString appendString:[NSString stringWithFormat:@"%02lx", (unsigned long)dataBuffer[i]]];
    }
    NSString* result = [NSString stringWithString:hexString];
    return result;
    
}

@end

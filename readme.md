## Qt 简易日志系统

* 在项目中包含头文件 hlog.h; 
*  在main函数中加入qInstallMessageHandler( hMessageOutput ) 即可
* hlog.h中 LOG_SIZE 代表每个日志文件的最大daxiao， LOG_COUNT 表示日志文件的数量

